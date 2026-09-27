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

#ifndef SPI_AGENT_TIMER_H
#define SPI_AGENT_TIMER_H

// LPC1114 I/O Processor GPIO special function pin aliases

#define LPC1114_CT32B1_CAP0	LPC1114_GPIO0
#define LPC1114_CT32B1_MAT0	LPC1114_GPIO1
#define LPC1114_CT32B1_MAT1	LPC1114_GPIO2
#define LPC1114_CT32B1_MAT2	LPC1114_GPIO3
#define LPC1114_CT32B1_MAT3	LPC1114_GPIO4
#define LPC1114_CT32B0_CAP0	LPC1114_GPIO5

// LPC1114 peripheral clock frequency

#define PCLK_FREQUENCY		48000000.0

_BEGIN_STD_C

// Enumeration types

typedef enum
{
  LPC1114_CT32B0,
  LPC1114_CT32B1,
  LPC1114_TIMER_ID_SENTINEL
} spiagent_timer_id_t;

typedef enum
{
  LPC1114_TIMER_MODE_DISABLED,
  LPC1114_TIMER_MODE_RESET,
  LPC1114_TIMER_MODE_PCLK,
  LPC1114_TIMER_MODE_CAP0_RISING,
  LPC1114_TIMER_MODE_CAP0_FALLING,
  LPC1114_TIMER_MODE_CAP0_BOTH,
  LPC1114_TIMER_MODE_SENTINEL
} spiagent_timer_mode_t;

typedef enum
{
  LPC1114_TIMER_CAPTURE_EDGE_DISABLED,
  LPC1114_TIMER_CAPTURE_EDGE_CAP0_RISING,
  LPC1114_TIMER_CAPTURE_EDGE_CAP0_FALLING,
  LPC1114_TIMER_CAPTURE_EDGE_CAP0_BOTH,
  LPC1114_TIMER_CAPTURE_EDGE_SENTINEL
} spiagent_timer_capture_edge_t;

typedef enum
{
  LPC1114_TIMER_MATCH0,
  LPC1114_TIMER_MATCH1,
  LPC1114_TIMER_MATCH2,
  LPC1114_TIMER_MATCH3,
  LPC1114_TIMER_MATCH_SENTINEL
} spiagent_timer_match_register_t;

typedef enum
{
  LPC1114_TIMER_MATCH_OUTPUT_DISABLED,
  LPC1114_TIMER_MATCH_OUTPUT_CLEAR,
  LPC1114_TIMER_MATCH_OUTPUT_SET,
  LPC1114_TIMER_MATCH_OUTPUT_TOGGLE,
  LPC1114_TIMER_MATCH_OUTPUT_SENTINEL
} spiagent_timer_match_output_action_t;

#ifdef __unix__
// Timer services provided by libspiagent

extern void spiagent_timer_init(uint32_t timer, int32_t *error);

extern void spiagent_timer_configure_mode(uint32_t timer,
  uint32_t mode, int32_t *error);

extern void spiagent_timer_configure_prescaler(uint32_t timer,
  uint32_t divisor, int32_t *error);

extern void spiagent_timer_configure_capture(uint32_t timer,
  uint32_t edge, uint32_t intr, int32_t *error);

extern void spiagent_timer_configure_match(uint32_t timer, uint32_t match,
  uint32_t value, uint32_t action, uint32_t intr, uint32_t reset, uint32_t stop,
  int32_t *error);

extern void spiagent_timer_get(uint32_t timer, uint32_t *count,
  int32_t *error);

extern void spiagent_timer_get_capture(uint32_t timer, uint32_t *count,
  int32_t *error);

extern void spiagent_timer_get_capture_delta(uint32_t timer, uint32_t *count,
  int32_t *error);
#endif

_END_STD_C

#endif
