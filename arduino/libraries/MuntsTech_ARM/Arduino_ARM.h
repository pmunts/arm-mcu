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

#ifndef UserLED
#ifdef LED_PIN
// Use make defined GPIO pin for user LED
#include <GPIO-Arduino.h>
MuntsTech::GPIO::Arduino::Pin_Class _UserLED(LED_PIN, OUTPUT);
#elifdef ENABLE_GROVE_LED_BUTTON_D2
// Use Grove LED Button (plugged into Grove socket D2) for user LED
#include <GPIO-Arduino.h>
MuntsTech::GPIO::Arduino::Pin_Class _UserLED(D2, OUTPUT);
#elifdef ARDUINO_SPARKFUN_PROMICRO_RP2040
// Use NeoPixel LED for user LED
#include <GPIO-NeoPixel.h>
MuntsTech::GPIO::NeoPixel::Pin_Class _UserLED(LED_BUILTIN);
#elifdef ARDUINO_SPARKFUN_PROMICRO_RP2350
// Use NeoPixel LED for user LED
#include <GPIO-NeoPixel.h>
MuntsTech::GPIO::NeoPixel::Pin_Class _UserLED(LED_BUILTIN);
#elifdef ARDUINO_SEEED_XIAO_RP2040
// Xiao RP2040 has three active low user LEDs
#include <GPIO-Arduino.h>
MuntsTech::GPIO::Arduino::Pin_Class _UserLED(LED_BUILTIN, OUTPUT, true, false);
MuntsTech::GPIO::Arduino::Pin_Class _UserLEDRed(17, OUTPUT, true, false);
MuntsTech::GPIO::Arduino::Pin_Class _UserLEDGreen(16, OUTPUT, true, false);
MuntsTech::GPIO::Arduino::Pin_Class _UserLEDBlue(25, OUTPUT, true, false);
#elifdef ARDUINO_SEEED_XIAO_RP2350
// Xiao RP2350 has one active low user LED
MuntsTech::GPIO::Arduino::Pin_Class _UserLED(LED_BUILTIN, OUTPUT, true, false);
#elifdef LED_BUILTIN
// Most other boards have an on-board LED, often connected to D13
#include <GPIO-Arduino.h>
MuntsTech::GPIO::Arduino::Pin_Class _UserLED(LED_BUILTIN, OUTPUT);
#endif
#define UserLED _UserLED
#endif

// User button configuration

#ifndef UserButton
#if defined(BUTTON_PIN) || defined(BUTTON_MODE) || defined(BUTTON_ACTIVELOW)
// Use make defined GPIO pin for user button
#include <GPIO-Arduino.h>
MuntsTech::GPIO::Arduino::Pin_Class _UserButton(BUTTON_PIN, BUTTON_MODE, BUTTON_ACTIVELOW);
#elifdef ENABLE_GROVE_LED_BUTTON_D2
// Use Grove LED Button plugged into Grove socket D2 for user button
// Active low button on D3
#include <GPIO-Arduino.h>
MuntsTech::GPIO::Arduino::Pin_Class _UserButton(D3, INPUT, true);
#elifdef ARDUINO_SEEED_XIAO_RP2040
// Xiao RP2040 doesn't have an uncommitted GPIO pin for a user button
#elifdef ARDUINO_SEEED_XIAO_RP2350
// Xiao RP2350 doesn't have an uncommitted GPIO pin for a user button
#elifdef ARDUINO_ARCH_RP2040
// All other RP2040 and RP2350 boards need an external active low button
// switch from D2 to GND.
#include <GPIO-Arduino.h>
MuntsTech::GPIO::Arduino::Pin_Class _UserButton(D2, INPUT_PULLUP, true);
#elifdef ARDUINO_DISCO_F407VG
// STM32F4-Discovery has an on-board active high button.
#include <GPIO-Arduino.h>
MuntsTech::GPIO::Arduino::Pin_Class _UserButton(USER_BTN, INPUT, false);
#elifdef ARDUINO_NUCLEO_F042K6
// Nucleo-F042K6 expects an external active low button switch from D26 to GND.
// This is unrealizable so override for an external active low button switch
// from D9 to GND, and matching some other Nucleo-32 boards.
#include <GPIO-Arduino.h>
MuntsTech::GPIO::Arduino::Pin_Class _UserButton(D9, INPUT_PULLUP, true);
#elifdef USER_BTN
// Some Nucleo-32 boards expect an external active low button switch from
// USER_BTN to GND.
// All  Nucleo-64 boards have an on-board active low button.
#include <GPIO-Arduino.h>
MuntsTech::GPIO::Arduino::Pin_Class _UserButton(USER_BTN, INPUT_PULLUP, true);
#endif
#define UserButton _UserButton
#endif

// Some boards have a NeoPixel compatible on-board RGB LED

#ifdef ARDUINO_SPARKFUN_PROMICRO_RP2040
#define NEOPIXEL_PIN LED_BUILTIN
#define NEOPIXEL_PWR 0xFFFFFFFF
#endif
#ifdef ARDUINO_SPARKFUN_PROMICRO_RP2350
#define NEOPIXEL_PIN LED_BUILTIN
#define NEOPIXEL_PWR 0xFFFFFFFF
#endif
#ifdef ARDUINO_SEEED_XIAO_RP2040
#define NEOPIXEL_PIN 12
#define NEOPIXEL_PWR 11
#endif
#ifdef ARDUINO_SEEED_XIAO_RP2350
#define NEOPIXEL_PIN 22
#define NEOPIXEL_PWR 23
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
