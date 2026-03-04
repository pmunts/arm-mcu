// LPC1114 I/O Processor LED Test

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

#include <Arduino_ARM.h>
#include <LPC1114_IOP.h>

LPC1114_IOP::Transport_Class IOP;  // LPC1114 I/O Processor
LPC1114_IOP::GPIO LED;             // LPC1114 I/O Processor on-board LED

void setup()
{
  Serial.begin(115200);
  Serial.println("\n\n\ecLPC1114 I/O Processor LED Test\n");

  IOP.Init();
  LED.Init(&IOP, LPC1114_LED, LPC1114_GPIO_OUTPUT, false);
}

void loop()
{
  Serial.print("Turning LED ");
  Serial.print(LED ? "OFF" : "ON");
  Serial.print("\r\n");

  // Toggle the LED

  LED = !LED;
  delay(1000);
}
