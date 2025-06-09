// #define DEBUG

#include "lvgl.h"
#include "lv_conf.h"
#include "ui.h"
#include "display_config.h"
#include "display_driver.h"
#include <Ticker.h>
#include "driver/twai.h"
#include "can_communication.h"

static SemaphoreHandle_t dataMutex;
static SemaphoreHandle_t uiMutex;


static LGFX display;

// LVGL callbacks
void disp_flush_callback(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *px_map) {
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  display.startWrite();
  display.setAddrWindow(area->x1, area->y1, w, h);
  display.pushPixelsDMA((uint16_t *)px_map, w * h, true);
  display.endWrite();

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
// UI Widget updaters
Ticker updateUiFast;
Ticker updateUiMid;
Ticker updateUiSlow;

//CAN Receiver
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

// Widget updaters
static void fastUpdate() {
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
}

static void midUpdate() {
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
}

static void slowUpdate() {
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
}
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
  ledcWrite(LCD_PIN_BACKLIGHT, brightnessVal);
}

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
  ledcAttach(LCD_PIN_BACKLIGHT, 600, 8);
  ledcWrite(LCD_PIN_BACKLIGHT, brightnessVal);

  display.init();
  display.fillScreen(TFT_BLACK);
  uiMutex = xSemaphoreCreateMutex();

  lv_init();

  disp_draw_buf1 = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * LCD_WIDTH * LCD_HEGHT / 10, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
  disp_draw_buf2 = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * LCD_WIDTH * LCD_HEGHT / 10, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);

  lv_disp_draw_buf_init(&draw_buf, disp_draw_buf1, disp_draw_buf2, LCD_WIDTH * LCD_HEGHT / 10);

  /* Initialize the display */
  lv_disp_drv_init(&disp_drv);
  /* Change the following line to your display resolution */
  disp_drv.hor_res = LCD_WIDTH;
  disp_drv.ver_res = LCD_HEGHT;
  disp_drv.flush_cb = disp_flush_callback;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = &touchpad_read;
  lv_indev_drv_register(&indev_drv);


  // Crate task get data and updater
  xTaskCreatePinnedToCore(TaskCANReceiver, "TaskCANReceiver", 4 * 1024, NULL, 1, NULL, 0);

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

void upBrightness(lv_event_t *e) {
  setBrightness(brightnessVal + 40);
}
void downBribrightness(lv_event_t *e) {
  setBrightness(brightnessVal - 40);
}
void benchIGN1(lv_event_t *e) {}
void benchIGN2(lv_event_t *e) {}
void benchIGN3(lv_event_t *e) {}
void benchIGN4(lv_event_t *e) {}
void benchIGN5(lv_event_t *e) {}
void benchIGN6(lv_event_t *e) {}
void benchIGN7(lv_event_t *e) {}
void benchIGN8(lv_event_t *e) {}
void benchINJ1(lv_event_t *e) {}
void benchINJ2(lv_event_t *e) {}
void benchINJ3(lv_event_t *e) {}
void benchINJ4(lv_event_t *e) {}
void benchINJ5(lv_event_t *e) {}
void benchINJ6(lv_event_t *e) {}
void benchINJ7(lv_event_t *e) {}
void benchINJ8(lv_event_t *e) {}
void StartStop(lv_event_t *e) {}
