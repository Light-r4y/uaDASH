#pragma once

#include "ui.h"
#include "config.h"
#include "twai_lib.h"
#include "mutex.h"
#include <Ticker.h>
#include <Preferences.h>
#include "build_info.h"

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

typedef struct warning_set {
  int rpm;
  int clt;
  int iat;
  int oilTemp;
  int oilPress;
  int fuelPress;
  bool isTurbo;
  float vBatt;
} warning_set;

typedef struct engine_set {
  uint8_t displacement;
  uint8_t trigger;
  uint8_t camshape;
} engine_set;

volatile static struct_message myData;
volatile static struct_message old_myData;
volatile static warning_set warningSet;
volatile static engine_set engineConfig;
volatile static bool changeMapWidget;
volatile static bool canEngineConfig;
volatile static bool checkEngineConfig;

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

  void getWarningsSet();
  void updateWarningsSet();
  void preInitWarnScreen(bool def = false);
  void setDefaultWarnSet();
  void setTurbo();
  void setNA();
  void rpmWarnSet(bool up);
  void cltWarnSet(bool up);
  void iatWarnSet(bool up);
  void oilTWarnSet(bool up);
  void oilPWarnSet(bool up);
  void fuelPWarnSet(bool up);
  void vBattWarnSet(bool up);
  void benchScreenSetup();
  void engineSettingScreenSettup();
  void engSet();
  void setEngDisp(int engDisp);
  void setCheckBoxDisplacement();
  void setCheckBoxTrigger();
  void setCheckBoxCamshape();
  void setEngTrig(int trig);
  void setEngCamS(int cams);
  void clearEngConf();
  void clearCheckBoxDisplacement();
  void clearCheckBoxTrig();
  void clearCheckBoxCamS();

#ifdef __cplusplus
} /*extern "C"*/
#endif
