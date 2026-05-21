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

#ifndef _MUNTSTECH_LED_H_
#define _MUNTSTECH_LED_H_

#include <GPIO-Neopixel.h>

using namespace MuntsTech::GPIO::NeoPixel;

namespace MuntsTech::Factories::LED
{
  // Create board specific default user LED (e.g. LED_BUILTIN) object instance
  MuntsTech::Interfaces::GPIO::Pin Create(bool state = false);

  // Create arbitrary GPIO LED object instance
  MuntsTech::Interfaces::GPIO::Pin CreateGPIO(unsigned pin,
    bool state = false, bool activelow = false);

  // Create arbitrary NeoPixel LED object instance
  MuntsTech::Interfaces::GPIO::Pin CreateNeoPixel(Adafruit_NeoPixel *chain,
    unsigned index, bool state = false, uint32_t color = DefaultOnColor);
}

#endif
