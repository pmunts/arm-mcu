/* Abstract services for controlling and using the system tick timer */

// $Id$

// Copyright (C)2015, Philip Munts, President, Munts AM Corp.
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

static unsigned systick_rate;

static void (*systick_callback)(void);

static volatile unsigned SleepCounter = 0;
static volatile unsigned long long UptimeCounter = 0;

void SysTick_Handler(void)
{
  UptimeCounter++;

  if (SleepCounter)
  {
    SleepCounter--;
  }

  if (systick_callback)
    (*systick_callback)();
}

int systick_init(unsigned rate, void (*callback)(void))
{
  errno_r = 0;

  // Validate parameters

  if (SystemCoreClock/rate > 16777216)
  {
    errno_r = EINVAL;
    return -1;
  }

  // Save the systick rate

  systick_rate = rate;

  // Save the callback function

  systick_callback = callback;

  SysTick_Config(SystemCoreClock / systick_rate);
  return 0;
}

void millisleep(unsigned milliseconds)
{
  SleepCounter = systick_rate*milliseconds/1000;
  while (SleepCounter) __WFI();
}

unsigned sleep(unsigned seconds)
{
  millisleep(seconds*1000);
  return 0;
}

unsigned uptime(void)
{
  return UptimeCounter/systick_rate;
}
