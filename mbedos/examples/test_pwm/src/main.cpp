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
#include <FEZ.h>

// Create an array of PWM outputs

PwmOut outputs[] =
{
  PwmOut(PWM0),
  PwmOut(PWM1),
  PwmOut(PWM2),
  PwmOut(PWM3),
  PwmOut(PWM4),
  PwmOut(PWM5),
  PwmOut(PWM6),
  PwmOut(PWM7)
};

int main(void)
{
  int i;
  int d;

  // Initialize PWM output pulse frequencies

  for (i = 0; i < 8; i++)
    outputs[i].period(0.001);

  // Sweep output duty cycle back and forth

  for (;;)
  {
    for (d = 0; d <= 100; d++)
    {
      for (i = 0; i < 8; i++)
        outputs[i] = d/100.0;

      wait_ms(50);
    }

    for (d = 100; d >= 0; d--)
    {
      for (i = 0; i < 8; i++)
        outputs[i] = d/100.0;

      wait_ms(50);
    }
  }
}
