// Arduino NeoPixel GPIO Pin Services

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

#ifndef _GPIO_NEOPIXEL_H
#define _GPIO_NEOPIXEL_H

#include <assert.h>
#include <gpio-interface.h>
#include <Adafruit_NeoPixel.h>

namespace MuntsTech::GPIO::NeoPixel
{
  const uint32_t DefaultOnColor = 0x00000040;

  // GPIO pin class definition

  struct Pin_Class : public MuntsTech::Interfaces::GPIO::Pin_Interface
  {
    // Parameterless stub constructor--Requires a subsequent
    // call to Initialize().

    Pin_Class()
    {
      this->LED   = NULL;
      this->state = false;
      this->index = 0xFFFF;
      this->color = 0x00000000;
    }

    // GPIO pin constructor

    Pin_Class(unsigned pin, bool state = false, unsigned nleds = 1,
      unsigned index = 0, uint32_t color = DefaultOnColor)
    {
      this->Initialize(pin, state, nleds, index, color);
    }

    // GPIO pin initializer

    void Initialize(unsigned pin, bool state = false, unsigned nleds = 1,
      unsigned index = 0, uint32_t color = DefaultOnColor)
    {
      this->LED     = new Adafruit_NeoPixel(nleds, pin, NEO_GRB + NEO_KHZ800);
      this->state   = state;
      this->index   = index;
      this->color   = color;
      this->LED->begin();
      this->write(state);
    }

    // GPIO pin methods

    virtual void write(bool state)
    {
      this->LED->setPixelColor(this->index, state ? this->color : 0);
      this->LED->show();
      this->state = state;
    }

    virtual bool read(void)
    {
      return this->state;
    }

    void setColor(uint32_t color)
    {
      this->color = color;
    }

    // GPIO pin operators

#ifdef ENABLE_ASSIGNMENT_OPERATOR
    operator bool(void)
    {
      return this->read();
    }

    void operatior =(const bool state)
    {
      this->write(state);
    }
#endif

  private:

    Adafruit_NeoPixel *LED;
    bool state;
    uint16_t index;
    uint32_t color;
  };
}

#endif
