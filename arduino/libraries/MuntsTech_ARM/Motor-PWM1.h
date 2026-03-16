// Motor Driver Services, using one PWM output (speed) and one GPIO output
// (direction).

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

#ifndef _MUNTSTECH_MOTOR_PWM1_H
#define _MUNTSTECH_MOTOR_PWM1_H

#include <cassert>
#include <gpio-interface.h>
#include <motor-interface.h>
#include <pwm-interface.h>
#include <GPIO-Arduino.h>
#include <PWM-Hardware.h>

using namespace MuntsTech::Interfaces::Motor;

namespace MuntsTech::Motor::PWM1
{
  struct Output_Class : public Output_Interface
  {
    // Parameterless stub constructor--Requires a subsequent
    // call to Initialize().

    Output_Class()
    {
      this->dirout = nullptr;
      this->pwmout = nullptr;
    }

    // Motor driver output constuctor

    Output_Class(unsigned dirpin, unsigned pwmpin,
      unsigned freq, unsigned velocity = SPEED_STOP)
    {
      this->Initialize(dirpin, pwmpin, freq, velocity);
    }

    // Motor driver output initializer

    void Initialize(unsigned dirpin, unsigned pwmpin,
      unsigned freq, unsigned velocity = SPEED_STOP)
    {
      assert(velocity >= SPEED_MIN);
      assert(velocity <= SPEED_MAX);
      this->dirout = new MuntsTech::GPIO::Arduino::Pin_Class(dirpin, OUTPUT);
      this->pwmout = new MuntsTech::PWM::Hardware::Output_Class(pwmpin, freq);

      this->write(velocity);
    }

    // Motor driver output methods

    virtual void write(const float velocity)
    {
      assert(this->dirout != nullptr);
      assert(this->pwmout != nullptr);
      assert(velocity >= SPEED_MIN);
      assert(velocity <= SPEED_MAX);

      if (velocity > SPEED_STOP)
      {
        // Clockwise (nominal) rotation
        this->dirout->write(true);
        this->pwmout->write(100.0F*velocity);
      }
      else if (velocity < SPEED_STOP)
      {
        // Counterclockwise (nominal) rotation
        this->dirout->write(false);
        this->pwmout->write(-100.0F*velocity);
      }
      else
      {
        // No rotation
        this->dirout->write(true);
        this->pwmout->write(0.0F);
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

    MuntsTech::Interfaces::GPIO::Pin dirout;
    MuntsTech::Interfaces::PWM::Output pwmout;
  };
}

#endif
