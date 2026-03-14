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

#ifndef _ARDUINO_ARM_H_
#define _ARDUINO_ARM_H_

#include <Arduino.h>

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

// User LED configuration

#ifndef LED_PIN
#ifdef ENABLE_GROVE_LED_BUTTON
#define LED_PIN D2
#elifdef ARDUINO_SPARKFUN_PROMICRO_RP2040
// SparkFun Pro Micro RP2040 does not have a GPIO LED
#define LED_PIN D2
#elifdef ARDUINO_SPARKFUN_PROMICRO_RP2350
// SparkFun Pro Micro RP2040 does not have a GPIO LED
#define LED_PIN D2
#elifdef LED_BUILTIN
// Most other boards have an on-board LED connected to D13
#define LED_PIN LED_BUILTIN
#endif
#endif

// Some boards have a NeoPixel compatible on-board RGB LED

#ifndef NEOPIXEL_PIN
#ifdef ARDUINO_SPARKFUN_PROMICRO_RP2040
#define NEOPIXEL_PIN LED_BUILTIN
#endif
#ifdef ARDUINO_SPARKFUN_PROMICRO_RP2350
#define NEOPIXEL_PIN LED_BUILTIN
#endif
#endif

// User button configuration

#ifndef BUTTON_PIN
#ifdef ENABLE_GROVE_LED_BUTTON
// Active low button on D3
#define BUTTON_PIN  D3
#define BUTTON_MODE INPUT
#define BUTTON_XOR  1
#elifdef ARDUINO_ARCH_RP2040
// All RP2040 and RP2350 boards expect an external active low button switch
// from D3 to GND.
#define BUTTON_PIN  D3
#define BUTTON_MODE INPUT_PULLUP
#define BUTTON_XOR  1
#elifdef ARDUINO_DISCO_F407VG
// STM32F4-Discovery has an on-board active high button.
#define BUTTON_PIN  USER_BTN
#define BUTTON_MODE INPUT
#define BUTTON_XOR  0
#elifdef ARDUINO_NUCLEO_F042K6
// Nucleo-F042K6 expects an external active low button switch from D26 to GND.
// This is unrealizable so override for an external active low button switch
// from D9 to GND, and matching some other Nucleo-32 boards.
#define BUTTON_PIN  D9
#define BUTTON_MODE INPUT_PULLUP
#define BUTTON_XOR  1
#elifdef USER_BTN
// Some Nucleo-32 boards expect an external active low button switch from D9
// to GND.
// All  Nucleo-64 boards have an on-board active low button.
#define BUTTON_PIN  USER_BTN
#define BUTTON_MODE INPUT_PULLUP
#define BUTTON_XOR  1
#endif
#endif

// I2C bus pins

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
