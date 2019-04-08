// GPIO Pin Definitions for the GHI FEZ board

// Copyright (C)2018-2019, Philip Munts, President, Munts AM Corp.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
//=
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

// Arduino expansion headers

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

// Buttons

#define BUTTON1		PA_15
#define BUTTON2		PC_13

// Serial console

#define SERIAL_TX	PA_2
#define SERIAL_RX	PA_3

// I2C bus

#define I2C_SCL		PB_6
#define I2C_SDA		PB_7

// SPI bus

#define SPI_MOSI	D11
#define SPI_MISO	D12
#define SPI_SCK		D13
#define SPI_CS		D10
#define SPI_SS0		D10
#define SPI_SS1		D9

// PWM outputs

#define PWM0		D0
#define PWM1		D1
#define PWM2		D3
#define PWM3		D5
#define PWM4		D6
#define PWM5		D9
#define PWM6		D10
#define PWM7		D11

#endif
