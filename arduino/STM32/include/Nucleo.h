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

#ifndef _NUCLEO_H_
#define _NUCLEO_H_

// Arduino compatible GPIO pins

#define D0	0	// RXD
#define D1	1	// TXD
#define D2	2
#define D3	3	// PWM
#define D4	4
#define D5	5	// PWM
#define D6	6	// PWM
#define D7	7
#define D8	8
#define D9	9	// PWM
#define D10	10	// PWM CS
#define D11	11	// PWM MOSI
#define D12	12	//     MISO
#define D13	13	// LED SCLK
#define LED	D13

// Nucleo-32 (Nano footprint) boards need a momentary switch connected to D12
#ifdef Nucleo_32
#define BUTTON	12
#define BUTTON_MODE	INPUT_PULLUP
#endif

// Nucleo-64 (Uno footprint) boards have an on-board momentary switch
#ifdef Nucleo_64
#define BUTTON	USER_BTN
#define BUTTON_MODE	INPUT
#endif

#endif
