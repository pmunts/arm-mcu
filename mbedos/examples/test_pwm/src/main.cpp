// ARM MbedOS PWM Output Test

// Copyright (C)2018-2020, Philip Munts, President, Munts AM Corp.
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
#include <appinfo.h>

BufferedSerial UART(SERIAL_TX, SERIAL_RX, 115200);

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
  int d;

  MUNTS::AppInfo::Banner("ARM Mbed OS PWM Output Test");

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

      ThisThread::sleep_for(50ms);
    }

    for (d = 100; d >= 0; d--)
    {
      for (PwmOut &outp : outputs)
        outp = d/100.0;

      ThisThread::sleep_for(50ms);
    }
  }
}
