// Arduino RP2350 Servo Output Test

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
// Raspberry Pi Pico2 or equivalent (3.3V logic!)

#include <Arduino.h>
#include <RP2040HardwarePWM.h>
#include <ServoPWM.h>

using namespace MuntsTech::Interfaces::Servo;

MuntsTech::Interfaces::Servo::Output *outp;

void setup()
{
  Serial.begin(115200);
  Serial.println("\ecArduino RP2350 Servo Output Test\n");

  outp = new MuntsTech::ServoPWM::Output(new MuntsTech::RP2040::HardwarePWM::Output(22, 50), 50);
}

void loop()
{
  for (float pos = POSITION_NEUTRAL; pos <= POSITION_MAX; pos += 0.015F)
  {
    *outp = pos;
    delay(20);
  }

  for (float pos = POSITION_MAX; pos >= POSITION_MIN; pos -= 0.015F)
  {
    *outp = pos;
    delay(20);
  }

  for (float pos = POSITION_MIN; pos <= POSITION_NEUTRAL; pos += 0.015F)
  {
    *outp = pos;
    delay(20);
  }
}
