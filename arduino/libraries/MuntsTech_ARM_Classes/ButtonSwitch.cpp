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
#include <ButtonSwitch.h>

// Create board specific default user button (e.g. USER_BTN) object instance

MuntsTech::Interfaces::GPIO::Pin MuntsTech::Factories::ButtonSwitch::Create(void)
{
#if defined(USERBUTTON_PIN) && defined(USERBUTTON_MODE) && defined(USERBUTTON_ACTIVELOW)
  // Make macro defined user button switch
  return Create(USERBUTTON_PIN, USERBUTTON_MODE, USERBUTTON_ACTIVELOW);
#elifdef ENABLE_GROVE_LED_BUTTON_D2
  // Active low button switch on D3
  return Create(D3, INPUT, true);
#elifdef ARDUINO_CYTRON_MAKER_NANO_RP2040
  // Active low button switch on GP20
  return Create(20, INPUT, true);
#elifdef ARDUINO_DISCO_F407VG
  // STM32F4-Discovery has an on-board active high button switch.
  return Create(USER_BTN, INPUT, false);
#elifdef ARDUINO_NUCLEO_64
  // Nucleo-64 boards have an on-board active low button switch.
  return Create(USER_BTN, INPUT, true);
#elifdef ARDUINO_NUCLEO_144
  // Nucleo-144 boards have an on-board active high button switch.
  return Create(USER_BTN, INPUT, false);
#else
  // External active low button switch on D3
  return Create(D3, INPUT_PULLUP, true);
#endif
}

// Create arbitrary button switch object instance

MuntsTech::Interfaces::GPIO::Pin MuntsTech::Factories::ButtonSwitch::Create(unsigned pin,
 unsigned mode, bool activelow)
{
  return new MuntsTech::GPIO::Arduino::Pin_Class(pin, mode, activelow);
}
