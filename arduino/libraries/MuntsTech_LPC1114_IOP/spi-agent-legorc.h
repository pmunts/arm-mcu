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

#ifndef SPI_AGENT_LEGORC_H
#define SPI_AGENT_LEGORC_H

_BEGIN_STD_C

// LEGO® Power Functions RC system constants

#define LEGO_RC_CHANNELS	4

// Motor identifiers

typedef enum
{
  LEGORC_ALLSTOP,
  LEGORC_MOTORA,
  LEGORC_MOTORB,
  LEGORC_COMBODIRECT,
  LEGORC_COMBOPWM,
  LEGORC_MOTOR_SENTINEL
} legorc_motor_id_t;

// Direction identifiers

typedef enum
{
  LEGORC_REVERSE,
  LEGORC_FORWARD,
  LEGORC_DIRECTION_SENTINEL
} legorc_direction_id_t;

#ifdef __unix__
// SPI Agent Firmware LEGO® Power Functions Remote Control services provided
// by libspiagent

extern void spiagent_legorc_put(uint32_t pin, uint32_t channel, uint32_t motor,
  uint32_t direction, uint32_t speed, int32_t *error);
#endif

_END_STD_C

#endif
