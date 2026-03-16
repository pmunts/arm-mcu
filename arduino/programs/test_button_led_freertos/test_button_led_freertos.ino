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

#define ENABLE_FREERTOS

#include <Arduino_ARM.h>
#include <GPIO-Arduino.h>

MuntsTech::GPIO::Arduino::Pin_Class Button;
MuntsTech::GPIO::Arduino::Pin_Class LED;

QueueHandle_t EdgeQueue;

// Button Interrupt Service Routine -- Enqueue button transitions

void EdgeHandler(void)
{
  bool newstate = Button.read();
  xQueueSendFromISR(EdgeQueue, &newstate, NULL);
}

// Main task -- Dequeue button transitions and display results

void MainTaskFunction(void *parameters)
{
  // Attach button GPIO pin interrupt service routine

  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), EdgeHandler, CHANGE);

  // Main event loop

  for (;;)
  {
    bool newstate;

    if (xQueueReceive(EdgeQueue, &newstate, pdMS_TO_TICKS(1000)) == pdPASS)
    {
      Serial.println(newstate ? "PRESS" : "RELEASE");
      LED.write(newstate);
    }
    else
      Serial.println("Tick...");
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println("\n\n\ecArduino Button and LED Test using FreeRTOS\n");
  Serial.print("LED    on D"); Serial.println(LED_PIN);
  Serial.print("Button on D"); Serial.println(BUTTON_PIN);
  Serial.println();

  Button.Initialize(BUTTON_PIN, BUTTON_MODE, BUTTON_XOR);
  LED.Initialize(LED_PIN, OUTPUT);

  LED.write(Button.read());

  // Create FreeRTOS entities and start the scheduler

  EdgeQueue = xQueueCreate(10, sizeof(bool));
  xTaskCreate(MainTaskFunction, "main", 512, NULL, 1, NULL);
  vTaskStartScheduler();
}

void loop()
{
}
