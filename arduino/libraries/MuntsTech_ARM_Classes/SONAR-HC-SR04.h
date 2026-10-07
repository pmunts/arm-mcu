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

#ifndef _SONAR_HC_SR04_H_
#define _SONAR_HC_SR04_H_

#include <rangefinder-interface.h>

using namespace MuntsTech::Interfaces::RangeFinder;

namespace MuntsTech::SONAR::HC_SR04
{
  // Speed of sound:
  //
  // 343 meters / second
  // 34300 cm   / second
  // 0.0343 cm  / microsecond

  const float Vsound = 0.0343F;

  struct RangeFinder_Class: public RangeFinder_Interface
  {
    // Parameterless stub constructor--Requires a subsequent
    // call to Initialize().

    RangeFinder_Class()
    {
      this->TriggerOutput = 0xFFFFFFFF;
      this->EchoInput     = 0xFFFFFFFF;
    }

    // HC-SR04 SONAR rangefinder object constructor

    RangeFinder_Class(unsigned TriggerPin, unsigned EchoPin)
    {
      this->Initialize(TriggerPin, EchoPin);
    }

    // HC-SR04 SONAR rangefinder object initializer

    void Initialize(unsigned TriggerPin, unsigned EchoPin)
    {
      this->TriggerOutput = TriggerPin;
      this->EchoInput     = EchoPin;

      pinMode(TriggerPin, OUTPUT);
      pinMode(EchoPin, INPUT);

      digitalWrite(TriggerPin, LOW);
    }

    float read(void)
    {
      delayMicroseconds(2);
      digitalWrite(this->TriggerOutput, HIGH);
      delayMicroseconds(10);
      digitalWrite(this->TriggerOutput, LOW);

      uint32_t duration = pulseIn(this->EchoInput, HIGH)/2;

      return duration*Vsound;
    }

  private:

    unsigned TriggerOutput;
    unsigned EchoInput;
  };
}

#endif
