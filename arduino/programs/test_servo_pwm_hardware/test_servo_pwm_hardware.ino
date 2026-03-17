// Arduino Hardware PWM Servo Output Test

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
#include <PWM-Hardware.h>
#include <Servo-PWM.h>

using namespace MuntsTech::Interfaces::Servo;

MuntsTech::PWM::Hardware::Output_Class pwmout;
MuntsTech::Servo::PWM::Output_Class outp;

void setup()
{
  Serial.begin(115200);
  Serial.println("\n\n\ecArduino Hardware PWM Servo Output Test\n");

  pwmout.Initialize(1, 50);
  outp.Initialize(&pwmout, 50);
}

void loop()
{
  for (float pos = POSITION_NEUTRAL; pos <= POSITION_MAX; pos += 0.015F)
  {
    outp.write(pos);
    delay(20);
  }

  for (float pos = POSITION_MAX; pos >= POSITION_MIN; pos -= 0.015F)
  {
    outp.write(pos);
    delay(20);
  }

  for (float pos = POSITION_MIN; pos <= POSITION_NEUTRAL; pos += 0.015F)
  {
    outp.write(pos);
    delay(20);
  }
}
