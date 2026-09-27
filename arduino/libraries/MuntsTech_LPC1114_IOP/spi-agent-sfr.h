/* Declarations for the Raspberry Pi LPC1114 I/O Processor Expansion Board SPI Agent */

// Copyright (C)2013-2018, Philip Munts, President, Munts AM Corp.
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

#ifndef SPI_AGENT_SFR_H
#define SPI_AGENT_SFR_H

#define IS_SFR(addr)		(((addr >= 0x40000000) && (addr < 0x40080000)) || \
				 ((addr >= 0x50000000) && (addr < 0x50200000)))

// Define some well-known SFR's -- see the LPC11xx User Manual UM10398
// for details

#define LPC1114_DEVICE_ID	0x400483F4
#define LPC1114_GPIO1DATA	0x50010CFC
#define LPC1114_U0SCR		0x4000801C

_BEGIN_STD_C

#ifdef __unix__
// SPI Agent Firmware SFR (Special Function Register) services provided by
// libspiagent

extern void spiagent_sfr_get(uint32_t address, uint32_t *data, int32_t *error);

extern void spiagent_sfr_put(uint32_t address, uint32_t data, int32_t *error);
#endif

_END_STD_C

#endif
