#pragma once

#include "ui.h"
#include "config.h"
#include "twai_lib.h"
#include "mutex.h"
#include <Ticker.h>
#include <Preferences.h>
#include "build_info.h"
#include "can_common.h"

// Updaters tikers
#define PERIOD_FAST_MS 20
#define PERIOD_MID_MS 200
#define PERIOD_SLOW_MS 800
#define PERIOD_HEARTBEAT_MS 500


#define DEF_WARN_RPM 600
#define DEF_WARN_OIL_P 180
#define DEF_WARN_FUEL_P 250
#define DEF_WARN_OIL_T 110
#define DEF_WARN_CLT 102
#define DEF_WARN_IAT 40
#define DEF_WARN_VBATT 12.5
#define DEF_IS_TURBO false


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
// volatile static warning_set warningSet;
// volatile static bool changeMapWidget;

extern ESP32S3_TWAI can;
extern Preferences preferences;
#ifdef __cplusplus
extern "C" {
#endif

  void TaskCANReceiver(void *pvParameters);
  void TaskHeartbeat(void *pvParameters);
  void fastUpdate();
  void midUpdate();
  void slowUpdate();

  void benchScreenSetup();
#ifdef __cplusplus
} /*extern "C"*/
#endif
