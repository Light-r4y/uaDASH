#include "updaters.h"

ESP32S3_TWAI can;
Preferences preferences;

void TaskHeartbeat(void *pvParameters)
{
  // uint8_t data[] = { 0x66, 0x00, 0x55, 0xAA, 0x00 };
  uint8_t data[] = {(uint8_t)bench_test_magic_numbers_e::BENCH_HEADER, 0x00, 0x55, 0xAA, 0x00};
  uint8_t countHeartbeat = 0;
  uint32_t error_count = 0;
  while (1)
  {
    data[4] = countHeartbeat;
    // 0x77000F 0x66 0x00 0x55 0xAA count -- heartbeat
    // can.send(0x77000F, data, sizeof(data), true);
    if (false == can.send((uint32_t)bench_test_packet_ids_e::DASH_ALIVE, data, sizeof(data), true))
    {
      error_count++;
#ifdef DEBUG
      Serial.printf("TaskHeartbeat error_count: %d\n", error_count);
#endif
    }
    countHeartbeat++;
    vTaskDelay(pdMS_TO_TICKS(PERIOD_HEARTBEAT_MS));
  }
}

void TaskCANReceiver(void *pvParameters)
{
  uint32_t id;
  uint8_t data[8];
  uint8_t length;
  bool extended;

  Ticker updateUiFast;
  Ticker updateUiMid;
  Ticker updateUiSlow;

  bool ret = false;
#ifdef DEBUG
  Serial.println("TaskCANReceiver init");
#endif

  while (!ret)
  {
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

  while (1)
  {
    // // Check if message is received
    if (can.getAlerts())
    {
      // One or more messages received. Handle all.
      while (can.receive(&id, data, &length, &extended))
      {
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
        if (xSemaphoreTake(dataMutex, portMAX_DELAY) == pdTRUE)
        {

          switch (id)
          {
          case 0x200:
            myData.gear = data[5];
            // myData.speed = data[6];
            break;
          case 0x201:
            myData.rpm = (data[1] << 8 | data[0]);
            // myData.speed = data[6];
            break;
          // case 0x203:
          //   myData.map = (data[1] << 8 | data[0]) * 0.0333;
          //   myData.clt = data[2] - 40;
          //   myData.iat = data[3] - 40;
          //   myData.fuelLevel = data[7] / 2;
          //   break;
          case 0x204:
            // myData.oilPress = (data[3] << 8 | data[2]) * 0.0333;
            // myData.oilTemp = data[4] - 40;
            myData.Vbat = (data[7] << 8 | data[6]) * 0.001;
            break;
            // case 0x207:
            //   myData.afr = (data[1] << 8 | data[0]) * 0.00147;
            //   myData.fuelPress = (data[5] << 8 | data[4]) * 0.0333;
            //   break;
          }
          xSemaphoreGive(dataMutex);
        }
      }
    }
    vTaskDelay(pdMS_TO_TICKS(5));
  }
}

// Widget updaters
void fastUpdate()
{
  if (xSemaphoreTake(dataMutex, portMAX_DELAY) == pdTRUE)
  {
#ifdef DEBUG
    // Serial.println("fastUpdate");
#endif
    if (xSemaphoreTake(uiMutex, portMAX_DELAY) == pdTRUE)
    {
      // RPM
      if (myData.rpm != old_myData.rpm)
      {
        if (myData.rpm == 0)
        {
          lv_label_set_text(ui_rpmVal0, "0");
          lv_img_set_angle(ui_needle, 0);
          // lv_bar_set_value(ui_rpmBar0, 0, LV_ANIM_OFF);
        }
        else
        {
          int val = myData.rpm / 10;
          lv_img_set_angle(ui_needle, val * 3);
          lv_label_set_text_fmt(ui_rpmVal0, "%d0", val);
        }
        old_myData.rpm = myData.rpm;
      }
      // MAP
      // if (myData.map != old_myData.map)
      // {
      // if (warningSet.isTurbo)
      // {
      //   float d_map = (myData.map / 100) - 1.0;
      //   if (d_map >= 0)
      //   {
      //     lv_obj_set_style_bg_color(ui_mapBar0, lv_color_hex(0xE0FF00), LV_PART_INDICATOR | LV_STATE_DEFAULT);
      //   }
      //   else
      //   {
      //     lv_obj_set_style_bg_color(ui_mapBar0, lv_color_hex(0x01FF71), LV_PART_INDICATOR | LV_STATE_DEFAULT);
      //   }
      //   lv_label_set_text_fmt(ui_mapVal0, "%.2f", d_map);
      // }
      // else
      // {
      //   lv_label_set_text_fmt(ui_mapVal0, "%.0f", myData.map);
      // }
      // lv_bar_set_value(ui_mapBar0, myData.map - 100, LV_ANIM_OFF);
      // old_myData.map = myData.map;
      // }
      // AFR
      // if (myData.afr != old_myData.afr)
      // {
      // int l_bar = myData.afr * 10 - 150;
      // lv_bar_set_value(ui_afrBar0, l_bar, LV_ANIM_OFF);
      // lv_label_set_text_fmt(ui_afrVal0, "%0.1f", myData.afr);

      // if ((l_bar > 10) || (l_bar < -25))
      // {
      //   lv_obj_set_style_bg_color(ui_afrBar0, lv_color_hex(0xFF0000), LV_PART_INDICATOR | LV_STATE_DEFAULT);
      // }
      // else if (l_bar > 0)
      // {
      //   lv_obj_set_style_bg_color(ui_afrBar0, lv_color_hex(0x00FFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
      // }
      // else
      // {
      //   lv_obj_set_style_bg_color(ui_afrBar0, lv_color_hex(0xE0FF00), LV_PART_INDICATOR | LV_STATE_DEFAULT);
      // }
      //   old_myData.afr = myData.afr;
      // }
      xSemaphoreGive(uiMutex);
    }
    xSemaphoreGive(dataMutex);
  }
}

void midUpdate()
{
  if (xSemaphoreTake(dataMutex, portMAX_DELAY) == pdTRUE)
  {
#ifdef DEBUG
    // Serial.println("midUpdate");
#endif
    if (xSemaphoreTake(uiMutex, portMAX_DELAY) == pdTRUE)
    {
      // Gear
      if (myData.gear != old_myData.gear)
      {
        if ((myData.gear < 0) && (myData.gear > 9))
        {
          lv_label_set_text(ui_gearVal1, "p");
        }
        else if (myData.gear == 0)
        {
          lv_label_set_text(ui_gearVal1, "n");
        }
        else
        {
          lv_label_set_text_fmt(ui_gearVal1, "%d", myData.gear);
        }
        old_myData.gear = myData.gear;
      }
      // VSS
      // if (myData.speed != old_myData.speed)
      // {
      //   lv_label_set_text_fmt(ui_speedVal0, "%d", myData.speed);
      //   old_myData.speed = myData.speed;
      // }
      // // OIL Press
      // if (myData.oilPress != old_myData.oilPress)
      // {
      //   lv_bar_set_value(ui_oilPressBar0, myData.oilPress, LV_ANIM_ON);
      //   lv_label_set_text_fmt(ui_oilPressVal0, "%.1f", myData.oilPress / 100);
      //   if (myData.oilPress > warningSet.oilPress)
      //   {
      //     lv_obj_set_style_bg_color(ui_oilPressBar0, lv_color_hex(0xE6FF00), LV_PART_INDICATOR | LV_STATE_DEFAULT);
      //   }
      //   else
      //   {
      //     lv_obj_set_style_bg_color(ui_oilPressBar0, lv_color_hex(0xFF0000), LV_PART_INDICATOR | LV_STATE_DEFAULT);
      //   }
      //   old_myData.oilPress = myData.oilPress;
      // }
      // // Fuel Press
      // if (myData.fuelPress != old_myData.fuelPress)
      // {
      //   lv_bar_set_value(ui_fuelPressBar0, myData.fuelPress, LV_ANIM_ON); /// set low press
      //   lv_label_set_text_fmt(ui_fuelPressVal0, "%.1f", myData.fuelPress / 100);
      //   if (myData.fuelPress > warningSet.fuelPress)
      //   {
      //     lv_obj_set_style_bg_color(ui_fuelPressBar0, lv_color_hex(0xE6FF00), LV_PART_INDICATOR | LV_STATE_DEFAULT);
      //   }
      //   else
      //   {
      //     lv_obj_set_style_bg_color(ui_fuelPressBar0, lv_color_hex(0xFF0000), LV_PART_INDICATOR | LV_STATE_DEFAULT);
      //   }
      //   old_myData.fuelPress = myData.fuelPress;
      // }
      xSemaphoreGive(uiMutex);
    }
    xSemaphoreGive(dataMutex);
  }
}

void slowUpdate()
{
  if (xSemaphoreTake(dataMutex, portMAX_DELAY) == pdTRUE)
  {
#ifdef DEBUG
    Serial.println("slowUpdate");
#endif
    if (xSemaphoreTake(uiMutex, portMAX_DELAY) == pdTRUE)
    {
      // // CLT
      // if (myData.clt != old_myData.clt)
      // {
      //   lv_bar_set_value(ui_cltBar0, myData.clt, LV_ANIM_ON);
      //   lv_label_set_text_fmt(ui_cltVal0, "%d", myData.clt);
      //   if (myData.clt < warningSet.clt)
      //   {
      //     lv_obj_set_style_bg_color(ui_cltBar0, lv_color_hex(0xE6FF00), LV_PART_INDICATOR | LV_STATE_DEFAULT);
      //   }
      //   else
      //   {
      //     lv_obj_set_style_bg_color(ui_cltBar0, lv_color_hex(0xFF0000), LV_PART_INDICATOR | LV_STATE_DEFAULT);
      //   }
      //   old_myData.clt = myData.clt;
      // }
      // // IAT
      // if (myData.iat != old_myData.iat)
      // {
      //   lv_bar_set_value(ui_iatBar0, myData.iat, LV_ANIM_ON);
      //   lv_label_set_text_fmt(ui_iatVal0, "%d", myData.iat);
      //   if (myData.iat < warningSet.iat)
      //   {
      //     lv_obj_set_style_bg_color(ui_iatBar0, lv_color_hex(0xE6FF00), LV_PART_INDICATOR | LV_STATE_DEFAULT);
      //   }
      //   else
      //   {
      //     lv_obj_set_style_bg_color(ui_iatBar0, lv_color_hex(0xFF0000), LV_PART_INDICATOR | LV_STATE_DEFAULT);
      //   }
      //   old_myData.iat = myData.iat;
      // }
      // // OIL T
      // if (myData.oilTemp != old_myData.oilTemp)
      // {
      //   lv_bar_set_value(ui_oilTempBar0, myData.oilTemp, LV_ANIM_ON);
      //   lv_label_set_text_fmt(ui_oilTempVal1, "%d", myData.oilTemp);
      //   if (myData.oilTemp < warningSet.oilTemp)
      //   {
      //     lv_obj_set_style_bg_color(ui_oilTempBar0, lv_color_hex(0xE6FF00), LV_PART_INDICATOR | LV_STATE_DEFAULT);
      //   }
      //   else
      //   {
      //     lv_obj_set_style_bg_color(ui_oilTempBar0, lv_color_hex(0xFF0000), LV_PART_INDICATOR | LV_STATE_DEFAULT);
      //   }
      //   old_myData.oilTemp = myData.oilTemp;
      // }
      // Vbat
      if (myData.Vbat != old_myData.Vbat)
      {
        // if (myData.Vbat < warningSet.vBatt)
        // {
        //   lv_obj_set_style_text_color(ui_vBattVal0, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
        // }
        // else
        // {
        //   lv_obj_set_style_text_color(ui_vBattVal0, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
        // }
        lv_label_set_text_fmt(ui_vBattVal0, "%.1f", myData.Vbat);
        old_myData.Vbat = myData.Vbat;
      }
      // // Fuel level
      // if (myData.fuelLevel != old_myData.fuelLevel)
      // {
      //   lv_bar_set_value(ui_fuelLevelBar0, myData.fuelLevel, LV_ANIM_ON);
      //   lv_label_set_text_fmt(ui_fuelLevelVal0, "%d", myData.fuelLevel);
      //   if (myData.fuelLevel > 15)
      //   {
      //     lv_obj_set_style_bg_color(ui_fuelLevelBar0, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
      //   }
      //   else
      //   {
      //     lv_obj_set_style_bg_color(ui_fuelLevelBar0, lv_color_hex(0xFF0000), LV_PART_INDICATOR | LV_STATE_DEFAULT);
      //   }
      //   old_myData.fuelLevel = myData.fuelLevel;
      // }

      lv_label_set_text(ui_FwLabel1, DASH_TAG);
      xSemaphoreGive(uiMutex);
    }
    xSemaphoreGive(dataMutex);
  }
}

void benchScreenSetup()
{
  // if (canEngineConfig)
  // {
  // lv_obj_clear_flag(ui_EngSetup, LV_OBJ_FLAG_HIDDEN);
  // }
}