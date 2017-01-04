/* Simple I2C routines for STM32F1 */

// Copyright (C)2013-2017, Philip Munts, President, Munts AM Corp.
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
#include <stdio.h>

#ifdef I2C2
#define MAX_I2C_PORTS		2
#else
#define MAX_I2C_PORTS		1
#endif

#define RESERVED_ADDRESS_LOW	0x07
#define RESERVED_ADDRESS_HIGH	0x78

// Map I2C port number to control structure

static I2C_TypeDef * const I2C_PORTS[MAX_I2C_PORTS] =
{
  I2C1,
  I2C2
};

int i2c_master_init(unsigned port)
{
  I2C_TypeDef *dev;

  // Validate parameters

  if ((port < 1) && (port > MAX_I2C_PORTS))
  {
    errno_r = ENODEV;
    return -1;
  }

  dev = I2C_PORTS[port];

  // Perform port specific configuration

  switch (port)
  {
#ifdef I2C1
    case I2C_PORT1 :
      // Enable peripheral clock

      RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

      // Configure GPIO pins

      if (gpiopin_device_configure(GPIOPIN_I2C1_SCL))
        return -1;

      if (gpiopin_device_configure(GPIOPIN_I2C1_SDA))
        return -1;
      break;
#endif

#ifdef I2C2
    case I2C_PORT2 :
      // Enable peripheral clock

      RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;

      // Configure GPIO pins

      if (gpiopin_device_configure(GPIOPIN_I2C2_SCL))
        return -1;

      if (gpiopin_device_configure(GPIOPIN_I2C2_SDA))
        return -1;
      break;
#endif

    default :
      errno_r = ENODEV;
      return -1;
  }

  // Configure for APB1 at 36 MHz (27.78 ns)

  dev->CR2 = 0x0024;
  dev->TRISE = 37;	// 1000 ns rise time
  dev->CCR = 180;	// 5000 ns pulse width

  // Enable I2C device

  dev->CR1 = I2C_CR1_PE;

  errno_r = 0;
  return 0;
}

ssize_t i2c_master_read(unsigned port, uint8_t slaveaddr,
  uint8_t *rxbuf, size_t rxsize)
{
  I2C_TypeDef *dev;
  ssize_t count = 0;

  // Validate parameters

  if ((port < 1) && (port > MAX_I2C_PORTS))
  {
    errno_r = ENODEV;
    return -1;
  }

  if (slaveaddr <= RESERVED_ADDRESS_LOW)
  {
    errno_r = EINVAL;
    return -1;
  }

  if (slaveaddr >= RESERVED_ADDRESS_HIGH)
  {
    errno_r = EINVAL;
    return -1;
  }

  if (rxbuf == NULL)
  {
    errno_r = EINVAL;
    return -1;
  }

  if (rxsize == 0)
  {
    errno_r = EINVAL;
    return -1;
  }

  dev = I2C_PORTS[port];

  dev->CR1 &= ~I2C_CR1_POS;

  // Assert START

  dev->CR1 |= I2C_CR1_START;
  while ((dev->SR1 & I2C_SR1_SB) == 0);

  // Address slave

  dev->DR = (slaveaddr << 1) + 1;
  while ((dev->SR1 & I2C_SR1_ADDR) == 0);
  dev->SR2;
  while ((dev->SR1 & I2C_SR1_ADDR) != 0);

  // Receive bytes

  if (rxsize == 1)
  {
    dev->CR1 &= ~I2C_CR1_ACK;
    dev->CR1 |= I2C_CR1_STOP;
  }
  else
  {
    dev->CR1 |= I2C_CR1_ACK;
  }

  while (rxsize--)
  {
    while ((dev->SR1 & I2C_SR1_RXNE) == 0);
    *rxbuf++ = dev->DR;
    count++;

    // Post NACK and STOP on just before last byte

    if (rxsize == 1)
    {
      dev->CR1 &= ~I2C_CR1_ACK;
      dev->CR1 |= I2C_CR1_STOP;
    }
  }

  // Wait for STOP

  while (dev->CR1 & I2C_CR1_STOP);

  errno_r = 0;
  return count;
}

ssize_t i2c_master_write(unsigned port, uint8_t slaveaddr,
  uint8_t *txbuf, size_t txsize)
{
  I2C_TypeDef *dev;
  ssize_t count = 0;

  // Validate parameters

  if ((port < 1) && (port > MAX_I2C_PORTS))
  {
    errno_r = ENODEV;
    return -1;
  }

  if (slaveaddr <= RESERVED_ADDRESS_LOW)
  {
    errno_r = EINVAL;
    return -1;
  }

  if (slaveaddr >= RESERVED_ADDRESS_HIGH)
  {
    errno_r = EINVAL;
    return -1;
  }

  if (txbuf == NULL)
  {
    errno_r = EINVAL;
    return -1;
  }

  if (txsize == 0)
  {
    errno_r = EINVAL;
    return -1;
  }

  dev = I2C_PORTS[port];

  // Assert START

  dev->CR1 |= I2C_CR1_START;
  while ((dev->SR1 & I2C_SR1_SB) == 0);

  // Address slave

  dev->DR = slaveaddr << 1;
  while ((dev->SR1 & I2C_SR1_ADDR) == 0);
  dev->SR2;

  // Transmit bytes

  while (txsize--)
  {
    dev->DR = *txbuf++;
    count++;
    while ((dev->SR1 & I2C_SR1_TXE) == 0);
  }

  // Assert STOP

  dev->CR1 |= I2C_CR1_STOP;
  while (dev->CR1 & I2C_CR1_STOP);

  errno_r = 0;
  return count;
}
