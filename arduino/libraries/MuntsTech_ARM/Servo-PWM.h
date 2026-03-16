// Servo output services using PWM services

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

#ifndef _MUNTSTECH_SERVO_PWM_H
#define _MUNTSTECH_SERVO_PWM_H

#include <cassert>
#include <pwm-interface.h>
#include <servo-interface.h>

using namespace MuntsTech::Interfaces::Servo;

namespace MuntsTech::Servo::PWM
{
  struct Output_Class: public Output_Interface
  {
    // Parameterless stub constructor--Requires a subsequent
    // call to Initialize().

    Output_Class()
    {
      this->pwmout   = NULL;
      this->freq     = 0.0F;
      this->swing    = 0.0F;
      this->midpoint = 0.0F;
    }

    Output_Class(MuntsTech::Interfaces::PWM::Output pwmout, unsigned frequency,
      float position = POSITION_NEUTRAL,
      float minwidth = 1.0E-3F, float maxwidth = 2.0E-3F)
    {
      this->Initialize(pwmout, frequency, position, minwidth, maxwidth);
    }

    // Servo output initializer

    void Initialize(MuntsTech::Interfaces::PWM::Output pwmout, unsigned frequency,
      float position = POSITION_NEUTRAL,
      float minwidth = 1.0E-3F, float maxwidth = 2.0E-3F)
    {
      assert(pwmout != NULL);
      assert(frequency > 0);
      assert(position >= POSITION_MIN);
      assert(position <= POSITION_MAX);
      assert(maxwidth > minwidth);
      assert(maxwidth < 1.0F/frequency);
      this->pwmout   = pwmout;
      this->freq     = frequency;
      this->swing    = (maxwidth - minwidth)/2.0F;
      this->midpoint = minwidth + swing;
      this->write(position);
    }

    // Servo output methods

    virtual void write(const float position)
    {
      assert(this->pwmout != NULL);
      assert(position >= POSITION_MIN);
      assert(position <= POSITION_MAX);
      this->pwmout->write((this->midpoint + this->swing*position)*this->freq*100.0F);
    }

    // Servo output operators

#ifdef ENABLE_ASSIGNMENT_OPERATOR
    void operatior =(const float position)
    {
      this->write(position);
    }
#endif

  private:

    MuntsTech::Interfaces::PWM::Output pwmout;
    float freq;
    float swing;
    float midpoint;
  };
}

#endif
