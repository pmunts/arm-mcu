// LPC1114 I/O Processor LED Test

// Copyright (C)2017-2026, Philip Munts dba Munts Technologies.
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

#include <Arduino_ARM.h>
#include <LPC1114_IOP.h>

LPC1114_IOP::Transport_Class IOP;
LPC1114_IOP::GPIO LED;

void setup()
{
  // Board specific I2C bus initialization

#if   defined(ARDUINO_CYTRON_MAKER_NANO_RP2040)
  // Maker Port 0
  Wire.setSCL(1);
  Wire.setSDA(0);
  IOP.Init(&Wire);
#elif defined(ARDUINO_SEEED_XIAO_RP2040)
  // Edge pins D4 and D5
  Wire.setSCL(7);
  Wire.setSDA(6);
  IOP.Init(&Wire);
#elif defined(ARDUINO_SEEED_XIAO_RP2350)
  // Edge pins D4 and D5
  Wire.setSCL(7);
  Wire.setSDA(6);
  IOP.Init(&Wire);
#elif defined(ARDUINO_SPARKFUN_PROMICRO_RP2040) || defined(ARDUINO_SPARKFUN_PROMICRO_RP2350)
  Wire.setSCL(17);
  Wire.setSDA(16);
  IOP.Init(&Wire);
#elif defined(ARDUINO_PIMORONI_TINY2350)
  Wire.setSCL(13);
  Wire.setSDA(12);
  IOP.Init(&Wire);
#else
  // Raspberry Pi Pico default
  Wire.setSCL(5);
  Wire.setSDA(4);
  IOP.Init(&Wire);
#endif

  LED.Init(&IOP, LPC1114_LED, LPC1114_GPIO_OUTPUT, false);
}

void loop()
{
  // Toggle the LED

  LED = !LED;
  delay(1000);
}
