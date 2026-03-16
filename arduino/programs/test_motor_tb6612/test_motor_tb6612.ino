// Arduino DC Motor Test

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
#include <Motor-TB6612.h>

MuntsTech::Motor::TB6612::Output_Class outp;

void setup()
{
  Serial.begin(115200);
  Serial.println("\n\n\ecArduino DC Motor Test\n");

  outp.Initialize(3, 4, 5, 1000);
}

void loop()
{
  for (float V = 0.0F; V < 1.0F; V += 1.0E-2F)
  {
    outp.write(V);
    delay(200);
  }

  for (float V = 1.0F; V > -1.0F; V -= 1.0E-2F)
  {
    outp.write(V);
    delay(200);
  }

  for (float V = -1.0F; V < 0.0F; V += 1.0E-2F)
  {
    outp.write(V);
    delay(200);
  }
}
