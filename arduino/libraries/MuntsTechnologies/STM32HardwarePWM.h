// STM32 Arduino Hardware PWM Output Services

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

#ifndef _STM32_HARDWARE_PWM_H
#define _STM32_HARDWARE_PWM_H

#include <assert.h>
#include "HardwareTimer.h"
#include <pwm-interface.h>

namespace MuntsTech::STM32::HardwarePWM
{
  // PWM output class definition

  struct Output: public MuntsTech::Interfaces::PWM::Output
  {
    // Parameterless stub constructor--Requires a subsequent
    // call to Initialize().

    Output()
    {
      this->timer   = NULL;
      this->channel = 0;
      this->pin     = 0;
      this->period  = 0;
    }

    // PWM output constructor

    Output(unsigned pin, unsigned frequency,
      float dutycycle = MuntsTech::Interfaces::PWM::DUTYCYCLE_MIN)
    {
      this->Initialize(pin, frequency, dutycycle);
    }

    // PWM output initializer method

    void Initialize(unsigned pin, unsigned frequency,
      float dutycycle = MuntsTech::Interfaces::PWM::DUTYCYCLE_MIN)
    {
      assert(frequency >= 50);
      assert(dutycycle >= MuntsTech::Interfaces::PWM::DUTYCYCLE_MIN);
      assert(dutycycle <= MuntsTech::Interfaces::PWM::DUTYCYCLE_MAX);

      // Look up the timer subsystem for the given output pin

      TIM_TypeDef *Instance = (TIM_TypeDef *)pinmap_peripheral(digitalPinToPinName(pin), PinMap_PWM);
      assert(Instance != NULL);

      // Populate private fields

      this->timer   = new HardwareTimer(Instance);
      this->channel = STM_PIN_CHANNEL(pinmap_function(digitalPinToPinName(pin), PinMap_PWM));
      this->pin     = pin;
      this->period  = this->timer->getTimerClkFreq()/frequency;

      // Configure the timer for PWM operation at maximum resolution

      this->timer->setPrescaleFactor(1);
      this->timer->setOverflow(this->period, TICK_FORMAT);
      this->timer->setMode(this->channel, TIMER_OUTPUT_COMPARE_PWM1, pin);
      this->timer->setCaptureCompare(this->channel, round(dutycycle/100.0F*this->period), TICK_COMPARE_FORMAT);
      this->timer->resume();
    }

    // PWM output methods

    virtual void write(const float dutycycle)
    {
      assert(this->timer != NULL);
      assert(dutycycle >= MuntsTech::Interfaces::PWM::DUTYCYCLE_MIN);
      assert(dutycycle <= MuntsTech::Interfaces::PWM::DUTYCYCLE_MAX);

      this->timer->setCaptureCompare(this->channel, round(dutycycle/100.0F*this->period), TICK_COMPARE_FORMAT);
    }

    // PWM output operators

    virtual void operator =(const float dutycycle)
    {
      this->write(dutycycle);
    }

  private:

    HardwareTimer *timer;
    unsigned channel;
    unsigned pin;
    unsigned period;
  };
}

#endif
