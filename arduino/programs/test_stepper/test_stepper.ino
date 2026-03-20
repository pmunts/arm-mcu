// Arduino Stepper Motor Test

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

// This sketch works with either a unipolar stepper motor driven by an
// ATtiny85 encoder *or* a bipolar stepper motor driven by an A4988 or
// equivalent.

#include <Arduino_ARM.h>

const int MaxSteps = 2048;
const int Dir      = 2;
const int Step     = 3;

void setup()
{
  Serial.begin(115200);
  Serial.println("\n\n\ecArduino Stepper Motor Test\n");

  pinMode(Dir,  OUTPUT);
  pinMode(Step, OUTPUT);
  digitalWrite(Step, false);
}

void loop()
{
  digitalWrite(Dir,  true);

  for (int i = 0; i < MaxSteps; i++)
  {
    digitalWrite(Step, true);
    delay(1);
    digitalWrite(Step, false);
    delay(10);
  }

  digitalWrite(Dir, false);

  for (int i = 0; i < MaxSteps; i++)
  {
    digitalWrite(Step, true);
    delay(1);
    digitalWrite(Step, false);
    delay(10);
  }
}
