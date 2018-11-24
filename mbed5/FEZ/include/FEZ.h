// GPIO Pin Definitions for the GHI FEZ board

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

#ifndef _GHI_FEZ_H_
#define _GHI_FEZ_H_

// Override the GPIO pin definitions for the Nucleo-F401RE board

#define A0		PA_4
#define A1		PA_5
#define A2		PA_6
#define A3		PA_7
#define A4		PB_0
#define A5		PB_1

#define D0		PA_10
#define D1		PA_9
#define D2		PC_1
#define D3		PA_8
#define D4		PC_15
#define D5		PB_8
#define D6		PC_6
#define D7		PC_14
#define D8		PC_0
#define D9		PC_9
#define D10		PC_8
#define D11		PB_5
#define D12		PB_4
#define D13		PB_3

// LEDs

#define LED1		PB_9
#define LED2		PC_10
#define LED3		-1
#define LED4		-1
#define LED_RED		PB_9

// Buttons

#define BUTTON1		PA_15
#define BUTTON2		PC_13
#define USER_BUTTON	PA_15

// Serial console

#define SERIAL_TX	PA_2
#define SERIAL_RX	PA_3

// I2C bus

#define I2C_SCL		PB_6
#define I2C_SDA		PB_7

// SPI bus

#define SPI_MOSI	PB_5
#define SPI_MISO	PB_4
#define SPI_SCK		PB_3
#define SPI_CS		PC_8
#define SPI_SS0		PC_8
#define SPI_SS1		PC_9

// PWM outputs

#define PWM1		PC_6
#define PWM2		PB_8
#define PWM_OUT		PC_6

#endif
