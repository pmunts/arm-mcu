/* Simple I2C driver services */

// $Id$

// Copyright (C)2015, Philip Munts, President, Munts AM Corp.
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
#include <stdio.h>

#define MAX_I2C_PORTS           1

int i2c_init(unsigned port, uint8_t addr)
{
  volatile int i;

  errno_r = 0;

// Validate parameters

  if (port >= MAX_I2C_PORTS)
  {
    errno_r = ENODEV;
    return -1;
  }

  if (addr > 127)
  {
    errno_r = EINVAL;
    return -1;
  }

  switch (port)
  {
    case 0 :
      // Configure I2C0 pins

      LPC_IOCON->PIO0_4 = 0x00000001;
      LPC_IOCON->PIO0_5 = 0x00000001;

      // Enable I2C0 peripheral clock

      LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 5);

      // Let I2C0 out of reset

      LPC_SYSCON->PRESETCTRL |= (1 << 1);

      for (i = 0; i < 100; i++);

      // Configure I2C address

      LPC_I2C->ADR0 = addr << 1;
      LPC_I2C->ADR1 = 0;
      LPC_I2C->ADR2 = 0;
      LPC_I2C->ADR3 = 0;

      LPC_I2C->MASK0 = 0;
      LPC_I2C->MASK1 = 0;
      LPC_I2C->MASK2 = 0;
      LPC_I2C->MASK3 = 0;
      break;
  }

  return 0;
}

ssize_t i2c_slave_receive(unsigned port, uint8_t *buf, size_t size)
{
  ssize_t count = 0;
  errno_r = 0;

// Validate parameters

  if (port >= MAX_I2C_PORTS)
  {
    errno_r = ENODEV;
    return -1;
  }

  if (buf == NULL)
  {
    errno_r = EINVAL;
    return -1;
  }

  if (size == 0)
  {
    errno_r = EINVAL;
    return -1;
  }

  // Enter slave receive mode

  LPC_I2C->CONSET = 0x54;
  LPC_I2C->CONCLR = 0x38;

  for (;;)
  {
    switch (LPC_I2C->STAT)
    {
      case 0xF8 :
        continue;

      case 0x60 :
        LPC_I2C->CONSET = 0x04;		// Assert AA
        LPC_I2C->CONCLR = 0x08;		// Clear SI
        continue;

      case 0x80 :
        *buf++ = LPC_I2C->DAT;
        count++;
        size--;

        if (size)
        {
          LPC_I2C->CONSET = 0x04;	// Assert AA
          LPC_I2C->CONCLR = 0x08;	// Clear SI
          continue;
        }
        else
        {
          LPC_I2C->CONCLR = 0x0C;	// Clear AA and SI
          return count;
        }
        break;

      case 0xA0 :
        LPC_I2C->CONSET = 0x04;		// Assert AA
        LPC_I2C->CONCLR = 0x08;		// Clear SI
        return count;

      default :
        printf("DEBUG: i2c_slave_receive(): Unexpected state => %02lX\n", LPC_I2C->STAT);
        errno_r = EIO;
        return -1;
    }
  }
}

ssize_t i2c_slave_transmit(unsigned port, uint8_t *buf, size_t size)
{
  ssize_t count = 0;
  errno_r = 0;

// Validate parameters

  if (port >= MAX_I2C_PORTS)
  {
    errno_r = ENODEV;
    return -1;
  }

  if (buf == NULL)
  {
    errno_r = EINVAL;
    return -1;
  }

  if (size == 0)
  {
    errno_r = EINVAL;
    return -1;
  }

  // Enter slave transmit mode

  LPC_I2C->CONSET = 0x54;
  LPC_I2C->CONCLR = 0x38;

  for (;;)
  {
    switch (LPC_I2C->STAT)
    {
      case 0xF8 :
        continue;

      case 0xA8 :
      case 0xB8 :
        if (size)
        {
          LPC_I2C->DAT = *buf++;
          size--;
          count++;
        }
        else
        {
          LPC_I2C->DAT = 0;		// Pad zero bytes
        }
        LPC_I2C->CONSET = 0x04;		// Assert AA
        LPC_I2C->CONCLR = 0x08;		// Clear SI
        continue;

      case 0xA0 :
      case 0xC0 :
      case 0xC8 :
        LPC_I2C->CONSET = 0x04;		// Assert AA
        LPC_I2C->CONCLR = 0x08;		// Clear SI
        return count;

      default :
        printf("DEBUG: i2c_slave_transmit(): Unexpected state => %02lX\n", LPC_I2C->STAT);
        errno_r = EIO;
        return -1;
    }
  }
}
