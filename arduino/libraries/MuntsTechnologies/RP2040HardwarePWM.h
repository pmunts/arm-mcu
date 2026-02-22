// PWM output services using RP2040 Hardware PWM Library
//
// See also:
//
// https://docs.arduino.cc/libraries/rp2040_pwm
// https://github.com/khoih-prog/RP2040_PWM

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

#ifndef _MUNTSTECH_RP2040_PWM_H
#define _MUNTSTECH_RP2040_PWM_H

#include <assert.h>
#include <RP2040_PWM.h>
#include <pwm-interface.h>

namespace MuntsTech::RP2040::HardwarePWM
{
  // PWM output class definition

  struct Output: public MuntsTech::Interfaces::PWM::Output_Interface
  {
    // PWM output Constructor

    Output(unsigned pin, unsigned frequency,
      double dutycycle = MuntsTech::Interfaces::PWM::DUTYCYCLE_MIN)
    {
      assert(pin <= 29);
      assert(frequency >= 50);
      assert(dutycycle >= MuntsTech::Interfaces::PWM::DUTYCYCLE_MIN);
      assert(dutycycle <= MuntsTech::Interfaces::PWM::DUTYCYCLE_MAX);
      this->pin  = pin;
      this->freq = frequency;
      this->outp = new RP2040_PWM(pin, frequency, dutycycle);
      this->outp->setPWM();
    }

    // PWM output methods

    virtual void write(const double dutycycle)
    {
      assert(dutycycle >= MuntsTech::Interfaces::PWM::DUTYCYCLE_MIN);
      assert(dutycycle <= MuntsTech::Interfaces::PWM::DUTYCYCLE_MAX);
      this->outp->setPWM(this->pin, this->freq, dutycycle);
    }

    // PWM output operators

    virtual void operator =(const double dutycycle)
    {
      this->write(dutycycle);
    }

  private:

    unsigned pin;
    unsigned freq;
    RP2040_PWM *outp;
  };
}

#endif
