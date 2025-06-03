// #define DEBUG

#include "lvgl.h"
#include "lv_conf.h"
// #include <examples/lv_examples.h>
// #include <demos/lv_demos.h>
#include "ui.h"

static SemaphoreHandle_t dataMutex;
static SemaphoreHandle_t uiMutex;

#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include <lgfx/v1/platforms/esp32s3/Panel_RGB.hpp>
#include <lgfx/v1/platforms/esp32s3/Bus_RGB.hpp>

/*******************************************************************************/
// Dislay driver config
class LGFX : public lgfx::LGFX_Device {

  lgfx::Bus_RGB _bus_instance;
  lgfx::Touch_GT911 _touch_instance;
  lgfx::Panel_RGB _panel_instance;

public:
  LGFX(void) {
    {
      auto cfg = _bus_instance.config();
      cfg.panel = &_panel_instance;

      // Configure sync and clock pins.
      cfg.pin_henable = GPIO_NUM_40;
      cfg.pin_vsync = GPIO_NUM_41;
      cfg.pin_hsync = GPIO_NUM_39;
      cfg.pin_pclk = GPIO_NUM_42;
      cfg.freq_write = 16000000;  // 14000000 (try 15, 14 or 16 Mhz for different esp32 chip clone)
      // Configure data pins.
      cfg.pin_d0 = GPIO_NUM_8;   // B0
      cfg.pin_d1 = GPIO_NUM_3;   // B1
      cfg.pin_d2 = GPIO_NUM_46;  // B2
      cfg.pin_d3 = GPIO_NUM_9;   // B3
      cfg.pin_d4 = GPIO_NUM_1;   // B4

      cfg.pin_d5 = GPIO_NUM_5;   // G0
      cfg.pin_d6 = GPIO_NUM_6;   // G1
      cfg.pin_d7 = GPIO_NUM_7;   // G2
      cfg.pin_d8 = GPIO_NUM_15;  // G3
      cfg.pin_d9 = GPIO_NUM_16;  // G4
      cfg.pin_d10 = GPIO_NUM_4;  // G5

      cfg.pin_d11 = GPIO_NUM_45;  // R0
      cfg.pin_d12 = GPIO_NUM_48;  // R1
      cfg.pin_d13 = GPIO_NUM_47;  // R2
      cfg.pin_d14 = GPIO_NUM_21;  // R3
      cfg.pin_d15 = GPIO_NUM_14;  // R4

      // Configure timing parameters for horizontal and vertical sync.
      cfg.hsync_polarity = 0;
      cfg.hsync_front_porch = 8;  //8;
      cfg.hsync_pulse_width = 4;  //4;
      cfg.hsync_back_porch = 8;   //8;

      cfg.vsync_polarity = 0;
      cfg.vsync_front_porch = 8;  //8;
      cfg.vsync_pulse_width = 4;  //4;
      cfg.vsync_back_porch = 8;   //8;

      // Configure polarity for clock and data transmission.
      cfg.pclk_active_neg = 1;
      cfg.de_idle_high = 1;    // 0
      cfg.pclk_idle_high = 1;  // 0

      _bus_instance.config(cfg);               
      _panel_instance.setBus(&_bus_instance);  
    }

    {                                       
      auto cfg = _panel_instance.config();  
      cfg.memory_width = 800;
      cfg.memory_height = 480;
      cfg.panel_width = 800;
      cfg.panel_height = 480;
      cfg.offset_x = 0;
      cfg.offset_y = 0;
      // cfg.offset_rotation = 0;
      // cfg.dummy_read_pixel = 16;
      // cfg.dummy_read_bits = 1;
      // cfg.readable = false;  //true
      // cfg.invert = false;
      // cfg.rgb_order = false;
      // cfg.dlen_16bit = true;   // false
      // cfg.bus_shared = false;  // true
      _panel_instance.config(cfg);
    }
    {
      auto cfg = _touch_instance.config();
      cfg.x_min = 0;
      cfg.x_max = 799;
      cfg.y_min = 0;
      cfg.y_max = 479;
      cfg.pin_int = GPIO_NUM_NC;
      cfg.pin_rst = GPIO_NUM_38;
      cfg.bus_shared = false;
      cfg.offset_rotation = 0;
      cfg.i2c_port = 1;           
      cfg.pin_sda = GPIO_NUM_19;
      cfg.pin_scl = GPIO_NUM_20;
      cfg.freq = 400000;

      _touch_instance.config(cfg);
      _panel_instance.setTouch(&_touch_instance);
    }

    setPanel(&_panel_instance);  
  }
};

static LGFX display;

void disp_flush_callback(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *px_map) {
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  display.startWrite();
  display.setAddrWindow(area->x1, area->y1, w, h);
  display.pushPixelsDMA((uint16_t *)px_map, w * h, true);
  // display.writePixels((uint16_t *)px_map, w * h, true);
  display.endWrite();
  // display.pushImageDMA(area->x1, area->y1, w, h, (lgfx::swap565_t *)&px_map->full);

  lv_disp_flush_ready(disp);
}

void touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data) {
  int32_t x, y;
  data->state = LV_INDEV_STATE_REL;
  if (display.getTouch(&x, &y)) {
    data->state = LV_INDEV_STATE_PR;
    data->point.x = x;
    data->point.y = y;
  }
}

/*******************************************************************************/
// Widget updaters
#include <Ticker.h>
#define PERIOD_FAST_MS 20
#define PERIOD_MID_MS 200
#define PERIOD_SLOW_MS 800

Ticker updateUiFast;
Ticker updateUiMid;
Ticker updateUiSlow;

typedef struct struct_message {
  int rpm;
  int speed;
  int clt;
  int iat;
  float afr;
  float Vbat;
  int fuelLevel;
  float map;
  float oilPress;
  float fuelPress;
  bool mainRelay;
  bool fuelPump;
  bool fan1;
  bool fan2;
} struct_message;

volatile static struct_message myData;
volatile static struct_message old_myData;

static void fastUpdate() {
  // void fastUpdate(void *pvParameters){
  //   while (1) {
  if (xSemaphoreTake(dataMutex, portMAX_DELAY) == pdTRUE) {
#ifdef DEBUG
    Serial.println("fastUpdate");
#endif
    if (xSemaphoreTake(uiMutex, portMAX_DELAY) == pdTRUE) {
      // RPM
      if (myData.rpm != old_myData.rpm) {
        int val = myData.rpm / 10;
        lv_bar_set_value(ui_rpmBar0, val, LV_ANIM_OFF);
        if (val > 600) {
          lv_obj_set_style_bg_color(ui_rpmBar0, lv_color_hex(0xFF0000), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        } else {
          lv_obj_set_style_bg_color(ui_rpmBar0, lv_color_hex(0xE0FF00), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        lv_label_set_text_fmt(ui_rpmVal0, "%d0", val);
        old_myData.rpm = myData.rpm;
      }
      // MAP
      if (myData.map != old_myData.map) {
        lv_bar_set_value(ui_mapBar0, myData.map, LV_ANIM_OFF);
        lv_label_set_text_fmt(ui_mapVal0, "%.0f", myData.map);
        old_myData.map = myData.map;
      }
      // AFR
      if (myData.afr != old_myData.afr) {
        int l_bar = myData.afr * 10 - 150;
        lv_bar_set_value(ui_afrBar0, l_bar, LV_ANIM_OFF);
        lv_label_set_text_fmt(ui_afrVal0, "%0.1f", myData.afr);

        if ((l_bar > 10) || (l_bar < -25)) {
          lv_obj_set_style_bg_color(ui_afrBar0, lv_color_hex(0xFF0000), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        } else if (l_bar > 0) {
          lv_obj_set_style_bg_color(ui_afrBar0, lv_color_hex(0x00FFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        } else {
          lv_obj_set_style_bg_color(ui_afrBar0, lv_color_hex(0xE0FF00), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        old_myData.afr = myData.afr;
      }
      xSemaphoreGive(uiMutex);
    }
    xSemaphoreGive(dataMutex);
  }
  //   vTaskDelay(pdMS_TO_TICKS(PERIOD_FAST_MS));
  // }
}

static void midUpdate() {
  // void midUpdate(void *pvParameters) {
  // while (1) {
  if (xSemaphoreTake(dataMutex, portMAX_DELAY) == pdTRUE) {
#ifdef DEBUG
    Serial.println("midUpdate");
#endif
    if (xSemaphoreTake(uiMutex, portMAX_DELAY) == pdTRUE) {
      // VSS
      if (myData.speed != old_myData.speed) {
        lv_label_set_text_fmt(ui_speedVal0, "%d", myData.speed);
        old_myData.speed = myData.speed;
      }
      // OIL Press
      if (myData.oilPress != old_myData.oilPress) {
        lv_bar_set_value(ui_oilPressBar0, myData.oilPress, LV_ANIM_ON);
        lv_label_set_text_fmt(ui_oilPressVal0, "%.1f", myData.oilPress / 100);
        if (myData.oilPress > 180) {
          lv_obj_set_style_bg_color(ui_oilPressBar0, lv_color_hex(0xE6FF00), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        } else {
          lv_obj_set_style_bg_color(ui_oilPressBar0, lv_color_hex(0xFF0000), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        old_myData.oilPress = myData.oilPress;
      }
      // Fuel Press
      if (myData.fuelPress != old_myData.fuelPress) {
        lv_bar_set_value(ui_fuelPressBar0, myData.fuelPress, LV_ANIM_ON);  ///set low press
        lv_label_set_text_fmt(ui_fuelPressVal0, "%.1f", myData.fuelPress / 100);
        if (myData.fuelPress > 270) {
          lv_obj_set_style_bg_color(ui_fuelPressBar0, lv_color_hex(0xE6FF00), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        } else {
          lv_obj_set_style_bg_color(ui_fuelPressBar0, lv_color_hex(0xFF0000), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        old_myData.fuelPress = myData.fuelPress;
      }
      xSemaphoreGive(uiMutex);
    }
    xSemaphoreGive(dataMutex);
  }
  //   vTaskDelay(pdMS_TO_TICKS(PERIOD_MID_MS));
  // }
}

static void slowUpdate() {
  // void slowUpdate(void *pvParameters) {
  // while (1) {
  if (xSemaphoreTake(dataMutex, portMAX_DELAY) == pdTRUE) {
#ifdef DEBUG
    Serial.println("slowUpdate");
#endif
    if (xSemaphoreTake(uiMutex, portMAX_DELAY) == pdTRUE) {
      // CLT
      if (myData.clt != old_myData.clt) {
        lv_bar_set_value(ui_cltBar0, myData.clt, LV_ANIM_ON);
        lv_label_set_text_fmt(ui_cltVal0, "%d", myData.clt);
        if (myData.clt < 102) {
          lv_obj_set_style_bg_color(ui_cltBar0, lv_color_hex(0xE6FF00), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        } else {
          lv_obj_set_style_bg_color(ui_cltBar0, lv_color_hex(0xFF0000), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        old_myData.clt = myData.clt;
      }
      // IAT
      if (myData.iat != old_myData.iat) {
        lv_bar_set_value(ui_iatBar0, myData.iat, LV_ANIM_ON);
        lv_label_set_text_fmt(ui_iatVal0, "%d", myData.iat);
        old_myData.iat = myData.iat;
      }
      // Vbat
      if (myData.Vbat != old_myData.Vbat) {
        lv_bar_set_value(ui_vBattBar0, myData.Vbat * 10, LV_ANIM_ON);
        lv_label_set_text_fmt(ui_vBattVal0, "%0.1f", myData.Vbat);
        if (myData.Vbat < 12) {
          lv_obj_set_style_bg_color(ui_vBattBar0, lv_color_hex(0xFF0000), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        } else if (myData.Vbat > 15) {
          lv_obj_set_style_bg_color(ui_vBattBar0, lv_color_hex(0xFF0000), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        } else {
          lv_obj_set_style_bg_color(ui_vBattBar0, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        old_myData.Vbat = myData.Vbat;
      }
      // Fuel level
      if (myData.fuelLevel != old_myData.fuelLevel) {
        lv_bar_set_value(ui_fuelLevelBar0, myData.fuelLevel, LV_ANIM_ON);
        lv_label_set_text_fmt(ui_fuelLevelVal0, "%d", myData.fuelLevel);
        if (myData.fuelLevel > 15) {
          lv_obj_set_style_bg_color(ui_fuelLevelBar0, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        } else {
          lv_obj_set_style_bg_color(ui_fuelLevelBar0, lv_color_hex(0xFF0000), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        old_myData.fuelLevel = myData.fuelLevel;
      }
      xSemaphoreGive(uiMutex);
    }
    xSemaphoreGive(dataMutex);
  }
  // vTaskDelay(pdMS_TO_TICKS(PERIOD_SLOW_MS));
  // }
}

/*******************************************************************************/
//CAN Receiver
#include "driver/twai.h"
// Pins used to connect to CAN bus transceiver:
#define RX_PIN 18
#define TX_PIN 17

// Interval:
#define POLLING_RATE_MS 50

void TaskCANReceiver(void *pvParameters) {
  twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT((gpio_num_t)TX_PIN, (gpio_num_t)RX_PIN, TWAI_MODE_NORMAL);  //TWAI_MODE_LISTEN_ONLY);
  twai_timing_config_t t_config = TWAI_TIMING_CONFIG_500KBITS();
  twai_filter_config_t f_config = {
    .acceptance_code = 0x20000000U << 3,  //0x200,// << 21,
    .acceptance_mask = 0x007FFFFFU << 3,  // << 21,
    .single_filter = false
  };

  // Install TWAI driver
  if (twai_driver_install(&g_config, &t_config, &f_config) != ESP_OK) {
#ifdef DEBUG
    Serial.println("Failed to install driver");
#endif
    while (1) {}
  }

  // Start TWAI driver
  if (twai_start() != ESP_OK) {
#ifdef DEBUG
    Serial.println("Failed to start driver");
#endif
    while (1) {}
  }

  // Reconfigure alerts to detect frame receive, Bus-Off error and RX queue full states
  uint32_t alerts_to_enable = TWAI_ALERT_RX_DATA;  // | TWAI_ALERT_ERR_PASS | TWAI_ALERT_BUS_ERROR | TWAI_ALERT_RX_QUEUE_FULL;
  if (twai_reconfigure_alerts(alerts_to_enable, NULL) != ESP_OK) {
#ifdef DEBUG
    Serial.println("Failed to reconfigure alerts");
#endif
    while (1) {}
  }

  dataMutex = xSemaphoreCreateMutex();

  updateUiFast.attach_ms(PERIOD_FAST_MS, fastUpdate);
  updateUiMid.attach_ms(PERIOD_MID_MS, midUpdate);
  updateUiSlow.attach_ms(PERIOD_SLOW_MS, slowUpdate);

  while (1) {
    uint32_t alerts_triggered;
    twai_read_alerts(&alerts_triggered, pdMS_TO_TICKS(POLLING_RATE_MS));
    // Check if message is received
    if (alerts_triggered & TWAI_ALERT_RX_DATA) {
      // One or more messages received. Handle all.
      twai_message_t message;
      while (twai_receive(&message, 0) == ESP_OK) {

        //  ID 0x200
        // SG_ WarningCounter : 0|16@1+ (1,0) [0|0] "" Vector__XXX
        // SG_ LastError : 16|16@1+ (1,0) [0|0] "" Vector__XXX
        // SG_ RevLimAct : 32|1@1+ (1,0) [0|0] "" Vector__XXX
        // SG_ MainRelayAct : 33|1@1+ (1,0) [0|0] "" Vector__XXX
        // SG_ FuelPumpAct : 34|1@1+ (1,0) [0|0] "" Vector__XXX
        // SG_ CELAct : 35|1@1+ (1,0) [0|0] "" Vector__XXX
        // SG_ EGOHeatAct : 36|1@1+ (1,0) [0|0] "" Vector__XXX
        // SG_ LambdaProtectAct : 37|1@1+ (1,0) [0|0] "" Vector__XXX
        // SG_ CurrentGear : 40|8@1+ (1,0) [0|0] "" Vector__XXX
        // SG_ DistanceTraveled : 48|16@1+ (0.1,0) [0|6553.5] "km" Vector__XXX
        // SG_ Fan : 38|1@1+ (1,0) [0|0] "" Vector__XXX
        // SG_ Fan2 : 39|1@1+ (1,0) [0|0] "" Vector__XXX

        //  ID 0x201
        //  SG_ RPM : 0|16@1+ (1,0) [0|0] "RPM" Vector__XXX
        //  SG_ IgnitionTiming : 16|16@1- (0.02,0) [0|0] "deg" Vector__XXX
        //  SG_ InjDuty : 32|8@1+ (0.5,0) [0|100] "%" Vector__XXX
        //  SG_ IgnDuty : 40|8@1+ (0.5,0) [0|100] "%" Vector__XXX
        //  SG_ VehicleSpeed : 48|8@1+ (1,0) [0|255] "kph" Vector__XXX
        //  SG_ FlexPct : 56|8@1+ (1,0) [0|100] "%" Vector__XXX

        //  ID 0x202
        //  SG_ PPS : 0|16@1- (0.01,0) [0|100] "%" Vector__XXX
        //  SG_ TPS1 : 16|16@1- (0.01,0) [0|100] "%" Vector__XXX
        //  SG_ TPS2 : 32|16@1- (0.01,0) [0|100] "%" Vector__XXX
        //  SG_ Wastegate : 48|16@1- (0.01,0) [0|100] "%" Vector__XXX

        //  ID 0x203
        //  SG_ MAP : 0|16@1+ (0.03333333,0) [0|0] "kPa" Vector__XXX
        //  SG_ CoolantTemp : 16|8@1+ (1,-40) [-40|200] "deg C" Vector__XXX
        //  SG_ IntakeTemp : 24|8@1+ (1,-40) [-40|200] "deg C" Vector__XXX
        //  SG_ AUX1Temp : 32|8@1+ (1,-40) [-40|200] "deg C" Vector__XXX
        //  SG_ AUX2Temp : 40|8@1+ (1,-40) [-40|200] "deg C" Vector__XXX
        //  SG_ MCUTemp : 48|8@1+ (1,-40) [-40|100] "deg C" Vector__XXX
        //  SG_ FuelLevel : 56|8@1+ (0.5,0) [0|0] "%" Vector__XXX

        //  ID 0x204
        //  SG_ OilPress : 16|16@1+ (0.03333333,0) [0|0] "kPa" Vector__XXX
        //  SG_ OilTemperature : 32|8@1+ (1,-40) [-40|215] "deg C" Vector__XXX
        //  SG_ FuelTemperature : 40|8@1+ (1,-40) [-40|215] "deg C" Vector__XXX
        //  SG_ BattVolt : 48|16@1+ (0.001,0) [0|25] "mV" Vector__XXX

        //  ID 0x207
        //  SG_ Lam1 : 0|16@1+ (0.0001,0) [0|2] "lambda" Vector__XXX
        //  SG_ Lam2 : 16|16@1+ (0.0001,0) [0|2] "lambda" Vector__XXX
        //  SG_ FpLow : 32|16@1+ (0.03333333,0) [0|0] "kPa" Vector__XXX
        //  SG_ FpHigh : 48|16@1+ (0.1,0) [0|0] "bar" Vector__XXX
        if (xSemaphoreTake(dataMutex, portMAX_DELAY) == pdTRUE) {
          switch (message.identifier) {
            case 0x201:
              myData.rpm = (message.data[1] << 8 | message.data[0]);
              myData.speed = message.data[6];
              break;
            case 0x203:
              myData.map = (message.data[1] << 8 | message.data[0]) * 0.0333;
              myData.clt = message.data[2] - 40;
              myData.iat = message.data[3] - 40;
              myData.fuelLevel = message.data[7] / 2;
              break;
            case 0x204:
              myData.oilPress = (message.data[3] << 8 | message.data[2]) * 0.0333;
              myData.Vbat = (message.data[7] << 8 | message.data[6]) * 0.001;
              break;
            case 0x207:
              myData.afr = (message.data[1] << 8 | message.data[0]) * 0.00147;
              myData.fuelPress = (message.data[5] << 8 | message.data[4]) * 0.0333;
              break;
          }
          xSemaphoreGive(dataMutex);
        }
      }
    }
    vTaskDelay(pdMS_TO_TICKS(5));
  }
}

/*******************************************************************************/

/*******************************************************************************/
// Initial setup
static int brightnessVal;

void setBrightness(int val) {
  if (val <= 55) {
    brightnessVal = 55;
  } else {
    if (val >= 255) {
      brightnessVal = 255;
    } else {
      brightnessVal = val;
    }
  }
  ledcWrite(GPIO_NUM_2, brightnessVal);
}

void upBrightness(lv_event_t *e) {
  setBrightness(brightnessVal + 40);
}
void downBribrightness(lv_event_t *e) {
  setBrightness(brightnessVal - 40);
}

const uint32_t screenWidth = 800;
const uint32_t screenHeight = 480;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t *disp_draw_buf1;
static lv_color_t *disp_draw_buf2;
static lv_disp_drv_t disp_drv;

void setup(void) {
  brightnessVal = 205;
#ifdef DEBUG
  Serial.begin(115200);
  Serial.println("Setup starting");
#endif
  ledcAttach(GPIO_NUM_2, 600, 8);
  ledcWrite(GPIO_NUM_2, brightnessVal);

  display.init();
  display.fillScreen(TFT_BLACK);
  uiMutex = xSemaphoreCreateMutex();

  lv_init();

  disp_draw_buf1 = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * screenWidth * screenHeight / 10, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
  disp_draw_buf2 = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * screenWidth * screenHeight / 10, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
  // disp_draw_buf2 = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * screenWidth * screenHeight / 10, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);

  lv_disp_draw_buf_init(&draw_buf, disp_draw_buf1, disp_draw_buf2, screenWidth * screenHeight / 10);

  /* Initialize the display */
  lv_disp_drv_init(&disp_drv);
  /* Change the following line to your display resolution */
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = disp_flush_callback;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = &touchpad_read;
  lv_indev_drv_register(&indev_drv);

  // lv_demo_benchmark();
  // lv_demo_widgets();

  // Crate task get data and updater
  xTaskCreatePinnedToCore(TaskCANReceiver, "TaskCANReceiver", 4 * 1024, NULL, 1, NULL, 0);
  // xTaskCreatePinnedToCore(fastUpdate, "fastUpdate", 4 * 1024, NULL, 1, NULL, 0);
  // xTaskCreatePinnedToCore(midUpdate, "midUpdate", 1 * 1024, NULL, 1, NULL, 0);
  // xTaskCreatePinnedToCore(slowUpdate, "slowUpdate", 1 * 1024, NULL, 1, NULL, 0);
  // xTaskCreatePinnedToCore(tickerUi, "tickerUi", 4 * 1024, NULL, 1, NULL, 0);

  // updateUiFast.attach_ms(PERIOD_FAST_MS, fastUpdate);
  // updateUiMid.attach_ms(PERIOD_MID_MS, midUpdate);
  // updateUiSlow.attach_ms(PERIOD_SLOW_MS, slowUpdate);

  ui_init();

#ifdef DEBUG
  Serial.println("Setup done");
#endif
}

void loop(void) {
  if (xSemaphoreTake(uiMutex, portMAX_DELAY) == pdTRUE) {
    lv_timer_handler();
    xSemaphoreGive(uiMutex);
  }

  vTaskDelay(pdMS_TO_TICKS(5));
}

/* void tickerUi(void *pvParameters) {
  while (1) {
    lv_timer_handler();
    vTaskDelay(pdMS_TO_TICKS(5));
  }
} */
