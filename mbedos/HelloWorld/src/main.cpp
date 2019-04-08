// Console I/O Test

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

#include <mbed.h>

Serial console(SERIAL_TX, SERIAL_RX);

int main(void)
{
  console.baud(115200);
  console.printf("\033[H\033[2J%s Console Output Test (" __DATE__ " " __TIME__
    ")\r\n\n", BOARDNAME);
  console.printf("Project:    %s\r\n", PROJECTNAME);
  console.printf("OS:         ARM Mbed OS %d.%d.%d\r\n", MBED_MAJOR_VERSION,
    MBED_MINOR_VERSION, MBED_PATCH_VERSION);
  console.printf("Tool chain: %s\r\n", TOOLCHAINNAME);
  console.printf("Compiler:   %s\r\n", __VERSION__);
  console.printf("Target:     %s\r\n", BOARDNAME);
  console.printf("CPU Freq:   %1.1f MHz\r\n\n", SystemCoreClock/1000000.0);

  console.printf("Hello, World\r\n\n");

  for (;;)
  {
    console.printf("\rTick");
    wait(1.0);
    console.printf("\rTock");
    wait(1.0);
  }
}
