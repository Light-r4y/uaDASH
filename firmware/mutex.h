#pragma once

#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

extern SemaphoreHandle_t dataMutex;
extern SemaphoreHandle_t uiMutex;

#ifdef __cplusplus
extern "C" {
#endif

void mutex_init();

#ifdef __cplusplus
} /*extern "C"*/
#endif