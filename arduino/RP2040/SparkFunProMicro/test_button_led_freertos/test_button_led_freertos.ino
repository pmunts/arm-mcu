// Arduino RP2040 Button and LED Test Using FreeRTOS

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

// NOTE: With the Arduino-Pico core, if FreeRTOS is enabled (:os=freertos
// appended to the FQBN), the normal Arduino main program function main()
// that calls setup() and loop() is replaced by one that creates some
// background tasks and then calls vTaskStartScheduler().
//
// The setup() and setup1() functions called by tasks running on CPU
// core 0 and core 1 respectively.
//
// The loop() and loop1() functions are called by idle tasks running on CPU
// core 0 and 1 respectively..
//
// main() also creates a task that provides USB serial port emulation.
// Serial.println() et al are redirected to the USB serial port.

// Hardware configuration (bottom to top):
//
// Sparkfun Electronics Pro Micro - RP2040  (3.3V logic!)

// Fix to enable Visual Studio Code IntelliSense
#define __FREERTOS 1

#include <Arduino.h>
#include <FreeRTOS.h>

// Assign GPIO pins

#define LED    2
#define BUTTON 3

QueueHandle_t EdgeQueue;

// Button Interrupt Service Routine -- Enqueue button transitions

void EdgeHandler(void)
{
  bool newstate = !digitalRead(BUTTON);
  xQueueSendFromISR(EdgeQueue, &newstate, NULL);
}

// Main task -- Dequeue button transitions and display results

void MainTaskFunction(void *parameters)
{
  // Attach button GPIO pin interrupt service routine

  attachInterrupt(digitalPinToInterrupt(BUTTON), EdgeHandler, CHANGE);

  // Main event loop

  for (;;)
  {
    bool newstate;

    if (xQueueReceive(EdgeQueue, &newstate, pdMS_TO_TICKS(1000)) == pdPASS)
    {
      Serial.println(newstate ? "PRESS" : "RELEASE");
      digitalWrite(LED, newstate);
    }
    else
      Serial.println("Tick...");
  }
}

// Configure hardware and start main task.

void setup()
{
  Serial.begin(115200);
  Serial.println("\ecArduino RP2040 Button and LED Test Using FreeRTOS\n");

  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, !digitalRead(BUTTON));

  // Create FreeRTOS entities and start the scheduler

  EdgeQueue = xQueueCreate(10, sizeof(bool));
  xTaskCreate(MainTaskFunction, "main", 512, NULL, 1, NULL);
}
