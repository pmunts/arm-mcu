/* Abstract services for controlling LED's */

// Copyright (C)2013-2018, Philip Munts, President, Munts AM Corp.
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

#include <cpu.h>

// Initialize the LED's (to the off state)

void LEDS_initialize(void)
{
#ifdef LED1_PIN
  gpio_configure(LED1_PIN, GPIO_DIR_OUTPUT);
#endif

#ifdef LED2_PIN
  gpio_configure(LED2_PIN, GPIO_DIR_OUTPUT);
#endif

#ifdef LED3_PIN
  gpio_configure(LED3_PIN, GPIO_DIR_OUTPUT);
#endif

#ifdef LED4_PIN
  gpio_configure(LED4_PIN, GPIO_DIR_OUTPUT);
#endif

#ifdef LED5_PIN
  gpio_configure(LED5_PIN, GPIO_DIR_OUTPUT);
#endif

#ifdef LED6_PIN
  gpio_configure(LED6_PIN, GPIO_DIR_OUTPUT);
#endif

#ifdef LED7_PIN
  gpio_configure(LED7_PIN, GPIO_DIR_OUTPUT);
#endif

#ifdef LED8_PIN
  gpio_configure(LED8_PIN, GPIO_DIR_OUTPUT);
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
  result += !gpio_read(LED1_PIN);
#else
  result += gpio_read(LED1_PIN);
#endif
#endif

#ifdef LED2_PIN
#ifdef LED2_ACTIVELOW
  result += !gpio_read(LED2_PIN) << 1;
#else
  result += gpio_read(LED2_PIN) << 1;
#endif
#endif

#ifdef LED3_PIN
#ifdef LED3_ACTIVELOW
  result += !gpio_read(LED3_PIN) << 2;
#else
  result += gpio_read(LED3_PIN) << 2;
#endif
#endif

#ifdef LED4_PIN
#ifdef LED4_ACTIVELOW
  result += !gpio_read(LED4_PIN) << 3;
#else
  result += gpio_read(LED4_PIN) << 3;
#endif
#endif

#ifdef LED5_PIN
#ifdef LED5_ACTIVELOW
  result += !gpio_read(LED5_PIN) << 4;
#else
  result += gpio_read(LED5_PIN) << 4;
#endif
#endif

#ifdef LED6_PIN
#ifdef LED6_ACTIVELOW
  result += !gpio_read(LED6_PIN) << 5;
#else
  result += gpio_read(LED6_PIN) << 5;
#endif
#endif

#ifdef LED7_PIN
#ifdef LED7_ACTIVELOW
  result += !gpio_read(LED7_PIN) << 6;
#else
  result += gpio_read(LED7_PIN) << 6;
#endif
#endif

#ifdef LED8_PIN
#ifdef LED8_ACTIVELOW
  result += !gpio_read(LED8_PIN) << 7;
#else
  result += gpio_read(LED8_PIN) << 7;
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
  gpio_write(LED1_PIN, ~mask & 0x01);
#else
  gpio_write(LED1_PIN, mask & 0x01);
#endif
#endif

#ifdef LED2_PIN
#ifdef LED2_ACTIVELOW
  gpio_write(LED2_PIN, ~mask & 0x02);
#else
  gpio_write(LED2_PIN, mask & 0x02);
#endif
#endif

#ifdef LED3_PIN
#ifdef LED3_ACTIVELOW
  gpio_write(LED3_PIN, ~mask & 0x04);
#else
  gpio_write(LED3_PIN, mask & 0x04);
#endif
#endif

#ifdef LED4_PIN
#ifdef LED4_ACTIVELOW
  gpio_write(LED4_PIN, ~mask & 0x08);
#else
  gpio_write(LED4_PIN, mask & 0x08);
#endif
#endif

#ifdef LED5_PIN
#ifdef LED5_ACTIVELOW
  gpio_write(LED5_PIN, ~mask & 0x10);
#else
  gpio_write(LED5_PIN, mask & 0x10);
#endif
#endif

#ifdef LED6_PIN
#ifdef LED6_ACTIVELOW
  gpio_write(LED6_PIN, ~mask & 0x20);
#else
  gpio_write(LED6_PIN, mask & 0x20);
#endif
#endif

#ifdef LED7_PIN
#ifdef LED7_ACTIVELOW
  gpio_write(LED7_PIN, ~mask & 0x40);
#else
  gpio_write(LED7_PIN, mask & 0x40);
#endif
#endif

#ifdef LED8_PIN
#ifdef LED8_ACTIVELOW
  gpio_write(LED8_PIN, ~mask & 0x80);
#else
  gpio_write(LED8_PIN, mask & 0x80);
#endif
#endif
}
