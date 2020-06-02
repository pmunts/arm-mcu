// GHI FEZ Board PWM Output Test

// Copyright (C)2018, Philip Munts, President, Munts AM Corp.
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

// Create an array of PWM outputs

PwmOut outputs[] =
{
  PwmOut(PB_3),   // D3
  PwmOut(PB_4),   // D5
  PwmOut(PB_10),  // D6
  PwmOut(PC_7),   // D9
  PwmOut(PB_6),   // D10
  PwmOut(PA_7),   // D11
};

int main(void)
{
  int i;
  int d;

  console.baud(115200);
  console.printf("\033[H\033[2J%s PWM Output Test (" __DATE__ " " __TIME__
    ")\r\n\n", BOARDNAME);
  console.printf("Project:    %s\r\n", PROJECTNAME);
  console.printf("Board:      %s\r\n", BOARDNAME);
  console.printf("OS:         ARM Mbed OS %d.%d.%d\r\n", MBED_MAJOR_VERSION,
    MBED_MINOR_VERSION, MBED_PATCH_VERSION);
  console.printf("Tool chain: %s\r\n", TOOLCHAINNAME);
  console.printf("Compiler:   %s\r\n", __VERSION__);
  console.printf("Target:     %s\r\n", TARGETNAME);
  console.printf("CPU Freq:   %1.1f MHz\r\n\n", SystemCoreClock/1000000.0);

  // Initialize PWM output pulse frequencies

  for (PwmOut &outp : outputs)
    outp.period(0.001);

  // Sweep output duty cycle back and forth

  for (;;)
  {
    for (d = 0; d <= 100; d++)
    {
      for (PwmOut &outp : outputs)
        outp = d/100.0;

      ThisThread::sleep_for(50);
    }

    for (d = 100; d >= 0; d--)
    {
      for (PwmOut &outp : outputs)
        outp = d/100.0;

      ThisThread::sleep_for(50);
    }
  }
}
