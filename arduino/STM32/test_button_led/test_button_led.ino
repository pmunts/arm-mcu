// Arduino Button and LED Test

// Copyright (C)2025-2026, Philip Munts dba Munts Technologies.
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

void setup()
{
  Serial2.begin(115200);
  Serial2.println("\ecArduino Button and LED Test\n");

  pinMode(USER_BTN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  static bool oldstate = digitalRead(USER_BTN);
  bool newstate = !digitalRead(USER_BTN);

  if (!oldstate && newstate)
  {
    Serial2.println("PRESS");
    digitalWrite(LED_BUILTIN, true);
  }

  if (oldstate && !newstate)
  {
    Serial2.println("RELEASE");
    digitalWrite(LED_BUILTIN, false);
  }

  oldstate = newstate;
}
