// Arduino FreeRTOS SMP Test

// Copyright (C)2026, Philip Munts dba Munts Technologies.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#define ENABLE_FREERTOS

#include <Arduino_ARM.h>

// Minimal Standard Random Number Generator, from "Random Number Generators:
// Good Ones Are Hard To Find", Communications of the ACM, October 1988,
// Volume 31 Number 10.

#define A	16807
#define M	2147483647
#define Q	127773
#define R	2836

unsigned int msrand1988(unsigned int *s)
{
  int hi, lo, test;

  hi = *s / Q;
  lo = *s % Q;
  test = A*lo - R*hi;

  if (test > 0)
    *s = test;
  else
    *s = test + M;

  return *s;
}

SemaphoreHandle_t SerialMutex = NULL;

void TaskFunc(void *parameters)
{
  char myname[20];
  memset(myname, 0, sizeof(myname));
  strcpy(myname, (char *) parameters);
  unsigned seed = myname[4];
  unsigned lastcore = rp2040.cpuid();

  vTaskCoreAffinitySet(NULL, 0x03);

  for (;;)
  {
    xSemaphoreTake(SerialMutex, portMAX_DELAY);
    unsigned thiscore = rp2040.cpuid();
    if (thiscore != lastcore) Serial.println("CORE JUMP DETECTED!!!");
    Serial.print(myname); Serial.print(" "); Serial.println(thiscore);
    xSemaphoreGive(SerialMutex);
    lastcore = thiscore;
    vTaskDelay(pdMS_TO_TICKS(1000 + msrand1988(&seed) % 1000));
  }
}

void setup()
{
  Serial.begin(115200);
  while (!BOOTSEL);
  Serial.println("\n\n\ecArduino FreeRTOS SMP Test\n");

  SerialMutex = xSemaphoreCreateMutex();

  xTaskCreate(TaskFunc, "main", 512, (void *) "task0", configMAX_PRIORITIES / 2 + 1, NULL);
  xTaskCreate(TaskFunc, "main", 512, (void *) "task1", configMAX_PRIORITIES / 2 + 1, NULL);
  xTaskCreate(TaskFunc, "main", 512, (void *) "task2", configMAX_PRIORITIES / 2 + 1, NULL);
  xTaskCreate(TaskFunc, "main", 512, (void *) "task3", configMAX_PRIORITIES / 2 + 1, NULL);
  xTaskCreate(TaskFunc, "main", 512, (void *) "task4", configMAX_PRIORITIES / 2 + 1, NULL);
  xTaskCreate(TaskFunc, "main", 512, (void *) "task5", configMAX_PRIORITIES / 2 + 1, NULL);
  xTaskCreate(TaskFunc, "main", 512, (void *) "task6", configMAX_PRIORITIES / 2 + 1, NULL);
  xTaskCreate(TaskFunc, "main", 512, (void *) "task7", configMAX_PRIORITIES / 2 + 1, NULL);
  xTaskCreate(TaskFunc, "main", 512, (void *) "task8", configMAX_PRIORITIES / 2 + 1, NULL);
  xTaskCreate(TaskFunc, "main", 512, (void *) "task9", configMAX_PRIORITIES / 2 + 1, NULL);
}
