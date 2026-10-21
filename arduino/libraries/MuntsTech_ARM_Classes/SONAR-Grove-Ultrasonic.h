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

// For the Grove Ultrasonic Ranger:
// https://wiki.seeedstudio.com/Grove-Ultrasonic_Ranger
//
// Should also work for the Parallax Ping))):
// https://www.parallax.com/products/ping-ultrasonic-distance-sensor
//
// and other 3-terminal ultrasonic rangefinder modules

#ifndef _SONAR_GROVE_ULTRASONIC_H_
#define _SONAR_GROVE_ULTRASONIC_H_

#include <rangefinder-interface.h>

using namespace MuntsTech::Interfaces::RangeFinder;

namespace MuntsTech::SONAR::Grove_Ultrasonic
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
      this->SIG = 0xFFFFFFFF;
    }

    // Grove Ultrasonic Ranger SONAR rangefinder object constructor

    RangeFinder_Class(unsigned SigPin)
    {
      this->Initialize(SigPin);
    }

    // Grove Ultrasonic Ranger SONAR rangefinder object initializer

    void Initialize(unsigned SigPin)
    {
      this->SIG = SigPin;
      pinMode(SIG, OUTPUT);
      digitalWrite(SIG, LOW);
    }

    float read(void)
    {
      // Send ping
      pinMode(SIG, OUTPUT);
      digitalWrite(SIG, HIGH);
      delayMicroseconds(10);
      digitalWrite(SIG, LOW);

      // Receive echo
      pinMode(SIG, INPUT);
      uint16_t duration = pulseIn(SIG, HIGH)/2;

      return duration*Vsound;
    }

  private:

    unsigned SIG;
  };
}

#endif
