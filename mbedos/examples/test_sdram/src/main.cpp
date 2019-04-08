// LPC4088 Quick Start SDRAM Test

// Copyright (C)2017-2018, Philip Munts, President, Munts AM Corp.
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

#include <stdint.h>

#include <mbed.h>
#include <sdram.h>

Serial console(USBTX, USBRX);

int main()
{
  uint8_t *sdram = (uint8_t *) SDRAM_BASE;
  int i;

  console.baud(115200);

  console.printf("\033[H\033[2J%s SDRAM Test (" __DATE__ " " __TIME__
    ")\r\n\n", BOARDNAME);

  console.printf("DEBUG: Initializing SDRAM controller...\r\n");
  sdram_init();

  console.printf("DEBUG: Filling some SDRAM...\r\n\n");

  for (i = 0; i < 256; i++)
    sdram[i] = i;

  for (;;)
  {
    wait(2.0);

    for (i = 0; i < 256; i++)
      console.printf("SDRAM location %08X is %02X\r\n", i, sdram[i]);
  }
}
