#include "updaters.h"
#include "display_driver.h"

void upBrightness(lv_event_t *e) {
  setBrightness(brightnessVal + 40);
}

void downBribrightness(lv_event_t *e) {
  setBrightness(brightnessVal - 40);
}

uint8_t data[] = { 0x66, 0x00, 0x00, 0x00, 0x00 };

void bench(uint8_t subsys, uint8_t index) {
  data[2] = subsys;
  data[4] = index;
  bool ret = can.send(0x77000C, data, sizeof(data), true);
  char sys[8] = { 0 };
  switch (subsys) {
    case 0x12:
      memcpy(&sys, "IGN", 3);
      break;
    case 0x13:
      memcpy(&sys, "INJ", 3);
      break;
    default:
      memcpy(&sys, "???", 3);
  }
  lv_label_set_text_fmt(ui_debugStatus, "bench%s%d send status: %s", sys, index, ret ? "OK" : "FAIL");
}

void benchIGN1(lv_event_t *e) {
  bench(0x12, 1);
}

void benchIGN2(lv_event_t *e) {
  bench(0x12, 2);
}

void benchIGN3(lv_event_t *e) {
  bench(0x12, 3);
}

void benchIGN4(lv_event_t *e) {
  bench(0x12, 4);
}

void benchIGN5(lv_event_t *e) {
  bench(0x12, 5);
}

void benchIGN6(lv_event_t *e) {
  bench(0x12, 6);
}

void benchIGN7(lv_event_t *e) {
  bench(0x12, 7);
}

void benchIGN8(lv_event_t *e) {
  bench(0x12, 8);
}

void benchINJ1(lv_event_t *e) {
  bench(0x13, 1);
}

void benchINJ2(lv_event_t *e) {
  bench(0x13, 2);
}

void benchINJ3(lv_event_t *e) {
  bench(0x13, 3);
}

void benchINJ4(lv_event_t *e) {
  bench(0x13, 4);
}

void benchINJ5(lv_event_t *e) {
  bench(0x13, 5);
}

void benchINJ6(lv_event_t *e) {
  bench(0x13, 6);
}

void benchINJ7(lv_event_t *e) {
  bench(0x13, 7);
}

void benchINJ8(lv_event_t *e) {
  bench(0x13, 8);
}

void StartStop(lv_event_t *e) {
}

void benchFuelPump(lv_event_t *e) {
}

void benchFan2(lv_event_t *e) {
}

void benchFan1(lv_event_t *e) {
}

void rpmWarnSetPlus(lv_event_t *e) {
  rpmWarnSet(true);
}

void rpmWarnSetMinus(lv_event_t *e) {
  rpmWarnSet(false);
}

void cltWarnSetPlus(lv_event_t *e) {
  cltWarnSet(true);
}

void cltWarnSetMinus(lv_event_t *e) {
  cltWarnSet(false);
}

void iatWarnSetPlus(lv_event_t *e) {
  iatWarnSet(true);
}

void iatWarnSetMinus(lv_event_t *e) {
  iatWarnSet(false);
}

void oilTWarnSetPlus(lv_event_t *e) {
  oilTWarnSet(true);
}

void oilTWarnSetMinus(lv_event_t *e) {
  oilTWarnSet(false);
}

void oilPWarnSetPlus(lv_event_t *e) {
  oilPWarnSet(true);
}

void oilPWarnSetMinus(lv_event_t *e) {
  oilPWarnSet(false);
}

void fuelPWarnSetPlus(lv_event_t *e) {
  fuelPWarnSet(true);
}

void fuelPWarnSetMinus(lv_event_t *e) {
  fuelPWarnSet(false);
}

void vBattWarnSetPlus(lv_event_t *e) {
  vBattWarnSet(true);
}

void vBattWarnSetMinus(lv_event_t *e) {
  vBattWarnSet(false);
}

void setIsTurbo(lv_event_t *e) {
  setTurbo();
}

void setIsNaturalA(lv_event_t *e) {
  setNA();
}

void saveWarnSet(lv_event_t *e) {
  updateWarningsSet();
}

void defaultWarnSet(lv_event_t *e) {
  setDefaultWarnSet();
}

void preInitSettingsSceen(lv_event_t *e) {
  preInitWarnScreen();
}
