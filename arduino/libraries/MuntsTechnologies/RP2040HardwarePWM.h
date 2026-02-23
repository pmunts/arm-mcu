// Hardware PWM output services using Pico SDK PWM services
// Works on both RP2040 and RP2350.

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
#include <pico/stdlib.h>
#include <hardware/pwm.h>
#include <pwm-interface.h>

namespace MuntsTech::RP2040::HardwarePWM
{
  // PWM output class definition

  struct Output: public MuntsTech::Interfaces::PWM::Output_Interface
  {
    // PWM output Constructor

    Output(unsigned pin, unsigned frequency,
      float dutycycle = MuntsTech::Interfaces::PWM::DUTYCYCLE_MIN)
    {
      assert(pin <= 29);
      assert(frequency >= 50);
      assert(dutycycle >= MuntsTech::Interfaces::PWM::DUTYCYCLE_MIN);
      assert(dutycycle <= MuntsTech::Interfaces::PWM::DUTYCYCLE_MAX);

      unsigned slice = pwm_gpio_to_slice_num(pin);
      unsigned channel = pwm_gpio_to_channel(pin);
      unsigned top;
      unsigned div_int;
      unsigned div_frac;

      GetDividers(frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_SYS)*1000,
        frequency, &top, &div_int, &div_frac);
      
      pwm_set_clkdiv_mode(slice, PWM_DIV_FREE_RUNNING);
      pwm_set_clkdiv_int_frac4(slice, div_int, div_frac);
      pwm_set_phase_correct(slice, false);
      pwm_set_wrap(slice, top);
      pwm_set_chan_level(slice, channel, 0);
      pwm_set_enabled(slice, true);

      gpio_set_function(pin, GPIO_FUNC_PWM);
      pwm_set_gpio_level(pin, (uint16_t) (dutycycle/100.0F*top));

      this->pin    = pin;
      this->period = top;
    }

    // PWM output methods

    virtual void write(const float dutycycle)
    {
      assert(dutycycle >= MuntsTech::Interfaces::PWM::DUTYCYCLE_MIN);
      assert(dutycycle <= MuntsTech::Interfaces::PWM::DUTYCYCLE_MAX);

      pwm_set_gpio_level(this->pin, (uint16_t) (dutycycle/100.0F*this->period));
    }

    // PWM output operators

    virtual void operator =(const float dutycycle)
    {
      this->write(dutycycle);
    }

  private:

    unsigned pin;
    unsigned period;

    static double fpwm_actual(double fsys, double top, double div_int,
      double div_frac)
    {
      return fsys/((top + 1.0)*(div_int + div_frac/16.0));
    }

    static bool GetDividers(unsigned fsys, unsigned fpwm, unsigned *top,
      unsigned *div_int, unsigned *div_frac)
    {
      for (unsigned t = 65536; t > 0; t--)
        for (unsigned i = 1; i <= 256; i++)
          for (unsigned frac = 0; frac < 16; frac++)
          {
            if ((i == 256) && (frac > 0)) continue;

            double ftry = fpwm_actual(fsys, t, i, frac);

            if (fabs(fpwm - ftry)/fpwm < 0.001)
            {
              *top = t;
              *div_int = i;
              *div_frac= frac;
              return true;
            }
          }

      return false;
    }
  };
}

#endif
