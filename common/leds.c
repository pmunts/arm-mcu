/* Abstract services for controlling LED's */

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

// Initialize the LED's (to the off state)

void LEDS_initialize(void)
{
#ifdef LED1_PIN
#ifdef _GPIOPINS_H
  gpiopin_configure(LED1_PIN, GPIOPIN_OUTPUT);
#endif
#ifdef _GPIO_H
  gpio_configure(LED1_PIN, GPIO_MODE_OUTPUT);
#endif
#endif

#ifdef LED2_PIN
#ifdef _GPIOPINS_H
  gpiopin_configure(LED2_PIN, GPIOPIN_OUTPUT);
#endif
#ifdef _GPIO_H
  gpio_configure(LED2_PIN, GPIO_MODE_OUTPUT);
#endif
#endif

#ifdef LED3_PIN
#ifdef _GPIOPINS_H
  gpiopin_configure(LED3_PIN, GPIOPIN_OUTPUT);
#endif
#ifdef _GPIO_H
  gpio_configure(LED3_PIN, GPIO_MODE_OUTPUT);
#endif
#endif

#ifdef LED4_PIN
#ifdef _GPIOPINS_H
  gpiopin_configure(LED4_PIN, GPIOPIN_OUTPUT);
#endif
#ifdef _GPIO_H
  gpio_configure(LED4_PIN, GPIO_MODE_OUTPUT);
#endif
#endif

#ifdef LED5_PIN
#ifdef _GPIOPINS_H
  gpiopin_configure(LED5_PIN, GPIOPIN_OUTPUT);
#endif
#ifdef _GPIO_H
  gpio_configure(LED5_PIN, GPIO_MODE_OUTPUT);
#endif
#endif

#ifdef LED6_PIN
#ifdef _GPIOPINS_H
  gpiopin_configure(LED6_PIN, GPIOPIN_OUTPUT);
#endif
#ifdef _GPIO_H
  gpio_configure(LED6_PIN, GPIO_MODE_OUTPUT);
#endif
#endif

#ifdef LED7_PIN
#ifdef _GPIOPINS_H
  gpiopin_configure(LED7_PIN, GPIOPIN_OUTPUT);
#endif
#ifdef _GPIO_H
  gpio_configure(LED7_PIN, GPIO_MODE_OUTPUT);
#endif
#endif

#ifdef LED8_PIN
#ifdef _GPIOPINS_H
  gpiopin_configure(LED8_PIN, GPIOPIN_OUTPUT);
#endif
#ifdef _GPIO_H
  gpio_configure(LED8_PIN, GPIO_MODE_OUTPUT);
#endif
#endif

  LEDS_set(0);	// Turn off all LEDs at startup
}

// Get LED states.  A 1 bit in the result indicates the LED is on.
// A 0 bit in the result indicates the LED is off.

unsigned long int LEDS_get(void)
{
  unsigned long int result = 0;

#ifdef LED1_PIN
#ifdef LED1_ACTIVELOW
#ifdef _GPIOPINS_H
  result += !LED1_OUTPUT;
#endif
#ifdef _GPIO_H
  result += !gpio_read(LED1_PIN);
#endif
#else
#ifdef _GPIOPINS_H
  result += LED1_OUTPUT;
#endif
#ifdef _GPIO_H
  result += gpio_read(LED1_PIN);
#endif
#endif
#endif

#ifdef LED2_PIN
#ifdef LED2_ACTIVELOW
#ifdef _GPIOPINS_H
  result += !LED2_OUTPUT << 1;
#endif
#ifdef _GPIO_H
  result += !gpio_read(LED2_PIN) << 1;
#endif
#else
#ifdef _GPIOPINS_H
  result += LED2_OUTPUT << 1;
#endif
#ifdef _GPIO_H
  result += gpio_read(LED2_PIN) << 1;
#endif
#endif
#endif

#ifdef LED3_PIN
#ifdef LED3_ACTIVELOW
#ifdef _GPIOPINS_H
  result += !LED3_OUTPUT << 2;
#endif
#ifdef _GPIO_H
  result += !gpio_read(LED3_PIN) << 2;
#endif
#else
#ifdef _GPIOPINS_H
  result += LED3_OUTPUT << 2;
#endif
#ifdef _GPIO_H
  result += gpio_read(LED3_PIN) << 2;
#endif
#endif
#endif

#ifdef LED4_PIN
#ifdef LED4_ACTIVELOW
#ifdef _GPIOPINS_H
  result += !LED4_OUTPUT << 3;
#endif
#ifdef _GPIO_H
  result += !gpio_read(LED4_PIN) << 3;
#endif
#else
#ifdef _GPIOPINS_H
  result += LED4_OUTPUT << 3;
#endif
#ifdef _GPIO_H
  result += gpio_read(LED4_PIN) << 3;
#endif
#endif
#endif

#ifdef LED5_PIN
#ifdef LED5_ACTIVELOW
#ifdef _GPIOPINS_H
  result += !LED5_OUTPUT << 4;
#endif
#ifdef _GPIO_H
  result += !gpio_read(LED5_PIN) << 4;
#endif
#else
#ifdef _GPIOPINS_H
  result += LED5_OUTPUT << 4;
#endif
#ifdef _GPIO_H
  result += gpio_read(LED5_PIN) << 4;
#endif
#endif
#endif

#ifdef LED6_PIN
#ifdef LED6_ACTIVELOW
#ifdef _GPIOPINS_H
  result += !LED6_OUTPUT << 5;
#endif
#ifdef _GPIO_H
  result += !gpio_read(LED6_PIN) << 5;
#endif
#else
#ifdef _GPIOPINS_H
  result += LED6_OUTPUT << 5;
#endif
#ifdef _GPIO_H
  result += gpio_read(LED6_PIN) << 5;
#endif
#endif
#endif

#ifdef LED7_PIN
#ifdef LED7_ACTIVELOW
#ifdef _GPIOPINS_H
  result += !LED7_OUTPUT << 6;
#endif
#ifdef _GPIO_H
  result += !gpio_read(LED7_PIN) << 6;
#endif
#else
#ifdef _GPIOPINS_H
  result += LED7_OUTPUT << 6;
#endif
#ifdef _GPIO_H
  result += gpio_read(LED7_PIN) << 6;
#endif
#endif
#endif

#ifdef LED8_PIN
#ifdef LED8_ACTIVELOW
#ifdef _GPIOPINS_H
  result += !LED8_OUTPUT << 7;
#endif
#ifdef _GPIO_H
  result += !gpio_read(LED8_PIN) << 7;
#endif
#else
#ifdef _GPIOPINS_H
  result += LED8_OUTPUT << 7;
#endif
#ifdef _GPIO_H
  result += gpio_read(LED8_PIN) << 7;
#endif
#endif
#endif

  return result;
}

// Set LED states.  A 1 bit in the mask indicates the LED should be turned on.
// A 0 bit in the mask indicates the LED should be turned off.

void LEDS_set(unsigned long int mask)
{
#ifdef LED1_PIN
#ifdef LED1_ACTIVELOW
#ifdef _GPIOPINS_H
  LED1_OUTPUT = ~mask;
#endif
#ifdef _GPIO_H
  gpio_write(LED1_PIN, ~mask);
#endif
#else
#ifdef _GPIOPINS_H
  LED1_OUTPUT = mask;
#endif
#ifdef _GPIO_H
  gpio_write(LED1_PIN, mask);
#endif
#endif
#endif

#ifdef LED2_PIN
#ifdef LED2_ACTIVELOW
#ifdef _GPIOPINS_H
  LED2_OUTPUT = ~mask >> 1;
#endif
#ifdef _GPIO_H
  gpio_write(LED2_PIN, ~mask >> 1);
#endif
#else
#ifdef _GPIOPINS_H
  LED2_OUTPUT = mask >> 1;
#endif
#ifdef _GPIO_H
  gpio_write(LED2_PIN, mask >> 1);
#endif
#endif
#endif

#ifdef LED3_PIN
#ifdef LED3_ACTIVELOW
#ifdef _GPIOPINS_H
  LED3_OUTPUT = ~mask >> 2;
#endif
#ifdef _GPIO_H
  gpio_write(LED3_PIN, ~mask >> 2);
#endif
#else
#ifdef _GPIOPINS_H
  LED3_OUTPUT = mask >> 2;
#endif
#ifdef _GPIO_H
  gpio_write(LED3_PIN, mask >> 2);
#endif
#endif
#endif

#ifdef LED4_PIN
#ifdef LED4_ACTIVELOW
#ifdef _GPIOPINS_H
  LED4_OUTPUT = ~mask >> 3;
#endif
#ifdef _GPIO_H
  gpio_write(LED4_PIN, ~mask >> 3);
#endif
#else
#ifdef _GPIOPINS_H
  LED4_OUTPUT = mask >> 3;
#endif
#ifdef _GPIO_H
  gpio_write(LED4_PIN, mask >> 3);
#endif
#endif
#endif

#ifdef LED5_PIN
#ifdef LED5_ACTIVELOW
#ifdef _GPIOPINS_H
  LED5_OUTPUT = ~mask >> 4;
#endif
#ifdef _GPIO_H
  gpio_write(LED5_PIN, ~mask >> 4);
#endif
#else
#ifdef _GPIOPINS_H
  LED5_OUTPUT = mask >> 4;
#endif
#ifdef _GPIO_H
  gpio_write(LED5_PIN, mask >> 4);
#endif
#endif
#endif

#ifdef LED6_PIN
#ifdef LED6_ACTIVELOW
#ifdef _GPIOPINS_H
  LED6_OUTPUT = ~mask >> 5;
#endif
#ifdef _GPIO_H
  gpio_write(LED6_PIN, ~mask >> 5);
#endif
#else
#ifdef _GPIOPINS_H
  LED6_OUTPUT = mask >> 5;
#endif
#ifdef _GPIO_H
  gpio_write(LED6_PIN, mask >> 5);
#endif
#endif
#endif

#ifdef LED7_PIN
#ifdef LED7_ACTIVELOW
#ifdef _GPIOPINS_H
  LED7_OUTPUT = ~mask >> 6;
#endif
#ifdef _GPIO_H
  gpio_write(LED7_PIN, ~mask >> 6);
#endif
#else
#ifdef _GPIOPINS_H
  LED7_OUTPUT = mask >> 6;
#endif
#ifdef _GPIO_H
  gpio_write(LED7_PIN, mask >> 6);
#endif
#endif
#endif

#ifdef LED8_PIN
#ifdef LED8_ACTIVELOW
#ifdef _GPIOPINS_H
  LED8_OUTPUT = ~mask >> 7;
#endif
#ifdef _GPIO_H
  gpio_write(LED8_PIN, ~mask >> 7);
#endif
#else
#ifdef _GPIOPINS_H
  LED8_OUTPUT = mask >> 7;
#endif
#ifdef _GPIO_H
  gpio_write(LED8_PIN, mask >> 7;
#endif
#endif
#endif
}
