/* Simple SPI master routines for STM32F1 */

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

#if defined(SPI3)
#define MAX_SPI_PORTS		3
#elif defined(SPI2)
#define MAX_SPI_PORTS		2
#else
#define MAX_SPI_PORTS		1
#endif

// Map SPI port number to device structure pointer

static SPI_TypeDef * const SPI_PORTS[MAX_SPI_PORTS] =
{
  SPI1,
#ifdef SPI2
  SPI2,
#endif
#ifdef SPI3
  SPI3,
#endif
};

/*****************************************************************************/

// Calculate the SPI clock prescaler for a given SPI clock rate.  Return an
// error if the requested SPI clock rate isn't possible.

static int SPI_Clock_Prescaler(uint32_t port,
                               uint32_t speed,
                               uint32_t *prescaler)
{
  uint32_t PCLK;

// Different SPI ports use PCLK1 or PCLK2 peripheral clock

  switch (port)
  {
    case SPI_PORT1 :
      PCLK = SystemCoreClock;	// SPI1 is on APB2=HCLK
      break;

#ifdef SPI2
    case SPI_PORT2 :
      PCLK = SystemCoreClock/2;	// SPI2 is on APB1=HCLK/2
      break;
#endif

#ifdef SPI3
    case SPI_PORT3 :
      PCLK = SystemCoreClock/2;	// SPI3 is on APB1=HCLK/2
      break;
#endif

    default :
      errno_r = ENODEV;
      return -1;
  }

// Calculate SPI clock prescaler from desired SPI clock rate and PCLK rate

  if (speed == PCLK/256)
    *prescaler = 7;
  else if (speed == PCLK/128)
    *prescaler = 6;
  else if (speed == PCLK/64)
    *prescaler = 5;
  else if (speed == PCLK/32)
    *prescaler = 4;
  else if (speed == PCLK/16)
    *prescaler = 3;
  else if (speed == PCLK/8)
    *prescaler = 2;
  else if (speed == PCLK/4)
    *prescaler = 1;
  else if (speed == PCLK/2)
    *prescaler = 0;

// Only the above SPI clock rates are possible.  Others are unrealizable.

  else
  {
    errno_r = EINVAL;
    return -1;
  }

  return 0;
}

/*****************************************************************************/

// Initialize SPI port for bidirectional master mode

int spi_master_init(uint32_t port, uint32_t wordsize, uint32_t clockmode,
  uint32_t speed, uint32_t bitorder)
{
  uint32_t prescaler;

  // Validate parameters

  if ((port < 1) && (port > MAX_SPI_PORTS))
  {
    errno_r = ENODEV;
    return -1;
  }

  if ((wordsize != 8) && (wordsize != 16))
  {
    errno_r = EINVAL;
    return -1;
  }

  if (clockmode > 3)
  {
    errno_r = EINVAL;
    return -1;
  }

  if (SPI_Clock_Prescaler(port, speed, &prescaler))
    return -1;

  if (bitorder > 1)
  {
    errno_r = EINVAL;
    return -1;
  }

  // Configure hardware

  switch (port)
  {
#ifdef SPI1
    case SPI_PORT1 :
      // Enable peripheral clock

      RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

      // Configure GPIO pins

      if (gpiopin_device_configure(GPIOPIN_SPI1_SCK))
        return -1;

      if (gpiopin_device_configure(GPIOPIN_SPI1_MISO))
        return -1;

      if (gpiopin_device_configure(GPIOPIN_SPI1_MOSI))
        return -1;

      // Configure the SPI controller

      SPI1->CR1 = 0x0344		|
        ((wordsize == 8 ? 0 : 1) << 11)	|
        ((bitorder ? 0 : 1) << 7)	|
        (prescaler << 3)		|
        clockmode;
      SPI1->CR2 = 0x00000000;
      break;
#endif

#ifdef SPI2
    case SPI_PORT2 :
      // Enable peripheral clock

      RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;

      // Configure GPIO pins

      if (gpiopin_device_configure(GPIOPIN_SPI2_SCK))
        return -1;

      if (gpiopin_device_configure(GPIOPIN_SPI2_MISO))
        return -1;

      if (gpiopin_device_configure(GPIOPIN_SPI2_MOSI))
        return -1;

      // Configure the SPI controller

      SPI2->CR1 = 0x0344		|
        ((wordsize == 8 ? 0 : 1) << 11)	|
        ((bitorder ? 0 : 1) << 7)	|
        (prescaler << 3)		|
        clockmode;
      SPI2->CR2 = 0x00000000;
      break;
#endif

#ifdef SPI3
    case SPI_PORT3 :
      // Enable peripheral clock

      RCC->APB1ENR |= RCC_APB1ENR_SPI3EN;

      // Configure GPIO pins

      if (gpiopin_device_configure(GPIOPIN_SPI3_SCK))
        return -1;

      if (gpiopin_device_configure(GPIOPIN_SPI3_MISO))
        return -1;

      if (gpiopin_device_configure(GPIOPIN_SPI3_MOSI))
        return -1;

      // Configure the SPI controller

      SPI3->CR1 = 0x0344		|
        ((wordsize == 8 ? 0 : 1) << 11)	|
        ((bitorder ? 0 : 1) << 7)	|
        (prescaler << 3)		|
        clockmode;
      SPI3->CR2 = 0x00000000;
      break;
#endif

    default :
      errno_r = EINVAL;
      return -1;
  }

  errno_r = 0;
  return 0;
}

/*****************************************************************************/

// Transmit command and/or receive result in bidirectional master mode

int spi_master_transfer(uint32_t port, uint8_t *txbuf, uint32_t txcount,
  uint8_t *rxbuf, uint32_t rxcount)
{
  SPI_TypeDef *dev;

  // Validate parameters

  if ((port < 1) && (port > MAX_SPI_PORTS))
  {
    errno_r = ENODEV;
    return -1;
  }

  if ((txbuf == NULL) && (txcount != 0))
  {
    errno_r = EINVAL;
    return -1;
  }

  if ((txcount == 0) && (txbuf != NULL))
  {
    errno_r = EINVAL;
    return -1;
  }

  if ((rxbuf == NULL) && (rxcount != 0))
  {
    errno_r = EINVAL;
    return -1;
  }

  if ((rxcount == 0) && (rxbuf != NULL))
  {
    errno_r = EINVAL;
    return -1;
  }

  dev = SPI_PORTS[port];

  // Transfer command data out

  while (txcount--)
  {
    while (!(dev->SR & SPI_SR_TXE));
    dev->DR = *txbuf++;
    while (!(dev->SR & SPI_SR_RXNE));
    (void) dev->DR;
  }

  // Transfer response data in

  while (rxcount--)
  {
    while (!(dev->SR & SPI_SR_TXE));
    dev->DR = 0;
    while (!(dev->SR & SPI_SR_RXNE));
    *rxbuf++ = dev->DR;
  }

  // Wait until the transfer is complete

  while (dev->SR & SPI_SR_BSY);

  errno_r = 0;
  return 0;
}
