#include "updaters.h"
#include "display_driver.h"

void upBrightness(lv_event_t *e) {
  setBrightness(brightnessVal + 40);
}

void downBribrightness(lv_event_t *e) {
  setBrightness(brightnessVal - 40);
}

uint8_t data[] = { 0x66, 0x00, 0x00, 0xBB };

void benchIGN1(lv_event_t *e) {
  bool ret = can.send(0x77000C, data, sizeof(data), true);
  lv_label_set_text_fmt(ui_debugStatus, "benchIGN1 send status: %s", ret ? "OK" : "FAIL");
#ifdef DEBUG
  Serial.println("benchIGN1");
#endif
}

void benchIGN2(lv_event_t *e) {
  bool ret = can.send(0x77000C, data, sizeof(data), true);
  lv_label_set_text_fmt(ui_debugStatus, "benchIGN2 send status: %s", ret ? "OK" : "FAIL");
}

void benchIGN3(lv_event_t *e) {
  bool ret = can.send(0x77000C, data, sizeof(data), true);
  lv_label_set_text_fmt(ui_debugStatus, "benchIGN3 send status: %s", ret ? "OK" : "FAIL");
}

void benchIGN4(lv_event_t *e) {
  bool ret = can.send(0x77000C, data, sizeof(data), true);
  lv_label_set_text_fmt(ui_debugStatus, "benchIGN4 send status: %s", ret ? "OK" : "FAIL");
}

void benchIGN5(lv_event_t *e) {
  bool ret = can.send(0x77000C, data, sizeof(data), true);
  lv_label_set_text_fmt(ui_debugStatus, "benchIGN5 send status: %s", ret ? "OK" : "FAIL");
}

void benchIGN6(lv_event_t *e) {
  bool ret = can.send(0x77000C, data, sizeof(data), true);
  lv_label_set_text_fmt(ui_debugStatus, "benchIGN6 send status: %s", ret ? "OK" : "FAIL");
}

void benchIGN7(lv_event_t *e) {
  bool ret = can.send(0x77000C, data, sizeof(data), true);
  lv_label_set_text_fmt(ui_debugStatus, "benchIGN7 send status: %s", ret ? "OK" : "FAIL");
}

void benchIGN8(lv_event_t *e) {
  bool ret = can.send(0x77000C, data, sizeof(data), true);
  lv_label_set_text_fmt(ui_debugStatus, "benchIGN8 send status: %s", ret ? "OK" : "FAIL");
}

void benchINJ1(lv_event_t *e) {
  bool ret = can.send(0x77000C, data, sizeof(data), true);
  lv_label_set_text_fmt(ui_debugStatus, "benchINJ1 send status: %s", ret ? "OK" : "FAIL");
}

void benchINJ2(lv_event_t *e) {
  bool ret = can.send(0x77000C, data, sizeof(data), true);
  lv_label_set_text_fmt(ui_debugStatus, "benchINJ2 send status: %s", ret ? "OK" : "FAIL");
}

void benchINJ3(lv_event_t *e) {
  bool ret = can.send(0x77000C, data, sizeof(data), true);
  lv_label_set_text_fmt(ui_debugStatus, "benchINJ3 send status: %s", ret ? "OK" : "FAIL");
}

void benchINJ4(lv_event_t *e) {
  bool ret = can.send(0x77000C, data, sizeof(data), true);
  lv_label_set_text_fmt(ui_debugStatus, "benchINJ4 send status: %s", ret ? "OK" : "FAIL");
}

void benchINJ5(lv_event_t *e) {
  bool ret = can.send(0x77000C, data, sizeof(data), true);
  lv_label_set_text_fmt(ui_debugStatus, "benchINJ5 send status: %s", ret ? "OK" : "FAIL");
}

void benchINJ6(lv_event_t *e) {
  bool ret = can.send(0x77000C, data, sizeof(data), true);
  lv_label_set_text_fmt(ui_debugStatus, "benchINJ6 send status: %s", ret ? "OK" : "FAIL");
}

void benchINJ7(lv_event_t *e) {
  bool ret = can.send(0x77000C, data, sizeof(data), true);
  lv_label_set_text_fmt(ui_debugStatus, "benchINJ7 send status: %s", ret ? "OK" : "FAIL");
}

void benchINJ8(lv_event_t *e) {
  bool ret = can.send(0x77000C, data, sizeof(data), true);
  lv_label_set_text_fmt(ui_debugStatus, "benchINJ8 send status: %s", ret ? "OK" : "FAIL");
}

void StartStop(lv_event_t *e) {
  bool ret = can.send(0x77000C, data, sizeof(data), true);
  lv_label_set_text_fmt(ui_debugStatus, "StartStop send status: %s", ret ? "OK" : "FAIL");
}

void benchFuelPump(lv_event_t *e) {
  bool ret = can.send(0x77000C, data, sizeof(data), true);
  lv_label_set_text_fmt(ui_debugStatus, "benchFuelPump send status: %s", ret ? "OK" : "FAIL");
}

void benchFan2(lv_event_t *e) {
  bool ret = can.send(0x77000C, data, sizeof(data), true);
  lv_label_set_text_fmt(ui_debugStatus, "benchFan2 send status: %s", ret ? "OK" : "FAIL");
}

void benchFan1(lv_event_t *e) {
  bool ret = can.send(0x77000C, data, sizeof(data), true);
  lv_label_set_text_fmt(ui_debugStatus, "benchFan1 send status: %s", ret ? "OK" : "FAIL");
}