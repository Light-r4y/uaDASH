#include "updaters.h"
#include "display_driver.h"

void upBrightness(lv_event_t *e) {
  setBrightness(brightnessVal + 40);
}

void downBribrightness(lv_event_t *e) {
  setBrightness(brightnessVal - 40);
}

// uint8_t data[] = { 0x66, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint8_t data[] = { bench_test_magic_numbers_e::BENCH_HEADER, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

void bench(uint8_t subsys, uint8_t index) {
  data[2] = subsys;
  data[4] = index;
  // bool ret = can.send(0x77000C, data, sizeof(data), true);
  bool ret = can.send(bench_test_packet_ids_e::ECU_CAN_BUS_USER_CONTROL, data, sizeof(data), true);
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
  // uint8_t data[] = { 0x66, 0x00, 0x14, 0x00, 0x09, 0x00 };
  uint8_t data[] = { bench_test_magic_numbers_e::BENCH_HEADER, 0x00, 0x14, 0x00, 0x09, 0x00 };
  // 0x77000C 0x66 0x00 0x14 0x00 0x09 0x00 start/stop engine
  // bool ret = can.send(0x77000C, data, sizeof(data), true);
  bool ret = can.send(bench_test_packet_ids_e::ECU_CAN_BUS_USER_CONTROL, data, sizeof(data), true); 
  lv_label_set_text_fmt(ui_debugStatus, "Engine Start/stop send status: %s", ret ? "OK" : "FAIL");
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

void preInitSettingsScreen(lv_event_t *e) {
  preInitWarnScreen();
}

void engSetSave(lv_event_t *e) {
  engSet();
}

void benchScreenInitSetup(lv_event_t *e) {
  benchScreenSetup();
}

void engineSettingScreenInitSettup(lv_event_t *e) {
  engineSettingScreenSettup();
}

void clearEngConfiguration(lv_event_t * e){
  clearEngConf();
}

void setDisp48L(lv_event_t *e) {
  setEngDisp(48);
}
void setDisp53L(lv_event_t *e) {
  setEngDisp(53);
}
void setDisp57L(lv_event_t *e) {
  setEngDisp(57);
}
void setDisp60L(lv_event_t *e) {
  setEngDisp(60);
}
void setDisp62L(lv_event_t *e) {
  setEngDisp(62);
}
void setDisp70L(lv_event_t *e) {
  setEngDisp(70);
}
void setTrig24(lv_event_t *e) {
  setEngTrig(24);
}
void setTrig58(lv_event_t *e) {
  setEngTrig(58);
}
void setCamS1(lv_event_t *e) {
  setEngCamS(1);
}
void setCamS2(lv_event_t *e) {
  setEngCamS(2);
}
void setCamS4(lv_event_t *e) {
  setEngCamS(4);
}