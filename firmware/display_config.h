#ifndef DISPLAY_CONFIG_H
#define DISPLAY_CONFIG_H

#define JC8048W550C             // 5inch C-touch
// #define WAVESHARE_S3_LCD7       // 7inch waveshare

#ifdef JC8048W550C

#define LCD_PIN_BACKLIGHT   GPIO_NUM_2

// resolution
#define LCD_WIDTH   800U
#define LCD_HEGHT   480U

#define LCD_PIN_HENABLE     GPIO_NUM_40
#define LCD_PIN_VSYNC       GPIO_NUM_41
#define LCD_PIN_HSYNC       GPIO_NUM_39
#define LCD_PIN_PCLK        GPIO_NUM_42

// RGB565 data pins
#define LCD_PIN_DATA_R0     GPIO_NUM_45
#define LCD_PIN_DATA_R1     GPIO_NUM_48
#define LCD_PIN_DATA_R2     GPIO_NUM_47
#define LCD_PIN_DATA_R3     GPIO_NUM_21
#define LCD_PIN_DATA_R4     GPIO_NUM_14
  
#define LCD_PIN_DATA_G0     GPIO_NUM_5
#define LCD_PIN_DATA_G1     GPIO_NUM_6
#define LCD_PIN_DATA_G2     GPIO_NUM_7
#define LCD_PIN_DATA_G3     GPIO_NUM_15
#define LCD_PIN_DATA_G4     GPIO_NUM_16
#define LCD_PIN_DATA_G5     GPIO_NUM_4

#define LCD_PIN_DATA_B0     GPIO_NUM_8
#define LCD_PIN_DATA_B1     GPIO_NUM_3
#define LCD_PIN_DATA_B2     GPIO_NUM_46
#define LCD_PIN_DATA_B3     GPIO_NUM_9
#define LCD_PIN_DATA_B4     GPIO_NUM_1

// timing and polarity
#define LCD_FREQ                16000000U
#define LCD_PCLK_ACTIVE_NEG     1
#define LCD_DE_IDLE_HIGH        1
#define LCD_PCLK_IDLE_HIGH      1

#define LCD_HSYNC_POLARITY      0
#define LCD_HSYNC_FRONT_PORCH   8
#define LCD_HSYNC_PULSE_WIDTH   4
#define LCD_HSYNC_BACK_PORCH    8

#define LCD_VSYNC_POLARITY      0
#define LCD_VSYNC_FRONT_PORCH   8
#define LCD_VSYNC_PULSE_WIDTH   4
#define LCD_VSYNC_BACK_PORCH    8

// touch
#define TOUCH_XMAX  LCD_WIDTH - 1
#define TOUCH_YMAX  LCD_HEGHT - 1

#define TOUCH_PIN_INT   GPIO_NUM_NC
#define TOUCH_PIN_RST   GPIO_NUM_38
#define TOUCH_PIN_SDA   GPIO_NUM_19
#define TOUCH_PIN_SCL   GPIO_NUM_20

#define TOUCH_FREQ      400000U
#define TOUCH_ROTATION  0

#endif  // JC8048W550C end

#endif  // HEADER
