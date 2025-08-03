#include "updaters.h"

ESP32S3_TWAI can;
Preferences preferences;

void TaskHeartbeat(void *pvParameters) {
  uint8_t data[] = { 0x66, 0x00, 0x55, 0xAA, 0x00 };
  uint8_t countHeartbeat = 0;
  while (1) {
    data[4] = countHeartbeat;
    // 0x77000D 0x66 0x00 0x5500 0xAA count -- heartbeat
    can.send(0x77000F, data, sizeof(data), true);
    countHeartbeat++;
    vTaskDelay(pdMS_TO_TICKS(PERIOD_HEARTBEAT_MS));
  }
}

void TaskCANReceiver(void *pvParameters) {
  uint32_t id;
  uint8_t data[8];
  uint8_t length;
  bool extended;

  Ticker updateUiFast;
  Ticker updateUiMid;
  Ticker updateUiSlow;

  getWarningsSet();
  changeMapWidget = true;
  canEngineConfig = false;
  checkEngineConfig = true;

  bool ret = false;
#ifdef DEBUG
  Serial.println("TaskCANReceiver init");
#endif

  while (!ret) {
    ret = can.init();
#ifdef DEBUG
    Serial.printf("can.init : %s\n", ret ? "OK" : "FAIL");
#endif
  }

  ret = can.alertConfigure();
#ifdef DEBUG
  Serial.printf("can.alertConfigure : %s\n", ret ? "OK" : "FAIL");
#endif

  updateUiFast.attach_ms(PERIOD_FAST_MS, fastUpdate);
  updateUiMid.attach_ms(PERIOD_MID_MS, midUpdate);
  updateUiSlow.attach_ms(PERIOD_SLOW_MS, slowUpdate);

  while (1) {
    // // Check if message is received
    if (can.getAlerts()) {
      // One or more messages received. Handle all.
      while (can.receive(&id, data, &length, &extended)) {
        if (extended && checkEngineConfig) {
#ifdef DEBUG
          Serial.printf("receive ext: %s\n", extended ? "yes" : "no");
#endif
          if (id == 0x77000D) {
            if (data[0] == 0x66) {
              canEngineConfig = true;
              checkEngineConfig = false;
              engineConfig.displacement = data[2];
              engineConfig.trigger = data[3];
              engineConfig.camshape = data[4];
            }
          }
        }
        //  ID 0x200
        // SG_ WarningCounter : 0|16@1+ (1,0) [0|0] "" Vector__XXX
        // SG_ LastError : 16|16@1+ (1,0) [0|0] "" Vector__XXX
        // SG_ RevLimAct : 32|1@1+ (1,0) [0|0] "" Vector__XXX
        // SG_ MainRelayAct : 33|1@1+ (1,0) [0|0] "" Vector__XXX
        // SG_ FuelPumpAct : 34|1@1+ (1,0) [0|0] "" Vector__XXX
        // SG_ CELAct : 35|1@1+ (1,0) [0|0] "" Vector__XXX
        // SG_ EGOHeatAct : 36|1@1+ (1,0) [0|0] "" Vector__XXX
        // SG_ LambdaProtectAct : 37|1@1+ (1,0) [0|0] "" Vector__XXX
        // SG_ CurrentGear : 40|8@1+ (1,0) [0|0] "" Vector__XXX
        // SG_ DistanceTraveled : 48|16@1+ (0.1,0) [0|6553.5] "km" Vector__XXX
        // SG_ Fan : 38|1@1+ (1,0) [0|0] "" Vector__XXX
        // SG_ Fan2 : 39|1@1+ (1,0) [0|0] "" Vector__XXX

        //  ID 0x201
        //  SG_ RPM : 0|16@1+ (1,0) [0|0] "RPM" Vector__XXX
        //  SG_ IgnitionTiming : 16|16@1- (0.02,0) [0|0] "deg" Vector__XXX
        //  SG_ InjDuty : 32|8@1+ (0.5,0) [0|100] "%" Vector__XXX
        //  SG_ IgnDuty : 40|8@1+ (0.5,0) [0|100] "%" Vector__XXX
        //  SG_ VehicleSpeed : 48|8@1+ (1,0) [0|255] "kph" Vector__XXX
        //  SG_ FlexPct : 56|8@1+ (1,0) [0|100] "%" Vector__XXX

        //  ID 0x202
        //  SG_ PPS : 0|16@1- (0.01,0) [0|100] "%" Vector__XXX
        //  SG_ TPS1 : 16|16@1- (0.01,0) [0|100] "%" Vector__XXX
        //  SG_ TPS2 : 32|16@1- (0.01,0) [0|100] "%" Vector__XXX
        //  SG_ Wastegate : 48|16@1- (0.01,0) [0|100] "%" Vector__XXX

        //  ID 0x203
        //  SG_ MAP : 0|16@1+ (0.03333333,0) [0|0] "kPa" Vector__XXX
        //  SG_ CoolantTemp : 16|8@1+ (1,-40) [-40|200] "deg C" Vector__XXX
        //  SG_ IntakeTemp : 24|8@1+ (1,-40) [-40|200] "deg C" Vector__XXX
        //  SG_ AUX1Temp : 32|8@1+ (1,-40) [-40|200] "deg C" Vector__XXX
        //  SG_ AUX2Temp : 40|8@1+ (1,-40) [-40|200] "deg C" Vector__XXX
        //  SG_ MCUTemp : 48|8@1+ (1,-40) [-40|100] "deg C" Vector__XXX
        //  SG_ FuelLevel : 56|8@1+ (0.5,0) [0|0] "%" Vector__XXX

        //  ID 0x204
        //  SG_ OilPress : 16|16@1+ (0.03333333,0) [0|0] "kPa" Vector__XXX
        //  SG_ OilTemperature : 32|8@1+ (1,-40) [-40|215] "deg C" Vector__XXX
        //  SG_ FuelTemperature : 40|8@1+ (1,-40) [-40|215] "deg C" Vector__XXX
        //  SG_ BattVolt : 48|16@1+ (0.001,0) [0|25] "mV" Vector__XXX

        //  ID 0x207
        //  SG_ Lam1 : 0|16@1+ (0.0001,0) [0|2] "lambda" Vector__XXX
        //  SG_ Lam2 : 16|16@1+ (0.0001,0) [0|2] "lambda" Vector__XXX
        //  SG_ FpLow : 32|16@1+ (0.03333333,0) [0|0] "kPa" Vector__XXX
        //  SG_ FpHigh : 48|16@1+ (0.1,0) [0|0] "bar" Vector__XXX
        if (xSemaphoreTake(dataMutex, portMAX_DELAY) == pdTRUE) {

          switch (id) {
            case 0x201:
              myData.rpm = (data[1] << 8 | data[0]);
              myData.speed = data[6];
              break;
            case 0x203:
              myData.map = (data[1] << 8 | data[0]) * 0.0333;
              myData.clt = data[2] - 40;
              myData.iat = data[3] - 40;
              myData.fuelLevel = data[7] / 2;
              break;
            case 0x204:
              myData.oilPress = (data[3] << 8 | data[2]) * 0.0333;
              myData.oilTemp = data[4] - 40;
              myData.Vbat = (data[7] << 8 | data[6]) * 0.001;
              break;
            case 0x207:
              myData.afr = (data[1] << 8 | data[0]) * 0.00147;
              myData.fuelPress = (data[5] << 8 | data[4]) * 0.0333;
              break;
          }
          xSemaphoreGive(dataMutex);
        }
      }
    }
    vTaskDelay(pdMS_TO_TICKS(5));
  }
}

// Widget updaters
void fastUpdate() {
  if (xSemaphoreTake(dataMutex, portMAX_DELAY) == pdTRUE) {
#ifdef DEBUG
    // Serial.println("fastUpdate");
#endif
    if (xSemaphoreTake(uiMutex, portMAX_DELAY) == pdTRUE) {
      // RPM
      if (myData.rpm != old_myData.rpm) {
        if (myData.rpm == 0) {
          lv_label_set_text(ui_rpmVal0, "0");
          lv_bar_set_value(ui_rpmBar0, 0, LV_ANIM_OFF);
        } else {
          int val = myData.rpm / 10;
          lv_bar_set_value(ui_rpmBar0, val, LV_ANIM_OFF);
          if (val > warningSet.rpm) {
            lv_obj_set_style_bg_color(ui_rpmBar0, lv_color_hex(0xFF0000), LV_PART_INDICATOR | LV_STATE_DEFAULT);
          } else {
            lv_obj_set_style_bg_color(ui_rpmBar0, lv_color_hex(0xE0FF00), LV_PART_INDICATOR | LV_STATE_DEFAULT);
          }
          lv_label_set_text_fmt(ui_rpmVal0, "%d0", val);
        }
        old_myData.rpm = myData.rpm;
      }
      // MAP
      if (myData.map != old_myData.map) {
        if (warningSet.isTurbo) {
          float d_map = myData.map / 100;
          if (d_map >= 0) {
            lv_obj_set_style_bg_color(ui_mapBar0, lv_color_hex(0xE0FF00), LV_PART_INDICATOR | LV_STATE_DEFAULT);
          } else {
            lv_obj_set_style_bg_color(ui_mapBar0, lv_color_hex(0x01FF71), LV_PART_INDICATOR | LV_STATE_DEFAULT);
          }
          lv_label_set_text_fmt(ui_mapVal0, "%.2f", d_map);
        } else {
          lv_label_set_text_fmt(ui_mapVal0, "%.0f", myData.map);
        }
        lv_bar_set_value(ui_mapBar0, myData.map - 100, LV_ANIM_OFF);
        old_myData.map = myData.map;
      }
      // AFR
      if (myData.afr != old_myData.afr) {
        int l_bar = myData.afr * 10 - 150;
        lv_bar_set_value(ui_afrBar0, l_bar, LV_ANIM_OFF);
        lv_label_set_text_fmt(ui_afrVal0, "%0.1f", myData.afr);

        if ((l_bar > 10) || (l_bar < -25)) {
          lv_obj_set_style_bg_color(ui_afrBar0, lv_color_hex(0xFF0000), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        } else if (l_bar > 0) {
          lv_obj_set_style_bg_color(ui_afrBar0, lv_color_hex(0x00FFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        } else {
          lv_obj_set_style_bg_color(ui_afrBar0, lv_color_hex(0xE0FF00), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        old_myData.afr = myData.afr;
      }
      xSemaphoreGive(uiMutex);
    }
    xSemaphoreGive(dataMutex);
  }
}

void midUpdate() {
  if (xSemaphoreTake(dataMutex, portMAX_DELAY) == pdTRUE) {
#ifdef DEBUG
    // Serial.println("midUpdate");
#endif
    if (xSemaphoreTake(uiMutex, portMAX_DELAY) == pdTRUE) {
      // VSS
      if (myData.speed != old_myData.speed) {
        lv_label_set_text_fmt(ui_speedVal0, "%d", myData.speed);
        old_myData.speed = myData.speed;
      }
      // OIL Press
      if (myData.oilPress != old_myData.oilPress) {
        lv_bar_set_value(ui_oilPressBar0, myData.oilPress, LV_ANIM_ON);
        lv_label_set_text_fmt(ui_oilPressVal0, "%.1f", myData.oilPress / 100);
        if (myData.oilPress > warningSet.oilPress) {
          lv_obj_set_style_bg_color(ui_oilPressBar0, lv_color_hex(0xE6FF00), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        } else {
          lv_obj_set_style_bg_color(ui_oilPressBar0, lv_color_hex(0xFF0000), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        old_myData.oilPress = myData.oilPress;
      }
      // Fuel Press
      if (myData.fuelPress != old_myData.fuelPress) {
        lv_bar_set_value(ui_fuelPressBar0, myData.fuelPress, LV_ANIM_ON);  /// set low press
        lv_label_set_text_fmt(ui_fuelPressVal0, "%.1f", myData.fuelPress / 100);
        if (myData.fuelPress > warningSet.fuelPress) {
          lv_obj_set_style_bg_color(ui_fuelPressBar0, lv_color_hex(0xE6FF00), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        } else {
          lv_obj_set_style_bg_color(ui_fuelPressBar0, lv_color_hex(0xFF0000), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        old_myData.fuelPress = myData.fuelPress;
      }
      xSemaphoreGive(uiMutex);
    }
    xSemaphoreGive(dataMutex);
  }
}

void slowUpdate() {
  if (changeMapWidget) {
    if (warningSet.isTurbo) {
      lv_label_set_text(ui_mapLabel1, "boost");
      lv_bar_set_range(ui_mapBar0, -100, 300);
      lv_label_set_text(ui_LabelMapMax, "3");
      lv_obj_clear_flag(ui_LabelMapT0, LV_OBJ_FLAG_HIDDEN);
      lv_label_set_text(ui_LabelMapMid, "1");
      lv_obj_clear_flag(ui_LabelMapT2, LV_OBJ_FLAG_HIDDEN);
      lv_label_set_text(ui_LabelMapMin, "-1");
      lv_label_set_text_fmt(ui_mapVal0, "%.2f", myData.map / 100);
    } else {
      lv_label_set_text(ui_mapLabel1, "map");
      lv_bar_set_range(ui_mapBar0, -100, 0);
      lv_label_set_text(ui_LabelMapMax, "100");
      lv_obj_add_flag(ui_LabelMapT0, LV_OBJ_FLAG_HIDDEN);
      lv_label_set_text(ui_LabelMapMid, "50");
      lv_obj_add_flag(ui_LabelMapT2, LV_OBJ_FLAG_HIDDEN);
      lv_label_set_text(ui_LabelMapMin, "0");
      lv_label_set_text_fmt(ui_mapVal0, "%.0f", myData.map);
    }
    changeMapWidget = false;
  }

  if (xSemaphoreTake(dataMutex, portMAX_DELAY) == pdTRUE) {
#ifdef DEBUG
    // Serial.println("slowUpdate");
#endif
    if (xSemaphoreTake(uiMutex, portMAX_DELAY) == pdTRUE) {
      // CLT
      if (myData.clt != old_myData.clt) {
        lv_bar_set_value(ui_cltBar0, myData.clt, LV_ANIM_ON);
        lv_label_set_text_fmt(ui_cltVal0, "%d", myData.clt);
        if (myData.clt < warningSet.clt) {
          lv_obj_set_style_bg_color(ui_cltBar0, lv_color_hex(0xE6FF00), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        } else {
          lv_obj_set_style_bg_color(ui_cltBar0, lv_color_hex(0xFF0000), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        old_myData.clt = myData.clt;
      }
      // IAT
      if (myData.iat != old_myData.iat) {
        lv_bar_set_value(ui_iatBar0, myData.iat, LV_ANIM_ON);
        lv_label_set_text_fmt(ui_iatVal0, "%d", myData.iat);
        if (myData.iat < warningSet.iat) {
          lv_obj_set_style_bg_color(ui_iatBar0, lv_color_hex(0xE6FF00), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        } else {
          lv_obj_set_style_bg_color(ui_iatBar0, lv_color_hex(0xFF0000), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        old_myData.iat = myData.iat;
      }
      // OIL T
      if (myData.oilTemp != old_myData.oilTemp) {
        lv_bar_set_value(ui_oilTempBar0, myData.oilTemp, LV_ANIM_ON);
        lv_label_set_text_fmt(ui_oilTempVal1, "%d", myData.oilTemp);
        if (myData.oilTemp < warningSet.oilTemp) {
          lv_obj_set_style_bg_color(ui_oilTempBar0, lv_color_hex(0xE6FF00), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        } else {
          lv_obj_set_style_bg_color(ui_oilTempBar0, lv_color_hex(0xFF0000), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        old_myData.oilTemp = myData.oilTemp;
      }
      // Vbat
      if (myData.Vbat != old_myData.Vbat) {
        if (myData.Vbat < warningSet.vBatt) {
          lv_obj_set_style_text_color(ui_vBattVal0, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
        } else {
          lv_obj_set_style_text_color(ui_vBattVal0, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        lv_label_set_text_fmt(ui_vBattVal0, "%.1f", myData.Vbat);
        old_myData.Vbat = myData.Vbat;
      }
      // Fuel level
      if (myData.fuelLevel != old_myData.fuelLevel) {
        lv_bar_set_value(ui_fuelLevelBar0, myData.fuelLevel, LV_ANIM_ON);
        lv_label_set_text_fmt(ui_fuelLevelVal0, "%d", myData.fuelLevel);
        if (myData.fuelLevel > 15) {
          lv_obj_set_style_bg_color(ui_fuelLevelBar0, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        } else {
          lv_obj_set_style_bg_color(ui_fuelLevelBar0, lv_color_hex(0xFF0000), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        old_myData.fuelLevel = myData.fuelLevel;
      }
      xSemaphoreGive(uiMutex);
    }
    xSemaphoreGive(dataMutex);
  }
}

void getWarningsSet() {
  preferences.begin("warn", true);
  warningSet.rpm = preferences.getInt("rpm", DEF_WARN_RPM);
  warningSet.iat = preferences.getInt("iat", DEF_WARN_IAT);
  warningSet.clt = preferences.getInt("clt", DEF_WARN_CLT);
  warningSet.oilTemp = preferences.getInt("oilT", DEF_WARN_OIL_T);
  warningSet.oilPress = preferences.getInt("oilP", DEF_WARN_OIL_P);
  warningSet.fuelPress = preferences.getInt("fuelP", DEF_WARN_FUEL_P);
  warningSet.vBatt = preferences.getFloat("vBatt", DEF_WARN_VBATT);
  warningSet.isTurbo = preferences.getBool("turbo", DEF_IS_TURBO);
  preferences.end();
#ifdef DEBUG
  Serial.printf("getWarningsSet > rpm: %d, iat: %d, clt: %d, oilT: %d, oilP: %d, fuelP: %d, vB: %0.1f, isTurbo: %d\n",
                warningSet.rpm, warningSet.iat, warningSet.clt, warningSet.oilTemp,
                warningSet.oilPress, warningSet.fuelPress, warningSet.vBatt, warningSet.isTurbo);
#endif
}

void updateWarningsSet() {
#ifdef DEBUG
  Serial.println("updateWarningsSet> start");
#endif

  preferences.begin("warn", false);

  if (warningSet.rpm != preferences.getInt("rpm", DEF_WARN_RPM)) {
    preferences.putInt("rpm", warningSet.rpm);
#ifdef DEBUG
    Serial.println("updateWarningsSet> warningSet.rpm");
#endif
  }
  if (warningSet.iat != preferences.getInt("iat", DEF_WARN_IAT)) {
    preferences.putInt("iat", warningSet.iat);
#ifdef DEBUG
    Serial.println("updateWarningsSet> warningSet.iat");
#endif
  }
  if (warningSet.clt != preferences.getInt("clt", DEF_WARN_CLT)) {
    preferences.putInt("clt", warningSet.clt);
#ifdef DEBUG
    Serial.println("updateWarningsSet> warningSet.clt");
#endif
  }
  if (warningSet.oilTemp != preferences.getInt("oilT", DEF_WARN_OIL_T)) {
    preferences.putInt("oilT", warningSet.oilTemp);
#ifdef DEBUG
    Serial.println("updateWarningsSet> warningSet.oilTemp");
#endif
  }
  if (warningSet.oilPress != preferences.getInt("oilP", DEF_WARN_OIL_P)) {
    preferences.putInt("oilP", warningSet.oilPress);
#ifdef DEBUG
    Serial.println("updateWarningsSet> warningSet.oilPress");
#endif
  }
  if (warningSet.fuelPress != preferences.getInt("fuelP", DEF_WARN_FUEL_P)) {
    preferences.putInt("fuelP", warningSet.fuelPress);
#ifdef DEBUG
    Serial.println("updateWarningsSet> warningSet.fuelPress");
#endif
  }
  if (warningSet.vBatt != preferences.getFloat("vBatt", DEF_WARN_VBATT)) {
    preferences.putFloat("vBatt", warningSet.vBatt);
#ifdef DEBUG
    Serial.println("updateWarningsSet> warningSet.vBatt");
#endif
  }
  if (warningSet.isTurbo != preferences.getBool("turbo", DEF_IS_TURBO)) {
    preferences.putBool("turbo", warningSet.isTurbo);
#ifdef DEBUG
    Serial.println("updateWarningsSet> warningSet.isTurbo");
#endif
  }
  preferences.end();
}

void preInitWarnScreen(bool def) {
#ifdef DEBUG
  Serial.println("preInitWarnScreen > start");
#endif
  lv_label_set_text(ui_FWValLabel, DASH_TAG);
  lv_label_set_text_fmt(ui_rpmWarnVal, "%d0", warningSet.rpm);
  lv_label_set_text_fmt(ui_iatWarnVal, "%d", warningSet.iat);
  lv_label_set_text_fmt(ui_cltWarnVal, "%d", warningSet.clt);
  lv_label_set_text_fmt(ui_oilTWarnVal, "%d", warningSet.oilTemp);
  lv_label_set_text_fmt(ui_oilPWarnVal, "%.1f", warningSet.oilPress / 100.0);
  lv_label_set_text_fmt(ui_fuelPWarnVal, "%.1f", warningSet.fuelPress / 100.0);
  lv_label_set_text_fmt(ui_vBattWarnVal, "%.1f", warningSet.vBatt);
  if (warningSet.isTurbo) {
    lv_obj_add_state(ui_turboSwitch, LV_STATE_CHECKED);
#ifdef DEBUG
    Serial.println("add_state: turboSwitch 1");
#endif
  } else {
    lv_obj_clear_state(ui_turboSwitch, LV_STATE_CHECKED);
#ifdef DEBUG
    Serial.println("add_state: turboSwitch 0");
#endif
  }
}

void setDefaultWarnSet() {
  preferences.begin("warn", false);
  preferences.putInt("rpm", DEF_WARN_RPM);
  preferences.putInt("iat", DEF_WARN_IAT);
  preferences.putInt("clt", DEF_WARN_CLT);
  preferences.putInt("oilT", DEF_WARN_OIL_T);
  preferences.putInt("oilP", DEF_WARN_OIL_P);
  preferences.putInt("fuelP", DEF_WARN_FUEL_P);
  preferences.putFloat("vBatt", DEF_WARN_VBATT);
  preferences.putBool("turbo", DEF_IS_TURBO);
  preferences.end();
  preInitWarnScreen(true);
}

void setTurbo() {
#ifdef DEBUG
  Serial.printf("setIsTurbo > start (isTurbo= %d)\n", warningSet.isTurbo);
#endif

  warningSet.isTurbo = true;
  changeMapWidget = true;

#ifdef DEBUG
  Serial.printf("setIsTurbo > end (isTurbo= %d)\n", warningSet.isTurbo);
#endif
}

void setNA() {
#ifdef DEBUG
  Serial.printf("setIsNaturalA > end (isTurbo= %d)\n", warningSet.isTurbo);
#endif

  warningSet.isTurbo = false;
  changeMapWidget = true;

#ifdef DEBUG
  Serial.printf("setIsNaturalA > end (isTurbo= %d)\n", warningSet.isTurbo);
#endif
}

void rpmWarnSet(bool up) {
  if (up) {
    if (warningSet.rpm < 800) {
      warningSet.rpm += 10;
    }
  } else {
    if (warningSet.rpm > 100) {
      warningSet.rpm -= 10;
    }
  }
  lv_label_set_text_fmt(ui_rpmWarnVal, "%d0", warningSet.rpm);
}

void cltWarnSet(bool up) {
  if (up) {
    if (warningSet.clt < 120) {
      warningSet.clt += 1;
    }
  } else {
    if (warningSet.clt > 0) {
      warningSet.clt -= 1;
    }
  }
  lv_label_set_text_fmt(ui_cltWarnVal, "%d", warningSet.clt);
}

void iatWarnSet(bool up) {
  if (up) {
    if (warningSet.iat < 80) {
      warningSet.iat += 1;
    }
  } else {
    if (warningSet.iat > 0) {
      warningSet.iat -= 1;
    }
  }
  lv_label_set_text_fmt(ui_iatWarnVal, "%d", warningSet.iat);
}

void oilTWarnSet(bool up) {
  if (up) {
    if (warningSet.oilTemp < 120) {
      warningSet.oilTemp += 1;
    }
  } else {
    if (warningSet.oilTemp > 0) {
      warningSet.oilTemp -= 1;
    }
  }
  lv_label_set_text_fmt(ui_oilTWarnVal, "%d", warningSet.oilTemp);
}

void oilPWarnSet(bool up) {
  if (up) {
    if (warningSet.oilPress < 500) {
      warningSet.oilPress += 10;
    }
  } else {
    if (warningSet.oilPress > 0) {
      warningSet.oilPress -= 10;
    }
  }
  lv_label_set_text_fmt(ui_oilPWarnVal, "%.1f", warningSet.oilPress / 100.0);
}

void fuelPWarnSet(bool up) {
  if (up) {
    if (warningSet.fuelPress < 500) {
      warningSet.fuelPress += 10;
    }
  } else {
    if (warningSet.fuelPress > 100) {
      warningSet.fuelPress -= 10;
    }
  }
  lv_label_set_text_fmt(ui_fuelPWarnVal, "%.1f", warningSet.fuelPress / 100.0);
}

void vBattWarnSet(bool up) {
  if (up) {
    if (warningSet.vBatt < 16) {
      warningSet.vBatt += 0.1;
    }
  } else {
    if (warningSet.vBatt > 5) {
      warningSet.vBatt -= 0.1;
    }
  }
  lv_label_set_text_fmt(ui_vBattWarnVal, "%.1f", warningSet.vBatt);
}

void benchScreenSetup() {
  if (canEngineConfig) {
    lv_obj_clear_flag(ui_EngSetup, LV_OBJ_FLAG_HIDDEN);
  }
}

void setCheckBoxDisplacement() {
  switch (engineConfig.displacement) {
    case 48:
      lv_obj_add_state(ui_CheckboxDisp48, LV_STATE_CHECKED);
      break;
    case 53:
      lv_obj_add_state(ui_CheckboxDisp53, LV_STATE_CHECKED);
      break;
    case 57:
      lv_obj_add_state(ui_CheckboxDisp57, LV_STATE_CHECKED);
      break;
    case 60:
      lv_obj_add_state(ui_CheckboxDisp60, LV_STATE_CHECKED);
      break;
    case 62:
      lv_obj_add_state(ui_CheckboxDisp62, LV_STATE_CHECKED);
      break;
    case 70:
      lv_obj_add_state(ui_CheckboxDisp70, LV_STATE_CHECKED);
      break;
    default:
      lv_obj_add_state(ui_CheckboxDisp48, LV_STATE_CHECKED);
      engineConfig.displacement = 48;
  }
}

void setCheckBoxTrigger() {
  switch (engineConfig.trigger) {
    case 24:
      lv_obj_add_state(ui_CheckboxTrig24, LV_STATE_CHECKED);
      break;
    case 58:
      lv_obj_add_state(ui_CheckboxTrig58, LV_STATE_CHECKED);
      break;
    default:
      lv_obj_add_state(ui_CheckboxTrig24, LV_STATE_CHECKED);
      engineConfig.trigger = 24;
  }
}

void setCheckBoxCamshape() {
  switch (engineConfig.camshape) {
    case 1:
      lv_obj_add_state(ui_CheckboxCamshape1, LV_STATE_CHECKED);
      break;
    case 2:
      lv_obj_add_state(ui_CheckboxCamshape2, LV_STATE_CHECKED);
      break;
    case 4:
      lv_obj_add_state(ui_CheckboxCamshape4, LV_STATE_CHECKED);
      break;
    default:
      lv_obj_add_state(ui_CheckboxCamshape1, LV_STATE_CHECKED);
      engineConfig.camshape = 1;
  }
}

void engineSettingScreenSettup() {
  setCheckBoxDisplacement();
  setCheckBoxTrigger();
  setCheckBoxCamshape();
}

void clearEngConf() {
  clearCheckBoxDisplacement();
  clearCheckBoxTrig();
  clearCheckBoxCamS();
  checkEngineConfig = true;
}

void engSet() {
  uint8_t data[] = { 0x66, 0x00, 0x00, 0x00, 0x00 };
  // 0x77000E 0x66 0x00 displ trigg camshape  -- setup engine configuraton
  data[2] = engineConfig.displacement;
  data[3] = engineConfig.trigger;
  data[4] = engineConfig.camshape;
  can.send(0x77000E, data, sizeof(data), true);
  checkEngineConfig = true;
}

void clearCheckBoxDisplacement() {
  lv_obj_clear_state(ui_CheckboxDisp48, LV_STATE_CHECKED);
  lv_obj_clear_state(ui_CheckboxDisp53, LV_STATE_CHECKED);
  lv_obj_clear_state(ui_CheckboxDisp57, LV_STATE_CHECKED);
  lv_obj_clear_state(ui_CheckboxDisp60, LV_STATE_CHECKED);
  lv_obj_clear_state(ui_CheckboxDisp62, LV_STATE_CHECKED);
  lv_obj_clear_state(ui_CheckboxDisp70, LV_STATE_CHECKED);
}

void clearCheckBoxTrig() {
  lv_obj_clear_state(ui_CheckboxTrig24, LV_STATE_CHECKED);
  lv_obj_clear_state(ui_CheckboxTrig58, LV_STATE_CHECKED);
}

void clearCheckBoxCamS() {
  lv_obj_clear_state(ui_CheckboxCamshape1, LV_STATE_CHECKED);
  lv_obj_clear_state(ui_CheckboxCamshape2, LV_STATE_CHECKED);
  lv_obj_clear_state(ui_CheckboxCamshape4, LV_STATE_CHECKED);
}

void setEngDisp(int engDisp) {
  clearCheckBoxDisplacement();
  engineConfig.displacement = engDisp;
  setCheckBoxDisplacement();
}

void setEngTrig(int trig) {
  clearCheckBoxTrig();
  engineConfig.trigger = trig;
  setCheckBoxTrigger();
}

void setEngCamS(int cams) {
  clearCheckBoxCamS();
  engineConfig.camshape = cams;
  setCheckBoxCamshape();
}