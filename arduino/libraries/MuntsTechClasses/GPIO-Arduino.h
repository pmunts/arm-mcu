// Arduino GPIO Pin Services

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

#ifndef _GPIO_ARDUINO_H
#define _GPIO_ARDUINO_H

#include <assert.h>
#include <gpio-interface.h>

#ifdef ARDUINO_ARCH_RP2040
#define OUTPUT_OPEN_DRAIN OUTPUT_OPENDRAIN
#endif

namespace MuntsTech::GPIO::Arduino
{
  // GPIO pin class definition

  struct Pin_Class : public MuntsTech::Interfaces::GPIO::Pin_Interface
  {
    // Parameterless stub constructor--Requires a subsequent
    // call to Initialize().

    Pin_Class()
    {
      this->pin = -1;
      this->output = false;
      this->activelow = false;
    }

    // GPIO pin constructor

    Pin_Class(unsigned pin, unsigned mode, bool activelow = false,
      bool state = false)
    {
      this->Initialize(pin, mode, activelow, state);
    }

    // GPIO pin initializer

    void Initialize(unsigned pin, unsigned mode, bool activelow = false,
      bool state = false)
    {
#ifdef ARDUINO_ARCH_RP2040
      assert(mode <= OUTPUT_12MA);
      this->output = (mode == OUTPUT) || ((mode >= OUTPUT_OPENDRAIN) && (mode <= OUTPUT_12MA));

#elifdef ARDUINO_ARCH_STM32
      assert(mode <= OUTPUT_OPEN_DRAIN);
      this->output = (mode == OUTPUT) || (mode = OUTPUT_OPEN_DRAIN);
#else
      assert(node <= INPUT_PULLUP);
      this->output = (mode == OUTPUT);
#endif
      pinMode(pin, mode);

      this->pin       = pin;
      this->activelow = activelow;

      if (this->output) this->write(state);
    }

    // GPIO pin methods

    virtual void write(bool state)
    {
      assert(this->output);
      digitalWrite(this->pin, state ^ this->activelow);
    }

    virtual bool read(void)
    {
      return digitalRead(this->pin) ^ this->activelow;
    }

    // PWM output operators

#ifdef ENABLE_ASSIGNMENT_OPERATOR
    operator bool(void)
    {
      return this->read();
    }

    virtual void operator =(const bool state)
    {
      this->write(dutycycle);
    }
#endif

  private:

    unsigned pin;
    bool output;
    bool activelow;
  };
}

#endif
