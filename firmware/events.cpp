#include "updaters.h"
#include "display_driver.h"

void upBrightness(lv_event_t *e) {
  setBrightness(brightnessVal + 40);
}

void downBribrightness(lv_event_t *e) {
  setBrightness(brightnessVal - 40);
}

void benchIGN1(lv_event_t *e) {
  uint8_t data[] = {0x66, 0x02, 0x03, 0x04};
  can.send(0x77000C, data, sizeof(data), true);
#ifdef DEBUG
    Serial.println("benchIGN1");
#endif
}

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
void benchFuelPump(lv_event_t * e){}
void benchFan2(lv_event_t * e){}
void benchFan1(lv_event_t * e){}