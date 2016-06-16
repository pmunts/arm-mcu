/* Simple I2C routines for STM32F1 */

// Copyright (C)2013-2016, Philip Munts, President, Munts AM Corp.
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

#define MAX_I2C_PORTS		2

#define GPIO_CONFIG_SCL		0xF
#define GPIO_CONFIG_SDA		0xF
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

  errno_r = 0;

  // Validate parameters

  if ((port < 1) && (port > MAX_I2C_PORTS))
  {
    errno_r = ENODEV;
    return -1;
  }

  dev = I2C_PORTS[port];

  // Configure I2C pins

  switch (port)
  {
    case 0 :
      // Enable peripheral clocks

      RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
      RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

#if defined(NUCLEO_F103RB) || defined(OLIMEX_STM32_P107)
      // SCL on PB8 (remap)
      // SDA on PB9 (remap)

      RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
      AFIO->MAPR |= AFIO_MAPR_I2C1_REMAP;

      GPIOB->CRH &= ~(0xF << 0);
      GPIOB->CRH |= GPIO_CONFIG_SCL << 0;

      GPIOB->CRH &= ~(0xF << 4);
      GPIOB->CRH |= GPIO_CONFIG_SDA << 4;
#else
      // SCL on PB6
      // SDA on PB7

      RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
      AFIO->MAPR &= ~AFIO_MAPR_I2C1_REMAP

      GPIOB->CRL &= ~(0xF << 24);
      GPIOB->CRL |= GPIO_CONFIG_SCL << 24;

      GPIOB->CRL &= ~(0xF << 28);
      GPIOB->CRL |= GPIO_CONFIG_SDA << 28;
#endif
      break;
  }

  // Configure for APB1 at 36 MHz (27.78 ns)

  dev->CR2 = 0x0024;
  dev->TRISE = 37;	// 1000 ns rise time
  dev->CCR = 180;	// 5000 ns pulse width

  // Enable I2C device

  dev->CR1 = I2C_CR1_PE;

  return 0;
}

ssize_t i2c_master_read(unsigned port, uint8_t slaveaddr,
  uint8_t *rxbuf, size_t rxsize)
{
  I2C_TypeDef *dev;

  errno_r = 0;

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

    // Post NACK and STOP on just before last byte

    if (rxsize == 1)
    {
      dev->CR1 &= ~I2C_CR1_ACK;
      dev->CR1 |= I2C_CR1_STOP;
    }
  }

  // Wait for STOP

  while (dev->CR1 & I2C_CR1_STOP);

  return 0;
}

ssize_t i2c_master_write(unsigned port, uint8_t slaveaddr,
  uint8_t *txbuf, size_t txsize)
{
  I2C_TypeDef *dev;

  errno_r = 0;

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
    while ((dev->SR1 & (I2C_SR1_BTF|I2C_SR1_TXE)) == 0);
  }

  // Assert STOP

  dev->CR1 |= I2C_CR1_STOP;
  while (dev->CR1 & I2C_CR1_STOP);

  return 0;
}
