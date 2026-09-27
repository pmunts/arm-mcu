// LPC1114 I/O Processor Pulse Width Modulated output services

// Copyright (C)2018, Philip Munts, President, Munts AM Corp.
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

#ifndef _LPC1114_IOP_PWM_H_
#define _LPC1114_IOP_PWM_H_

#include "LPC1114_IOP_Common.h"

namespace LPC1114_IOP
{
  struct PWM
  {
    // Default parameterless constructor -- The resulting object will not be
    // usable until reconstructed or Init() has been called!
    PWM(void);

    // Construct a PWM output
    PWM(Transport server, uint32_t pin, uint32_t freq = 100,
      double dutycycle = LPC1114_PWM_DUTY_MIN);

    // Initialize a PWM output
    void Init(Transport server, uint32_t pin, uint32_t freq = 100,
      double dutycycle = LPC1114_PWM_DUTY_MIN);

    // PWM output method
    void Put(const double dutycycle);

    // PWM output operator
    void operator =(const double dutycycle);

  private:

    Transport server;
    uint32_t pin;
  };

  struct Servo
  {
    // Default parameterless constructor -- The resulting object will not be
    // usable until reconstructed or Init() has been called!
    Servo(void);

    // Construct a servo output
    Servo(Transport server, uint32_t pin, uint32_t freq = 50,
      double position = LPC1114_SERVO_NEUTRAL);

    // Initialize a servo output
    void Init(Transport server, uint32_t pin, uint32_t freq = 50,
      double position = LPC1114_SERVO_NEUTRAL);

    // Servo output method
    void Put(const double position);

    // Servo output operator
    void operator =(const double position);

  private:

    uint32_t frequency;
    PWM *output;
  };
}

#endif
