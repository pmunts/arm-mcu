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

// LED configuration

#ifndef LED
#ifdef ARDUINO_SPARKFUN_PROMICRO_RP2040
// SparkFun Pro Micro RP2040 does not have a GPIO LED
#define LED	D2
// Most other boards have an LED connected to D13
#elifdef LED_BUILTIN
#define LED	LED_BUILTIN
#endif
#endif

// User button configuration

#ifndef BUTTON_PIN
#ifdef ARDUINO_NUCLEO_F042K6
#define BUTTON_PIN  12
#define BUTTON_MODE INPUT_PULLUP
#elifdef USER_BTN
#define BUTTON_PIN  USER_BTN
#define BUTTON_MODE INPUT
#elifdef ARDUINO_SPARKFUN_PROMICRO_RP2040
#define BUTTON_PIN  3
#define BUTTON_MODE INPUT_PULLUP
#elifdef ARDUINO_RASPBERRY_PI_PICO_2
#define BUTTON_PIN  22
#define BUTTON_MODE INPUT_PULLUP
#elifdef ARDUINO_RASPBERRY_PI_PICO_2W
#define BUTTON_PIN  22
#define BUTTON_MODE INPUT_PULLUP
#elifdef ARDUINO_WAVESHARE_RP2350_PLUS
#define BUTTON_PIN  22
#define BUTTON_MODE INPUT_PULLUP
#endif
#endif

// Enable FreeRTOS

#ifdef ENABLE_FREERTOS
#ifdef ARDUINO_ARCH_RP2040
#define __FREERTOS 1
#include <FreeRTOS.h>
#elifdef ARDUINO_ARCH_STM32
#include <STM32FreeRTOS.h>
#endif
#endif

// Hardware PWM servo configuration

#ifdef ENABLE_HARDWARE_SERVO
#include <ServoPWM.h>
#define ENABLE_HARDWARE_PWM
#endif

// Hardware PWM configuration

#ifdef ENABLE_HARDWARE_PWM
#ifdef ARDUINO_ARCH_RP2040
#include <RP2040HardwarePWM.h>
#elifdef ARDUINO_ARCH_STM32
#include <STM32HardwarePWM.h>
#endif
#endif

#endif
