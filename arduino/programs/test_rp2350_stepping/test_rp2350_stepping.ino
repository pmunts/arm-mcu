// Arduino RP2350 Stepping Test

// Copyright (C)2026, Philip Munts dba Munts Technologies.
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

const uint32_t *CHIP_ID       = (uint32_t *) 0x40000000;
const uint32_t *PACKAGE_SEL   = (uint32_t *) 0x40000004;
const uint32_t *PLATFORM      = (uint32_t *) 0x40000008;
const uint32_t *GITREF_RP2350 = (uint32_t *) 0x40000014;

void setup()
{
  char outbuf[32];

  Serial.begin(115200);
  while (!BOOTSEL);
  Serial.println("\n\n\ecArduino RP2350 Stepping Test\n");
  Serial.print("rp2350_chip_version()  => ");
  Serial.println(rp2350_chip_version());

  Serial.print("CHIP_ID register       => ");
  memset(outbuf, 0, sizeof(outbuf));
  snprintf(outbuf, sizeof(outbuf)-1, "%08X", *CHIP_ID);
  Serial.println(outbuf);

  Serial.print("PACKAGE_SEL register   => ");
  memset(outbuf, 0, sizeof(outbuf));
  snprintf(outbuf, sizeof(outbuf)-1, "%08X", *PACKAGE_SEL);
  Serial.println(outbuf);

  Serial.print("PLATFORM register      => ");
  memset(outbuf, 0, sizeof(outbuf));
  snprintf(outbuf, sizeof(outbuf)-1, "%08X", *PLATFORM);
  Serial.println(outbuf);

  Serial.print("GITREF_RP2350 register => ");
  memset(outbuf, 0, sizeof(outbuf));
  snprintf(outbuf, sizeof(outbuf)-1, "%08X", *GITREF_RP2350);
  Serial.println(outbuf);
}

void loop()
{
}
