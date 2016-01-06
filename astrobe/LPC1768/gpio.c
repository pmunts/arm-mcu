// Generate bitband addresses for LPC1768 GPIO pins

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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GPIOBASE	0x2009C000
#define MAXPORTS	5
#define PINSPERPORT	32
#define bit_band_base	0x22000000

unsigned long int bit_word_addr(unsigned long int byte_offset, unsigned long int bit_number)
{
  return bit_band_base + (byte_offset*32) + (bit_number*4);
}

int main(void)
{
  int port, bit, pinnumber;
  unsigned portbase;

  printf("MODULE GPIO;\n\n");
  printf("(* Bitband GPIO pin definitions for the LPC1768 Cortex-M3 microcontroller *)\n\n");
  printf("(* Copyright (C)2015, Philip Munts, President, Munts AM Corp.                  *)\n");
  printf("(*                                                                             *)\n");
  printf("(* Redistribution and use in source and binary forms, with or without          *)\n");
  printf("(* modification, are permitted provided that the following conditions are met: *)\n");
  printf("(*                                                                             *)\n");
  printf("(* * Redistributions of source code must retain the above copyright notice,    *)\n");
  printf("(*   this list of conditions and the following disclaimer.                     *)\n");
  printf("(*                                                                             *)\n");
  printf("(* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS \"AS IS\" *)\n");
  printf("(* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE   *)\n");
  printf("(* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE  *)\n");
  printf("(* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE   *)\n");
  printf("(* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR         *)\n");
  printf("(* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF        *)\n");
  printf("(* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS    *)\n");
  printf("(* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN     *)\n");
  printf("(* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)     *)\n");
  printf("(* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE  *)\n");
  printf("(* POSSIBILITY OF SUCH DAMAGE.                                                 *)\n\n");
  printf("(* GPIO pins are numbered sequentially from the least significant bit of the   *)\n");
  printf("(* lowest GPIO port to the highest port and bit.                               *)\n\n");
  printf("(* Each GPIO pin has three constants defined for it: DirN, MaskN, and PinN.    *)\n");
  printf("(* These map to the Cortex-M3 bitband addresses for that particular GPIO pin.  *)\n\n");
  printf("CONST\n");

  for (port = 0; port < MAXPORTS; port++)
    for (bit = 0; bit < PINSPERPORT; bit++)
    {
      pinnumber = port*PINSPERPORT + bit;
      portbase = GPIOBASE - 0x20000000 + port*0x20;

      printf("  Dir%-3d*  = %08lXH; (* P%d.%-2d *)\n", pinnumber, bit_word_addr(portbase + 0x00, bit), port, bit);
      printf("  Mask%-3d* = %08lXH;\n",   pinnumber, bit_word_addr(portbase + 0x10, bit));
      printf("  Pin%-3d*  = %08lXH;\n\n", pinnumber, bit_word_addr(portbase + 0x14, bit));
    }

  printf("(* Mask constants *)\n\n");
  printf("  UNMASKED* = 0;\n");
  printf("  MASKED*   = 1;\n\n");
  printf("(* Data direction constants *)\n\n");
  printf("  INPUT*    = 0;\n");
  printf("  OUTPUT*   = 1;\n\n");
  printf("(* Logic level constants *)\n\n");
  printf("  HIGH*     = 1;\n");
  printf("  LOW*      = 0;\n");
  printf("  ON*       = 1;\n");
  printf("  OFF*      = 0;\n\n");
  printf("END GPIO.\n");

  exit(0);
}
