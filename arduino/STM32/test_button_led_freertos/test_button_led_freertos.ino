// Arduino Button and LED Test using FreeRTOS

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

// Hardware configuration (bottom to top):
//
// Nucleo STM32F411RE (3.3V logic!)

#include <Arduino.h>
#include <STM32FreeRTOS.h>

QueueHandle_t EdgeQueue;

// Button Interrupt Service Routine -- Enqueue button transitions

void EdgeHandler(void)
{
  bool newstate = !digitalRead(USER_BTN);
  xQueueSendFromISR(EdgeQueue, &newstate, NULL);
}

// Main task -- Dequeue button transitions and display results

void MainTaskFunction(void *parameters)
{
  // Attach button GPIO pin interrupt service routine

  attachInterrupt(digitalPinToInterrupt(USER_BTN), EdgeHandler, CHANGE);

  // Main event loop

  for (;;)
  {
    bool newstate;

    if (xQueueReceive(EdgeQueue, &newstate, pdMS_TO_TICKS(1000)) == pdPASS)
    {
      Serial.println(newstate ? "PRESS" : "RELEASE");
      digitalWrite(LED_BUILTIN, newstate);
    }
    else
      Serial.println("Tick...");
  }
}

// Configure hardware and start FreeRTOS.  Does not return because
// vTaskStartScheduler() does not return.

void setup()
{
  Serial2.begin(115200);
  Serial2.println("\ecArduino Button and LED Test using FreeRTOS\n");

  // Configure GPIO pins

  pinMode(USER_BTN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  // Create FreeRTOS entities and start the scheduler

  EdgeQueue = xQueueCreate(10, sizeof(bool));
  xTaskCreate(MainTaskFunction, "main", 512, NULL, 1, NULL);
  vTaskStartScheduler();
}

// With FreeRTOS running, loop() is called by the idle task instead of the
// Arduino main() function (which blocked because setup() did not return).

void loop()
{
}
