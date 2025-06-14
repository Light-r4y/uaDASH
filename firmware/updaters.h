#pragma once

#include "ui.h"
#include "config.h"
#include "twai_lib.h"
#include "mutex.h"
#include <Ticker.h>

// Updaters tikers
#define PERIOD_FAST_MS 20
#define PERIOD_MID_MS 200
#define PERIOD_SLOW_MS 800

typedef struct struct_message {
  int rpm;
  int speed;
  int clt;
  int iat;
  int oilTemp;
  int fuelLevel;
  float afr;
  float Vbat;
  float map;
  float oilPress;
  float fuelPress;
  // bool mainRelay;
  // bool fuelPump;
  // bool fan1;
  // bool fan2;
} struct_message;

volatile static struct_message myData;
volatile static struct_message old_myData;

extern ESP32S3_TWAI can;
#ifdef __cplusplus
extern "C" {
#endif

void TaskCANReceiver(void *pvParameters);
void fastUpdate();
void midUpdate();
void slowUpdate();

#ifdef __cplusplus
} /*extern "C"*/
#endif
