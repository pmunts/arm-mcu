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

#ifndef LED
#define LED	D13
#endif

// Nucleo-32 boards need a momentary button switch from D12 to ground

#ifdef Nucleo_32
#ifndef BUTTON_PIN
#define BUTTON_PIN	12
#endif
#ifndef BUTTON_MODE
#define BUTTON_MODE	INPUT_PULLUP
#endif
#endif

// Nucleo-64 boards have an on-board user button switch

#ifdef Nucleo_64
#endif
#ifndef BUTTON_PIN
#define BUTTON_PIN	USER_BTN
#endif
#ifndef BUTTON_MODE
#define BUTTON_MODE	INPUT
#endif
#endif
