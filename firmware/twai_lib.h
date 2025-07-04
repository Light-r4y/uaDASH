#ifndef TWAI_LIB_H
#define TWAI_LIB_H

#include <Arduino.h>
#include "config.h"
#include <driver/twai.h>

// Pins used to connect to CAN bus transceiver:
#ifdef JC8048W550C
#define CAN_RX_PIN GPIO_NUM_18
#define CAN_TX_PIN GPIO_NUM_17
#elif defined(WAVESHARE_S3_LCD7)
#define CAN_RX_PIN GPIO_NUM_19  
#define CAN_TX_PIN GPIO_NUM_20
#elif defined(WAVESHARE_S3_LCD5)
#define CAN_RX_PIN GPIO_NUM_16  
#define CAN_TX_PIN GPIO_NUM_15
#else
#error "Please choose LCD type in config.h"
#endif

#define CAN_BAUDRATE    TWAI_TIMING_CONFIG_500KBITS()

#define CAN_FILTER_CODE 0x20000000U << 3
#define CAN_FILTER_MASK 0x007FFFFFU << 3

// CAN Interval:
#define POLLING_RATE_MS 50

#define TWAI_MODE       TWAI_MODE_NORMAL
#define TWAI_FILTER_ONE false

class ESP32S3_TWAI
{
public:
    // Initialize TWAI controller
    bool init(gpio_num_t txPin = (gpio_num_t)CAN_TX_PIN,
              gpio_num_t rxPin = (gpio_num_t)CAN_RX_PIN,
              twai_timing_config_t timing = CAN_BAUDRATE,
              twai_mode_t mode = TWAI_MODE,
              bool useFilter = false,
              uint32_t acceptanceCode = CAN_FILTER_CODE,
              uint32_t acceptanceMask = CAN_FILTER_MASK,
              bool singleFilter = TWAI_FILTER_ONE);

    // Configure alerts to detect TWAI controller
    bool alertConfigure(uint32_t alerts = TWAI_ALERT_RX_DATA);

    // Get detects alerts TWAI controller
    bool getAlerts();

    // Deinitialize TWAI controller
    void close();

    // Send a CAN frame
    bool send(uint32_t id, const uint8_t *data, uint8_t length, bool extended = false);

    // Check if a frame is available
    bool available();

    // Receive a CAN frame
    bool receive(uint32_t *id, uint8_t *data, uint8_t *length, bool *extended = nullptr);

    // Get TWAI status
    twai_status_info_t getStatus();

private:
    bool _initialized = false;
};

#endif