#include "display_driver.h"


// Dislay driver config

LCD_Panel::LCD_Panel(void) {
  {
    auto cfg = _bus_instance.config();
    cfg.panel = &_panel_instance;

    // Configure sync and clock pins.
    cfg.pin_henable = LCD_PIN_HENABLE;  //GPIO_NUM_40;
    cfg.pin_vsync = LCD_PIN_VSYNC;      //GPIO_NUM_41;
    cfg.pin_hsync = LCD_PIN_HSYNC;      //GPIO_NUM_39;
    cfg.pin_pclk = LCD_PIN_PCLK;        //GPIO_NUM_42;
    cfg.freq_write = LCD_FREQ;          //16000000;  // 14000000 (try 15, 14 or 16 Mhz for different esp32 chip clone)

    // Configure data pins.
    cfg.pin_d0 = LCD_PIN_DATA_B0;  //GPIO_NUM_8;   // B0
    cfg.pin_d1 = LCD_PIN_DATA_B1;  //GPIO_NUM_3;   // B1
    cfg.pin_d2 = LCD_PIN_DATA_B2;  //GPIO_NUM_46;  // B2
    cfg.pin_d3 = LCD_PIN_DATA_B3;  //GPIO_NUM_9;   // B3
    cfg.pin_d4 = LCD_PIN_DATA_B4;  //GPIO_NUM_1;   // B4

    cfg.pin_d5 = LCD_PIN_DATA_G0;   //GPIO_NUM_5;   // G0
    cfg.pin_d6 = LCD_PIN_DATA_G1;   //GPIO_NUM_6;   // G1
    cfg.pin_d7 = LCD_PIN_DATA_G2;   //GPIO_NUM_7;   // G2
    cfg.pin_d8 = LCD_PIN_DATA_G3;   //GPIO_NUM_15;  // G3
    cfg.pin_d9 = LCD_PIN_DATA_G4;   //GPIO_NUM_16;  // G4
    cfg.pin_d10 = LCD_PIN_DATA_G5;  //GPIO_NUM_4;  // G5

    cfg.pin_d11 = LCD_PIN_DATA_R0;  //GPIO_NUM_45;  // R0
    cfg.pin_d12 = LCD_PIN_DATA_R1;  //GPIO_NUM_48;  // R1
    cfg.pin_d13 = LCD_PIN_DATA_R2;  //GPIO_NUM_47;  // R2
    cfg.pin_d14 = LCD_PIN_DATA_R3;  //GPIO_NUM_21;  // R3
    cfg.pin_d15 = LCD_PIN_DATA_R4;  //GPIO_NUM_14;  // R4

    // Configure timing parameters for horizontal and vertical sync.
    cfg.hsync_polarity = LCD_HSYNC_POLARITY;        //0;
    cfg.hsync_front_porch = LCD_HSYNC_FRONT_PORCH;  //8;
    cfg.hsync_pulse_width = LCD_HSYNC_PULSE_WIDTH;  //4;
    cfg.hsync_back_porch = LCD_HSYNC_BACK_PORCH;    //8;

    cfg.vsync_polarity = LCD_VSYNC_POLARITY;        //0;
    cfg.vsync_front_porch = LCD_VSYNC_FRONT_PORCH;  //8;
    cfg.vsync_pulse_width = LCD_VSYNC_PULSE_WIDTH;  //4;
    cfg.vsync_back_porch = LCD_VSYNC_BACK_PORCH;    //8;

    // Configure polarity for clock and data transmission.
    cfg.pclk_active_neg = LCD_PCLK_ACTIVE_NEG;  //1;
    cfg.de_idle_high = LCD_DE_IDLE_HIGH;        //1;  // 0
    cfg.pclk_idle_high = LCD_PCLK_IDLE_HIGH;    //1;  // 0

    _bus_instance.config(cfg);
    _panel_instance.setBus(&_bus_instance);
  }
  {
    auto cfg = _panel_instance.config();
    cfg.memory_width = LCD_WIDTH;   //800;
    cfg.memory_height = LCD_HEIGHT;  //480;
    cfg.panel_width = LCD_WIDTH;    //800;
    cfg.panel_height = LCD_HEIGHT;   //480;
    cfg.offset_x = 0;
    cfg.offset_y = 0;
    _panel_instance.config(cfg);
  }
  {
    auto cfg = _touch_instance.config();
    cfg.x_min = 0;
    cfg.x_max = TOUCH_XMAX;  //799;
    cfg.y_min = 0;
    cfg.y_max = TOUCH_YMAX;       //479;
    cfg.pin_int = TOUCH_PIN_INT;  //GPIO_NUM_NC;
    cfg.pin_rst = TOUCH_PIN_RST;  //GPIO_NUM_38;
    cfg.bus_shared = false;
    cfg.offset_rotation = TOUCH_ROTATION;  //0;
    cfg.i2c_port = 1;
    cfg.pin_sda = TOUCH_PIN_SDA;  //GPIO_NUM_19;
    cfg.pin_scl = TOUCH_PIN_SCL;  //GPIO_NUM_20;
    cfg.freq = TOUCH_FREQ;        //400000;

    _touch_instance.config(cfg);
    _panel_instance.setTouch(&_touch_instance);
  }

  setPanel(&_panel_instance);
}

LCD_Panel display;
int brightnessVal = 205;

void lcd_panel_start() {

  ledcAttach(LCD_PIN_BACKLIGHT, 1000, 8);
  ledcWrite(LCD_PIN_BACKLIGHT, brightnessVal);
#if defined(WAVESHARE_S3_LCD7) || defined(WAVESHARE_S3_LCD5)
  pinMode(4, OUTPUT);
  /* Initialize IO expander */
  ESP_IOExpander_CH422G *expander = new ESP_IOExpander_CH422G(
    (i2c_port_t)I2C_NUM_0 /*I2C_MASTER_NUM*/, ESP_IO_EXPANDER_I2C_CH422G_ADDRESS,
    9 /*I2C_MASTER_SCL_IO*/, 8 /*I2C_MASTER_SDA_IO*/);

  expander->init();
  expander->begin();
  expander->enableAllIO_Output();
  expander->digitalWrite(1 /*TP_RST*/, HIGH);
  expander->digitalWrite(3 /*LCD_RST*/, HIGH);
  expander->digitalWrite(2 /*LCD_BL*/, HIGH);
  delay(100);
#endif

  display.init();
  display.fillScreen(TFT_BLACK);
}

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

void setBrightness(int val) {
// #ifdef JC8048W550C
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
// #endif
}