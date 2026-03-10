// TB6612 Motor Driver Services

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

#ifndef _MUNTSTECH_MOTOR_TB6612_H
#define _MUNTSTECH_MOTOR_TB6612_H

#include <cassert>
#include <gpio-interface.h>
#include <motor-interface.h>
#include <pwm-interface.h>
#include <GPIO-Arduino.h>
#include <PWM-Hardware.h>

using namespace MuntsTech::Interfaces::Motor;

namespace MuntsTech::Motor::TB6612
{
  struct Output_Class : public Output_Interface
  {
    // Parameterless stub constructor--Requires a subsequent
    // call to Initialize().

    Output_Class()
    {
      this->pwmout = nullptr;
      this->in1out = nullptr;
      this->in2out = nullptr;
    }

    // Motor driver output constuctor

    Output_Class(unsigned pwmpin, unsigned in1pin, unsigned in2pin,
      unsigned freq, unsigned velocity = SPEED_STOP)
    {
      this->Initialize(pwmpin, in1pin, in2pin, freq, velocity);
    }

    // Motor driver output initializer

    void Initialize(unsigned pwmpin, unsigned in1pin, unsigned in2pin,
      unsigned freq, unsigned velocity = SPEED_STOP)
    {
      assert(velocity >= SPEED_MIN);
      assert(velocity <= SPEED_MAX);
      this->pwmout = new MuntsTech::HardwarePWM::Output_Class(pwmpin, freq);
      this->in1out = new MuntsTech::GPIO::Arduino::Pin_Class(in1pin, OUTPUT);
      this->in2out = new MuntsTech::GPIO::Arduino::Pin_Class(in2pin, OUTPUT);

      this->write(velocity);
    }

    // Motor driver output methods

    virtual void write(const float velocity)
    {
      assert(pwmout != nullptr);
      assert(in1out != nullptr);
      assert(in2out != nullptr);
      assert(velocity >= SPEED_MIN);
      assert(velocity <= SPEED_MAX);

      if (velocity > SPEED_STOP)
      {
        // Clockwise (nominal) rotation
        this->in1out->write(true);
        this->in2out->write(false);
        this->pwmout->write(100.0F*velocity);
      }
      else if (velocity < SPEED_STOP)
      {
        // Counterclockwise (nominal) rotation
        this->in1out->write(false);
        this->in2out->write(true);
        this->pwmout->write(-100.0F*velocity);
      }
      else
      {
        // No rotation
        this->pwmout->write(0.0F);
        this->in1out->write(false);
        this->in2out->write(false);
      }
    }

  private:

    MuntsTech::Interfaces::PWM::Output pwmout;
    MuntsTech::Interfaces::GPIO::Pin in1out;
    MuntsTech::Interfaces::GPIO::Pin in2out;
  };
}

#endif
