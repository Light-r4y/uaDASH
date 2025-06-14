#include "mutex.h"


SemaphoreHandle_t dataMutex = xSemaphoreCreateMutex();
SemaphoreHandle_t uiMutex = xSemaphoreCreateMutex();

void mutex_init() {
  if (dataMutex == NULL || uiMutex == NULL) {
#ifdef DEBUG
    Serial.println("Failed Mutex init");
#endif
    while (1)
      ;
  }
}