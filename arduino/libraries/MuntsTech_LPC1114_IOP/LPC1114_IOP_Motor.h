// LPC1114 I/O Processor Motor output services

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

#ifndef _LPC1114_IOP_MOTOR_H_
#define _LPC1114_IOP_MOTOR_H_

#include "LPC1114_IOP_Common.h"
#include "LPC1114_IOP_GPIO.h"
#include "LPC1114_IOP_LEGORC.h"
#include "LPC1114_IOP_PWM.h"

namespace LPC1114_IOP
{
  struct Motor
  {
    // Default parameterless constructor -- The resulting object will not be
    // usable until reconstructed or Init() has been called!
    Motor(void);

    // Motor controlled with a PWM speed output and a GPIO direction output
    Motor(Transport server, PWM *pwmout, GPIO *dirout);

    void Init(Transport server, PWM *pwmout, GPIO *dirout);

    // Motor controlled with two PWM outputs (clockwise and counterclockwise)
    Motor(Transport server, PWM *pwmcw, PWM *pwmccw);

    void Init(Transport server, PWM *pwmcw, PWM *pwmccw);

    // Motor controlled with a servo output (continuous rotation servo)
    Motor(Transport server, Servo *servo);

    void Init(Transport server, Servo *servo);

    // Motor controlled by LEGO Power Functions Infrared Remote Control Protocol
    Motor(Transport server, LEGORC *ired, uint32_t channel, uint32_t motor);

    void Init(Transport server, LEGORC *ired, uint32_t channel, uint32_t motor);

    // Set motor speed
    void Put(const double velocity);

    void operator =(const double velocity);

  private:

    Transport server;
    GPIO *dir;
    PWM *pwm1;
    PWM *pwm2;
    Servo *servo;
    LEGORC *ired;
    uint32_t channel;
    uint32_t motor;
  };
}

#endif
