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

// Map SPI port number to control structure

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

// Initialize SPI port for bidirectional master mode

int spi_master_init(uint32_t port,
                    uint32_t wordsize,
                    uint32_t clockmode,
                    uint32_t speed,
                    uint32_t bitorder)
{
  SPI_TypeDef *dev;

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

  if (bitorder > 1)
  {
    errno_r = EINVAL;
    return -1;
  }

  dev = SPI_PORTS[port];

  // Configure clocks and GPIO pins

  switch (port)
  {
  }

  // Configure the SPI controller

  errno_r = 0;
  return 0;
}

/*****************************************************************************/

// Transmit command and/or receive result in bidirectional master mode

int spi_master_transfer(uint32_t port,
                        uint8_t *txbuf,
                        uint32_t txcount,
                        uint8_t *rxbuf,
                        uint32_t rxcount)
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
