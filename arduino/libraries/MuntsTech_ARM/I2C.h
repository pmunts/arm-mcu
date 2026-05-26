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
// Default I2C bus pins

#ifndef _MUNTSTECH_I2C_H_
#define _MUNTSTECH_I2C_H_

/*****************************************************************************/

// RP2040/RP2350 Boards, using the Arduino-Pico core package

#ifdef ARDUINO_ARCH_RP2040
#ifdef ARDUINO_CYTRON_MAKER_NANO_RP2040
// I2C bus on GP26 and GP27 (Maker Port 1 aka QWIIC socket 1)
#define I2C_SDA_PIN 26
#define I2C_SCL_PIN 27
#elifdef ARDUINO_PIMORONI_TINY2350
// I2C bus on GP12 and GP13 (QWIIC socket)
#define I2C_SDA_PIN 12
#define I2C_SCL_PIN 13
#elifdef ARDUINO_SPARKFUN_PROMICRO_RP2040
// I2C bus on GPIO16 and GPIO17 (QWIIC socket)
#define I2C_SDA_PIN 16
#define I2C_SCL_PIN 17
#elifdef ARDUINO_SPARKFUN_PROMICRO_RP2350
// I2C bus on GPIO16 and GPIO17 (QWIIC socket)
#define I2C_SDA_PIN 16
#define I2C_SCL_PIN 17
#else
// All other RP2040/RP2350 boards: Same as Raspberry Pi Pico default,
// I2C bus on GP4 and GP5
#define I2C_SDA_PIN 4
#define I2C_SCL_PIN 5
#endif
#endif

/*****************************************************************************/

#endif
