/* Simple A/D Converter Test program */

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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cpu.h>

#define MAX_CHANNELS	8

int main(void)
{
  bool ValidChannels[MAX_CHANNELS];
  unsigned channel;

  cpu_init(DEFAULT_CPU_FREQ);
  systick_init(100, NULL);
  serial_stdio(CONSOLE_PORT);

  printf("\033[H\033[2J%s A/D Converter Test (" __DATE__ " " __TIME__ ")\n\n", MCUFAMILYNAME);
  puts(revision);
  printf("\nCPU Freq:%u Hz  Compiler:%s %s %s\n\n", (unsigned int) SystemCoreClock,
    __COMPILER__, __VERSION__, __ABI__);

// Initialize A/D inputs

  memset(ValidChannels, 0, sizeof(ValidChannels));

  for (channel = 0; channel < MAX_CHANNELS; channel++)
    if (adc_init(NULL, channel) == 0)
      ValidChannels[channel] = true;

  for (;;)
  {
    for (channel = 0; channel < MAX_CHANNELS; channel++)
      if (ValidChannels[channel])
        printf("ADC%d:%05d ", channel, adc_read(NULL, channel));

    putchar('\r');
    fflush(stdout);

    sleep(1);
  }
}
