// LPC1114 I/O Processor Version Test

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

void setup()
{
  Serial.begin(115200);
  while (!BOOTSEL);
  Serial.print("LPC1114 I/O Processor Version Test\r\n\n");
  Serial.flush();

  // Board specific I2C bus initialization

#if   defined(ARDUINO_CYTRON_MAKER_NANO_RP2040)
  // Maker Port 0
  Wire.setSCL(1);
  Wire.setSDA(0);
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

  SPIAGENT_COMMAND_MSG_t cmd;
  SPIAGENT_RESPONSE_MSG_t resp;

  memset(&cmd, 0, sizeof(cmd));
  memset(&resp, 0, sizeof(resp));

  cmd.command = SPIAGENT_CMD_NOP;
  cmd.pin     = 0;
  cmd.data    = 0;

  IOP.Transaction(&cmd, &resp);
  LPC1114_IOP::CheckError("NOP", resp.error);

  Serial.print("The LPC1114 I/O Processor firmware version is ");
  Serial.println(resp.data, DEC);
  Serial.flush();

  cmd.command = SPIAGENT_CMD_GET_SFR;
  cmd.pin     = 0x400483F4; // LPC1114 Device ID register
  cmd.data    = 0;

  IOP.Transaction(&cmd, &resp);
  LPC1114_IOP::CheckError("SFR GET", resp.error);

  Serial.print("The LPC1114 device ID is ");
  Serial.println(resp.data, HEX);
  Serial.flush();
}

void loop()
{
}
