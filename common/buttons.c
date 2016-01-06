/* Abstract services for reading buttons (momentary switches) */

// $Id$

// Copyright (C)2013-2015, Philip Munts, President, Munts AM Corp.
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

static const char revision[] = "$Id$";

#include <cpu.h>

// Configure the button input pins

void buttons_initialize(void)
{
#ifdef BUTTON1_PIN
#ifdef _GPIOPINS_H
  gpiopin_configure(BUTTON1_PIN, GPIOPIN_INPUT);
#endif
#ifdef _GPIO_H
  gpio_configure(BUTTON1_PIN, GPIO_MODE_INPUT);
#endif
#endif

#ifdef BUTTON2_PIN
#ifdef _GPIOPINS_H
  gpiopin_configure(BUTTON2_PIN, GPIOPIN_INPUT);
#endif
#ifdef _GPIO_H
  gpio_configure(BUTTON2_PIN, GPIO_MODE_INPUT);
#endif
#endif

#ifdef BUTTON3_PIN
#ifdef _GPIOPINS_H
  gpiopin_configure(BUTTON3_PIN, GPIOPIN_INPUT);
#endif
#ifdef _GPIO_H
  gpio_configure(BUTTON3_PIN, GPIO_MODE_INPUT);
#endif
#endif

#ifdef BUTTON4_PIN
#ifdef _GPIOPINS_H
  gpiopin_configure(BUTTON4_PIN, GPIOPIN_INPUT);
#endif
#ifdef _GPIO_H
  gpio_configure(BUTTON4_PIN, GPIO_MODE_INPUT);
#endif
#endif

#ifdef BUTTON5_PIN
#ifdef _GPIOPINS_H
  gpiopin_configure(BUTTON5_PIN, GPIOPIN_INPUT);
#endif
#ifdef _GPIO_H
  gpio_configure(BUTTON5_PIN, GPIO_MODE_INPUT);
#endif
#endif

#ifdef BUTTON6_PIN
#ifdef _GPIOPINS_H
  gpiopin_configure(BUTTON6_PIN, GPIOPIN_INPUT);
#endif
#ifdef _GPIO_H
  gpio_configure(BUTTON6_PIN, GPIO_MODE_INPUT);
#endif
#endif

#ifdef BUTTON7_PIN
#ifdef _GPIOPINS_H
  gpiopin_configure(BUTTON7_PIN, GPIOPIN_INPUT);
#endif
#ifdef _GPIO_H
  gpio_configure(BUTTON7_PIN, GPIO_MODE_INPUT);
#endif
#endif

#ifdef BUTTON8_PIN
#ifdef _GPIOPINS_H
  gpiopin_configure(BUTTON8_PIN, GPIOPIN_INPUT);
#endif
#ifdef _GPIO_H
  gpio_configure(BUTTON8_PIN, GPIO_MODE_INPUT);
#endif
#endif
}

// Get button states.  A 1 bit in the result indicates the button is pushed.
// A 0 bit in the result indicates the button is not pushed.

unsigned long int buttons_get(void)
{
  unsigned long int result = 0;

#ifdef BUTTON1_PIN
#ifdef BUTTON1_ACTIVELOW
#ifdef _GPIOPINS_H
  result += !BUTTON1_INPUT;
#endif
#ifdef _GPIO_H
  result += !gpio_read(BUTTON1_PIN);
#endif
#else
#ifdef _GPIOPINS_H
  result += BUTTON1_INPUT;
#endif
#ifdef _GPIO_H
  result += gpio_read(BUTTON1_PIN);
#endif
#endif
#endif

#ifdef BUTTON2_PIN
#ifdef BUTTON2_ACTIVELOW
#ifdef _GPIOPINS_H
  result += !BUTTON2_INPUT << 1;
#endif
#ifdef _GPIO_H
  result += !gpio_read(BUTTON2_PIN) << 1;
#endif
#else
#ifdef _GPIOPINS_H
  result += BUTTON2_INPUT << 1;
#endif
#ifdef _GPIO_H
  result += gpio_read(BUTTON2_PIN) << 1;
#endif
#endif
#endif

#ifdef BUTTON3_PIN
#ifdef BUTTON3_ACTIVELOW
#ifdef _GPIOPINS_H
  result += !BUTTON3_INPUT << 2;
#endif
#ifdef _GPIO_H
  result += !gpio_read(BUTTON3_PIN) << 2;
#endif
#else
#ifdef _GPIOPINS_H
  result += BUTTON3_INPUT << 2;
#endif
#ifdef _GPIO_H
  result += gpio_read(BUTTON3_PIN) << 2;
#endif
#endif
#endif

#ifdef BUTTON4_PIN
#ifdef BUTTON4_ACTIVELOW
#ifdef _GPIOPINS_H
  result += !BUTTON4_INPUT << 3;
#endif
#ifdef _GPIO_H
  result += !gpio_read(BUTTON4_PIN) << 3;
#endif
#else
#ifdef _GPIOPINS_H
  result += BUTTON4_INPUT << 3;
#endif
#ifdef _GPIO_H
  result += gpio_read(BUTTON4_PIN) << 3;
#endif
#endif
#endif

#ifdef BUTTON5_PIN
#ifdef BUTTON5_ACTIVELOW
#ifdef _GPIOPINS_H
  result += !BUTTON5_INPUT << 4;
#endif
#ifdef _GPIO_H
  result += !gpio_read(BUTTON5_PIN) << 4;
#endif
#else
#ifdef _GPIOPINS_H
  result += BUTTON5_INPUT << 4;
#endif
#ifdef _GPIO_H
  result += gpio_read(BUTTON5_PIN) << 4;
#endif
#endif
#endif

#ifdef BUTTON6_PIN
#ifdef BUTTON6_ACTIVELOW
#ifdef _GPIOPINS_H
  result += !BUTTON6_INPUT << 5;
#endif
#ifdef _GPIO_H
  result += !gpio_read(BUTTON6_PIN) << 5;
#endif
#else
#ifdef _GPIOPINS_H
  result += BUTTON6_INPUT << 5;
#endif
#ifdef _GPIO_H
  result += gpio_read(BUTTON6_PIN) << 5;
#endif
#endif
#endif

#ifdef BUTTON7_PIN
#ifdef BUTTON7_ACTIVELOW
#ifdef _GPIOPINS_H
  result += !BUTTON7_INPUT << 6;
#endif
#ifdef _GPIO_H
  result += !gpio_read(BUTTON7_PIN) << 6;
#endif
#else
#ifdef _GPIOPINS_H
  result += BUTTON7_INPUT << 6;
#endif
#ifdef _GPIO_H
  result += gpio_read(BUTTON7_PIN) << 6;
#endif
#endif
#endif

#ifdef BUTTON8_PIN
#ifdef BUTTON8_ACTIVELOW
#ifdef _GPIOPINS_H
  result += !BUTTON8_INPUT << 7;
#endif
#ifdef _GPIO_H
  result += !gpio_read(BUTTON8_PIN) << 7;
#endif
#else
#ifdef _GPIOPINS_H
  result += BUTTON8_INPUT << 7;
#endif
#ifdef _GPIO_H
  result += gpio_read(BUTTON8_PIN) << 7;
#endif
#endif
#endif

  return result;
}
