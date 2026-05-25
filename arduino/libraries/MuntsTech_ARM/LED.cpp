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

#include <Arduino_ARM.h>
#include <LED.h>

// Configure a board specific NeoPixel chain

#if defined(ARDUINO_SPARKFUN_PROMICRO_RP2040) || defined(ARDUINO_SPARKFUN_PROMICRO_RP2350)
static Adafruit_NeoPixel _LED_NeoPixelChain(1, LED_BUILTIN, NEO_GRB + NEO_KHZ800);
#elif defined(ARDUINO_WAVESHARE_RP2040_ZERO) || defined(ARDUINO_WAVESHARE_RP2350_ZERO)
static Adafruit_NeoPixel _LED_NeoPixelChain(1, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);
#endif

// Create board specific default user LED (e.g. LED_BUILTIN) object instance

MuntsTech::Interfaces::GPIO::Pin MuntsTech::Factories::LED::Create(bool state)
{
#ifdef USERLED
  // Use make defined GPIO user LED (overrides board default user LED)
  return CreateGPIO(USERLED, state);
#elifdef ENABLE_GROVE_LED_BUTTON_D2
  // GPIO user LED on D2 (overrides board default user LED)
  return CreateGPIO(D2, state);
#elifdef ARDUINO_CYTRON_MAKER_NANO_RP2040
  // GPIO user LED on GP18 aka D13
  return CreateGPIO(18, state);
#elif defined(ARDUINO_PIMORONI_TINY2040) || defined(ARDUINO_PIMORONI_TINY2350)
  // Active low GPIO user LED
  return CreateGPIO(LED_BUILTIN, state, true);
#elif defined(ARDUINO_SEEED_XIAO_RP2040) || defined(ARDUINO_SEEED_XIAO_RP2350)
  // Active low GPIO user LED
  return CreateGPIO(LED_BUILTIN, state, true);
#elif defined(ARDUINO_SPARKFUN_PROMICRO_RP2040) || defined(ARDUINO_SPARKFUN_PROMICRO_RP2350)
  // NeoPixel user LED
  return CreateNeoPixel(&_LED_NeoPixelChain, 0, state);
#elifdef LED_BUILTIN
  // Most other boards have an active high GPIO LED, often connected to D13
  return CreateGPIO(LED_BUILTIN, state);
#else
  return nullptr;
#endif
}

// Create arbitrary GPIO LED object instance

MuntsTech::Interfaces::GPIO::Pin MuntsTech::Factories::LED::CreateGPIO(unsigned pin,
  bool state, bool activelow)
{
  return new MuntsTech::GPIO::Arduino::Pin_Class(pin, OUTPUT, activelow, state);
}

// Create arbitrary NeoPixel LED object instance

MuntsTech::Interfaces::GPIO::Pin MuntsTech::Factories::LED::CreateNeoPixel(
  Adafruit_NeoPixel *chain, unsigned index, bool state, uint32_t color)
{
  chain->begin();
  return new MuntsTech::GPIO::NeoPixel::Pin_Class(chain, index, state, color);
}
