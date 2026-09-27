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

#ifndef SPI_AGENT_GPIO_H
#define SPI_AGENT_GPIO_H

// LPC1114 I/O Processor GPIO pin assignments

#define LPC1114_INT		3	// PIO0_3  (Raspberry Pi GPIO4)
#define LPC1114_READY		11	// PIO0_11 (Raspberry Pi GPIO22)
#define LPC1114_LED		7	// PIO0_7  (Expansion board LED)
#define LPC1114_GPIO0		12	// PIO1_0  (Terminal block pos 2)
#define LPC1114_GPIO1		13	// PIO1_1  (Terminal block pos 3)
#define LPC1114_GPIO2		14	// PIO1_2  (Terminal block pos 4)
#define LPC1114_GPIO3		15	// PIO1_3  (Terminal block pos 5)
#define LPC1114_GPIO4		16	// PIO1_4  (Terminal block pos 6)
#define LPC1114_GPIO5		17	// PIO1_5  (Terminal block pos 7)
#define LPC1114_GPIO6		20	// PIO1_8  (Terminal block pos 8)
#define LPC1114_GPIO7		21	// PIO1_9  (Terminal block pos 9)

#define IS_GPIO(p) (((p >= LPC1114_GPIO0) && (p <= LPC1114_GPIO5)) || ((p >= LPC1114_GPIO6) && (p <= LPC1114_GPIO7)))
#define IS_INT(p) (p == LPC1114_INT)
#define IS_LED(p) (p == LPC1114_LED)

_BEGIN_STD_C

// SPI Agent Firmware GPIO data directions

typedef enum
{
  LPC1114_GPIO_INPUT,
  LPC1114_GPIO_OUTPUT,
  LPC1114_GPIO_DIRECTION_SENTINEL
} LPC1114_GPIO_DIRECTION_t;

// SPI Agent Firmware GPIO resistor directions

typedef enum
{
  LPC1114_GPIO_PULLDOWN,
  LPC1114_GPIO_PULLUP,
  LPC1114_GPIO_RESISTOR_SENTINEL
} LPC1114_GPIO_RESISTOR_t;

// SPI Agent Firmware GPIO configuration modes

typedef enum
{
  LPC1114_GPIO_MODE_INPUT,		// High impedance input
  LPC1114_GPIO_MODE_INPUT_PULLDOWN,
  LPC1114_GPIO_MODE_INPUT_PULLUP,
  LPC1114_GPIO_MODE_OUTPUT,		// Push-pull output
  LPC1114_GPIO_MODE_OUTPUT_OPENDRAIN,
  LPC1114_GPIO_MODE_SENTINEL
} LPC1114_GPIO_MODE_t;

// SPI Agent Firmware GPIO input interrupt configurations

typedef enum
{
  LPC1114_GPIO_INTERRUPT_DISABLED,
  LPC1114_GPIO_INTERRUPT_FALLING,
  LPC1114_GPIO_INTERRUPT_RISING,
  LPC1114_GPIO_INTERRUPT_BOTH,
  LPC1114_GPIO_INTERRUPT_SENTINEL
} LPC1114_GPIO_INTERRUPT_CONFIG_t;

#ifdef __unix__
// General Purpose Input Output services provided by libspiagent

extern void spiagent_gpio_configure(uint32_t pin, uint32_t direction,
  uint32_t state, int32_t *error);

extern void spiagent_gpio_configure_mode(uint32_t pin, uint32_t mode,
  int32_t *error);

extern void spiagent_gpio_configure_interrupt(uint32_t pin,
  uint32_t intconfig, int32_t *error);

extern void spiagent_gpio_get(uint32_t pin, uint32_t *state, int32_t *error);

extern void spiagent_gpio_put(uint32_t pin, uint32_t state, int32_t *error);
#endif

_END_STD_C

#endif
