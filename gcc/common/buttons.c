/* Abstract services for reading buttons (momentary switches) */

// Copyright (C)2013-2017, Philip Munts, President, Munts AM Corp.
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

// Configure the button input pins

void buttons_initialize(void)
{
#ifdef BUTTON1_PIN
  gpio_configure(BUTTON1_PIN, GPIO_DIR_INPUT);
#endif

#ifdef BUTTON2_PIN
  gpio_configure(BUTTON2_PIN, GPIO_DIR_INPUT);
#endif

#ifdef BUTTON3_PIN
  gpio_configure(BUTTON3_PIN, GPIO_DIR_INPUT);
#endif

#ifdef BUTTON4_PIN
  gpio_configure(BUTTON4_PIN, GPIO_DIR_INPUT);
#endif

#ifdef BUTTON5_PIN
  gpio_configure(BUTTON5_PIN, GPIO_DIR_INPUT);
#endif

#ifdef BUTTON6_PIN
  gpio_configure(BUTTON6_PIN, GPIO_DIR_INPUT);
#endif

#ifdef BUTTON7_PIN
  gpio_configure(BUTTON7_PIN, GPIO_DIR_INPUT);
#endif

#ifdef BUTTON8_PIN
  gpio_configure(BUTTON8_PIN, GPIO_DIR_INPUT);
#endif
}

// Get button states.  A 1 bit in the result indicates the button is pushed.
// A 0 bit in the result indicates the button is not pushed.

unsigned long int buttons_get(void)
{
  unsigned long int result = 0;

#ifdef BUTTON1_PIN
#ifdef BUTTON1_ACTIVELOW
  result += !gpio_read(BUTTON1_PIN);
#else
  result += gpio_read(BUTTON1_PIN);
#endif
#endif

#ifdef BUTTON2_PIN
#ifdef BUTTON2_ACTIVELOW
  result += !gpio_read(BUTTON2_PIN) << 1;
#else
  result += gpio_read(BUTTON2_PIN) << 1;
#endif
#endif

#ifdef BUTTON3_PIN
#ifdef BUTTON3_ACTIVELOW
  result += !gpio_read(BUTTON3_PIN) << 2;
#else
  result += gpio_read(BUTTON3_PIN) << 2;
#endif
#endif

#ifdef BUTTON4_PIN
#ifdef BUTTON4_ACTIVELOW
  result += !gpio_read(BUTTON4_PIN) << 3;
#else
  result += gpio_read(BUTTON4_PIN) << 3;
#endif
#endif

#ifdef BUTTON5_PIN
#ifdef BUTTON5_ACTIVELOW
  result += !gpio_read(BUTTON5_PIN) << 4;
#else
  result += gpio_read(BUTTON5_PIN) << 4;
#endif
#endif

#ifdef BUTTON6_PIN
#ifdef BUTTON6_ACTIVELOW
  result += !gpio_read(BUTTON6_PIN) << 5;
#else
  result += gpio_read(BUTTON6_PIN) << 5;
#endif
#endif

#ifdef BUTTON7_PIN
#ifdef BUTTON7_ACTIVELOW
  result += !gpio_read(BUTTON7_PIN) << 6;
#else
  result += gpio_read(BUTTON7_PIN) << 6;
#endif
#endif

#ifdef BUTTON8_PIN
#ifdef BUTTON8_ACTIVELOW
  result += !gpio_read(BUTTON8_PIN) << 7;
#else
  result += gpio_read(BUTTON8_PIN) << 7;
#endif
#endif

  return result;
}
