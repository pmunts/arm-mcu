/* Abstract bitwise GPIO services */

// $Id$

// Copyright (C)2013-2015, Philip Munts, President, Munts AM Corp.
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

static const char revision[] = "$Id$";

#include <cpu.h>

#if defined(GPIOG)
#define MAX_GPIO_PORTS		7
#elif defined(GPIOF)
#define MAX_GPIO_PORTS		6
#elif defined(GPIOE)
#define MAX_GPIO_PORTS		5
#else
#define MAX_GPIO_PORTS		4
#endif

#define PINS_PER_GPIO_PORT	16

#define GPIO_CONFIG_INPUT	0x00000004
#define GPIO_CONFIG_OUTPUT	0x00000003

static GPIO_TypeDef * const PORTS[] =
{
  GPIOA,
  GPIOB,
  GPIOC,
  GPIOD,
#ifdef GPIOE
  GPIOE,
#endif
#ifdef GPIOF
  GPIOF,
#endif
#ifdef GPIOG
  GPIOG,
#endif
};

int gpiopin_configure(unsigned int pin, gpiopin_direction_t direction)
{
  unsigned int port;

// Split into port and pin components

  port = pin / PINS_PER_GPIO_PORT;
  pin  = pin % PINS_PER_GPIO_PORT;

// Validate parameters

  if (port >= MAX_GPIO_PORTS)
  {
    errno_r = EINVAL;
    return __LINE__ - 3;
  }

  if (direction > GPIOPIN_OUTPUT)
  {
    errno_r = EINVAL;
    return __LINE__ - 3;
  }

// Enable the peripheral clock

  RCC->APB2ENR |= RCC_APB2ENR_AFIOEN|(1 << (port + 2));

// Configure the pin

  if (pin < 8)
  {
    PORTS[port]->CRL &= ~(0xF << (pin*4));
    PORTS[port]->CRL |= ((direction == GPIOPIN_INPUT) ? GPIO_CONFIG_INPUT : GPIO_CONFIG_OUTPUT) << (pin*4);
  }
  else
  {
    PORTS[port]->CRH &= ~(0xF << ((pin-8)*4));
    PORTS[port]->CRH |= ((direction == GPIOPIN_INPUT) ? GPIO_CONFIG_INPUT : GPIO_CONFIG_OUTPUT) << ((pin-8)*4);
  }

  return 0;
}
