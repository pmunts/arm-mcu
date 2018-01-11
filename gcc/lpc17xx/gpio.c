/* Abstract bitwise GPIO services */

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

#include <cpu.h>

#define MAX_GPIO_PORTS		5
#define PINS_PER_GPIO_PORT	32

static LPC_GPIO_TypeDef * const PORTS[] =
{
  LPC_GPIO0,
  LPC_GPIO1,
  LPC_GPIO2,
  LPC_GPIO3,
  LPC_GPIO4
};

int gpio_configure(unsigned pin, unsigned direction)
{
  unsigned int port;

  // Split into port and pin components

  port = pin / PINS_PER_GPIO_PORT;
  pin  = pin % PINS_PER_GPIO_PORT;

  // Validate parameters

  if (port >= MAX_GPIO_PORTS)
  {
    errno_r = EINVAL;
    return -1;
  }

  if (direction > GPIO_DIR_OUTPUT)
  {
    errno_r = EINVAL;
    return -1;
  }

  // Configure the pin

  PORTS[port]->FIOMASK &= ~(1 << pin);
  PORTS[port]->FIODIR  |= (direction << pin);
  return 0;
}

int gpio_read(unsigned pin)
{
  unsigned int port;

  // Split into port and pin components

  port = pin / PINS_PER_GPIO_PORT;
  pin  = pin % PINS_PER_GPIO_PORT;

  // Validate parameters

  if (port >= MAX_GPIO_PORTS)
  {
    errno_r = EINVAL;
    return -1;
  }

  // Read the pin state

  return (PORTS[port]->FIOPIN >> pin) & 0x01;
}

int gpio_write(unsigned pin, bool state)
{
  unsigned int port;

  // Split into port and pin components

  port = pin / PINS_PER_GPIO_PORT;
  pin  = pin % PINS_PER_GPIO_PORT;

  // Validate parameters

  if (port >= MAX_GPIO_PORTS)
  {
    errno_r = EINVAL;
    return -1;
  }

  // Write the pin state

  if (state)
    PORTS[port]->FIOSET = 1 << pin;
  else
    PORTS[port]->FIOCLR = 1 << pin;

  return 0;
}
