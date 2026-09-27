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

#ifndef SPI_AGENT_ADC_H
#define SPI_AGENT_ADC_H

// LPC1114 I/O Processor GPIO special function pin aliases

#define LPC1114_AD1		LPC1114_GPIO0
#define LPC1114_AD2		LPC1114_GPIO1
#define LPC1114_AD3		LPC1114_GPIO2
#define LPC1114_AD4		LPC1114_GPIO3
#define LPC1114_AD5		LPC1114_GPIO4

#define LPC1114_ADC_SPAN	3.3
#define LPC1114_ADC_BITS	10
#define LPC1114_ADC_STEPS	1024
#define LPC1114_ADC_STEPSIZE	0.00322265625

#define IS_ANALOG(p) ((p >= LPC1114_AD1) && (p <= LPC1114_AD5))

_BEGIN_STD_C

#ifdef __unix__
// Analog input services provided by libspiagent

extern void spiagent_analog_configure(uint32_t pin, int32_t *error);

extern void spiagent_analog_get(uint32_t pin, float *voltage, int32_t *error);
#endif

_END_STD_C

#endif
