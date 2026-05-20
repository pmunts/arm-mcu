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

#ifndef _MUNTSTECH_ARDUINO_ARM_H_
#define _MUNTSTECH_ARDUINO_ARM_H_

#include <Arduino.h>

#ifdef ARDUINO_CYTRON_MAKER_NANO_RP2040
// Analog pins
#define A0	26
#define A1	27
#define A2	28
#define A3	29
#define A4
#define A5
#define A6
#define A7
#ifdef COMPAT_SILKSCREEN
// PCB silkscreen compatible pin definitions
#define D0	0	// TXD
#define D1	1	// RXD
#define D2	2
#define D3	3
#define D4	4
#define D5	5
#define D6	6
#define D7	7
#define D8	8
#define D9	9
#define D10
#define D11
#define D12	12	// SDA0
#define D13	13	// SCL0
#define D14	14	// SDA1
#define D15	15	// SCL1
#define D16	16
#define D17	17
#define D18	18
#define D19	19
#define D20
#define D21
#define D22
#define D23
#define D24
#define D25
#define D26	26	// A0
#define D27	27	// A1
#define D28	28	// A2
#define D29	29	// A3
#else
// Arduino Nano compatible pin definitions
#define D0	1	// RXD
#define D1	0	// TXD
#define D2	2
#define D3	3
#define D4	4
#define D5	5
#define D6	6
#define D7	7
#define D8	8
#define D9	9
#define D10	17
#define D11	19
#define D12	16
#define D13	18
#define D14	26	// A0
#define D15	27	// A1
#define D16	28	// A2
#define D17	29	// A3
#define D18	12	// SDA0
#define D19	13	// SCL0
#define D20	14	// SDA1
#define D21	15	// SCL1
#define D22
#define D23
#define D24
#define D25
#define D26
#define D27
#define D28
#define D29
#endif
#endif

#include <ButtonSwitch.h>
#include <LED.h>

// Default I2C bus pins

#ifdef ARDUINO_ARCH_RP2040
#ifdef PICO_RP2350
// I2C bus on GP4 and GP5, same as Raspberry Pi Pico 2
#define I2C_SDA_PIN 4
#define I2C_SCL_PIN 5
#elifdef ARDUINO_SPARKFUN_PROMICRO_RP2040
// I2C bus on GPIO16 and GPIO17
#define I2C_SDA_PIN 16
#define I2C_SCL_PIN 17
#else
// I2C bus on GP4 and GP5, same as Raspberry Pi Pico
#endif
#endif

// Enable FreeRTOS

#ifdef ENABLE_FREERTOS
#ifdef ARDUINO_ARCH_RP2040
#include <FreeRTOS.h>
// The Arduino-Pico core main() calls vTaskStartScheduler(), so redefine it
// as an empty macro to prevent application code from calling it again.
#define vTaskStartScheduler()
#elifdef ARDUINO_ARCH_STM32
#include <STM32FreeRTOS.h>
#endif
#endif

#endif
