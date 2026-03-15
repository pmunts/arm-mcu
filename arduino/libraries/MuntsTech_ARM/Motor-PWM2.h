// Motor Driver Services, using two PWM outputs

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

#ifndef _MUNTSTECH_MOTOR_PWM2_H
#define _MUNTSTECH_MOTOR_PWM2_H

#include <cassert>
#include <motor-interface.h>
#include <pwm-interface.h>
#include <PWM-Hardware.h>

using namespace MuntsTech::Interfaces::Motor;

namespace MuntsTech::Motor::PWM2
{
  struct Output_Class : public Output_Interface
  {
    // Parameterless stub constructor--Requires a subsequent
    // call to Initialize().

    Output_Class()
    {
      this->pwmout1 = nullptr;
      this->pwmout2 = nullptr;
    }

    // Motor driver output constuctor

    Output_Class(unsigned pwmpin1, unsigned pwmpin2,
      unsigned freq, unsigned velocity = SPEED_STOP)
    {
      this->Initialize(pwmpin1, pwmpin2, freq, velocity);
    }

    // Motor driver output initializer

    void Initialize(unsigned pwmpin1, unsigned pwmpin2,
      unsigned freq, unsigned velocity = SPEED_STOP)
    {
      assert(velocity >= SPEED_MIN);
      assert(velocity <= SPEED_MAX);
      this->pwmout1 = new MuntsTech::HardwarePWM::Output_Class(pwmpin1, freq);
      this->pwmout2 = new MuntsTech::HardwarePWM::Output_Class(pwmpin2, freq);

      this->write(velocity);
    }

    // Motor driver output methods

    virtual void write(const float velocity)
    {
      assert(pwmout1 != nullptr);
      assert(pwmout2 != nullptr);
      assert(velocity >= SPEED_MIN);
      assert(velocity <= SPEED_MAX);

      if (velocity > SPEED_STOP)
      {
        // Clockwise (nominal) rotation
        this->pwmout2->write(0.0F);
        this->pwmout1->write(100.0F*velocity);
      }
      else if (velocity < SPEED_STOP)
      {
        // Counterclockwise (nominal) rotation
        this->pwmout1->write(0.0F);
        this->pwmout2->write(-100.0F*velocity);
      }
      else
      {
        // No rotation
        this->pwmout1->write(0.0F);
        this->pwmout2->write(0.0F);
      }
    }

    // Motor driver output operators

#ifdef ENABLE_ASSIGNMENT_OPERATOR
    virtual void operator =(const float velocity)
    {
      this->write(velocity);
    }
#endif

  private:

    MuntsTech::Interfaces::PWM::Output pwmout1;  // Nominally CW
    MuntsTech::Interfaces::PWM::Output pwmout2;  // Nominally CCW
  };
}

#endif
