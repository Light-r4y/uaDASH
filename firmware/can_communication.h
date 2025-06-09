#ifndef CAN_COMMUNICATION_H
#define CAN_COMMUNICATION_H

// Pins used to connect to CAN bus transceiver:
#define RX_PIN GPIO_NUM_18  // 18
#define TX_PIN GPIO_NUM_17  // 17

// CAN Interval:
#define POLLING_RATE_MS 50

// Updaters tikers
#define PERIOD_FAST_MS 20
#define PERIOD_MID_MS 200
#define PERIOD_SLOW_MS 800

typedef struct struct_message {
  int rpm;
  int speed;
  int clt;
  int iat;
  float afr;
  float Vbat;
  int fuelLevel;
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

#endif  // HEADER