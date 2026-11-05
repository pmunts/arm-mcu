// Hardware PWM output services using Pico SDK PWM services
// Works on both RA4M1 and RP2350.

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

#ifndef _MUNTSTECH_RA4M1_PWM_H
#define _MUNTSTECH_RA4M1_PWM_H

#include <cassert>
#include <pwm.h>
#include <pwm-interface.h>

namespace MuntsTech::PWM::Hardware
{
  // PWM output class definition

  struct Output_Class: public MuntsTech::Interfaces::PWM::Output_Interface
  {
    // Parameterless stub constructor--Requires a subsequent
    // call to Initialize().

    Output_Class()
    {
      this->outp   = nullptr;
    }

    // PWM output constructor

    Output_Class(unsigned pin, unsigned fpwm,
      float dutycycle = MuntsTech::Interfaces::PWM::DUTYCYCLE_MIN)
    {
      this->Initialize(pin, fpwm, dutycycle);
    }

    // PWM output initializer method

    void Initialize(unsigned pin, unsigned fpwm,
      float dutycycle = MuntsTech::Interfaces::PWM::DUTYCYCLE_MIN)
    {
      assert(fpwm >= 50);
      assert(dutycycle >= MuntsTech::Interfaces::PWM::DUTYCYCLE_MIN);
      assert(dutycycle <= MuntsTech::Interfaces::PWM::DUTYCYCLE_MAX);

      this->outp = new PwmOut(pin);
      this->outp->begin(fpwm, dutycycle);
    }

    // PWM output methods

    virtual void write(const float dutycycle)
    {
      assert(this->outp != nullptr);
      assert(dutycycle >= MuntsTech::Interfaces::PWM::DUTYCYCLE_MIN);
      assert(dutycycle <= MuntsTech::Interfaces::PWM::DUTYCYCLE_MAX);

      this->outp->pulse_perc(dutycycle);
    }

    // PWM output operators

#ifdef ENABLE_ASSIGNMENT_OPERATOR
    void operator =(const float dutycycle)
    {
      this->write(dutycycle);
    }
#endif

  private:

    PwmOut *outp;
  };
}

#endif
