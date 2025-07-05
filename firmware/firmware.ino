
#include "display_driver.h"
#include "updaters.h"
#include "mutex.h"

static lv_disp_draw_buf_t draw_buf;
static lv_color_t *disp_draw_buf1;
static lv_color_t *disp_draw_buf2;
static lv_disp_drv_t disp_drv;

void setup(void) {

#ifdef DEBUG
  Serial.begin(115200);
  Serial.println("Setup starting");
#endif

  mutex_init();
  lcd_panel_start();
  lv_init();

  disp_draw_buf1 = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * LCD_WIDTH * LCD_HEGHT / 10, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
  disp_draw_buf2 = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * LCD_WIDTH * LCD_HEGHT / 10, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
  lv_disp_draw_buf_init(&draw_buf, disp_draw_buf1, disp_draw_buf2, LCD_WIDTH * LCD_HEGHT / 10);

  lv_disp_drv_init(&disp_drv);
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
  xTaskCreatePinnedToCore(TaskHeartbeat, "TaskHeartbeat", 1 * 1024, NULL, 1, NULL, 0);

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