// Arduino PCA9686 PWM Output Services

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

#ifndef _PCA9685_PWM_H
#define _PCA9685_PWM_H

#include <assert.h>
#include <pwm-interface.h>
#include <FaBoPWM_PCA9685.h>

namespace MuntsTech::PCA9685::PWM
{
  // PCA9685 device class definition

  struct Device
  {
    // Parameterless stub constructor--Requires a subsequent
    // call to Initialize().

    Device()
    {
      this->driver = NULL;
    }

    Device(uint8_t addr, unsigned freq)
    {
      this->Initialize(addr, freq);
    }

    void Initialize(uint8_t addr, unsigned freq)
    {
      assert(freq >= 50);
      assert(freq <= 1526);
      this->driver = new FaBoPWM(addr);
      this->driver->begin();
      this->driver->init(0);
      this->driver->set_hz(freq);
    }

    void write(unsigned channel, unsigned data)
    {
      assert(this->driver != NULL);
      assert(channel <= 15);
      assert(data <= 4095);

      this->driver->set_channel_value(channel, data);
    }

  private:

    FaBoPWM *driver;
  };

  // PWM output class definition

  struct Output_Class: public MuntsTech::Interfaces::PWM::Output_Interface
  {
    // Parameterless stub constructor--Requires a subsequent
    // call to Initialize().

    Output_Class()
    {
      this->dev     = NULL;
      this->channel = 0;
    }

    // PWM output constructor

    Output_Class(Device *dev, unsigned channel, 
      float dutycycle = MuntsTech::Interfaces::PWM::DUTYCYCLE_MIN)
    {
      this->Initialize(dev, channel, dutycycle);
    }

    // PWM output initializer method

    void Initialize(Device *dev, unsigned channel,
      float dutycycle = MuntsTech::Interfaces::PWM::DUTYCYCLE_MIN)
    {
      assert(dev != NULL);
      assert(channel <= 15);
      assert(dutycycle >= MuntsTech::Interfaces::PWM::DUTYCYCLE_MIN);
      assert(dutycycle <= MuntsTech::Interfaces::PWM::DUTYCYCLE_MAX);

      this->dev     = dev;
      this->channel = channel;
      this->write(dutycycle);
    }

    // PWM output methods

    virtual void write(const float dutycycle)
    {
      assert(this->dev != NULL);
      assert(dutycycle >= MuntsTech::Interfaces::PWM::DUTYCYCLE_MIN);
      assert(dutycycle <= MuntsTech::Interfaces::PWM::DUTYCYCLE_MAX);

      this->dev->write(this->channel, (unsigned) (dutycycle/100.0*4095));
    }

    // PWM output operators

    virtual void operator =(const float dutycycle)
    {
      this->write(dutycycle);
    }

  private:

    Device *dev;
    unsigned channel;
  };
}

#endif
