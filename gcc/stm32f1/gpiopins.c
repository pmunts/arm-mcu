/* Abstract bitwise GPIO services */

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
#include <string.h>

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
    return -1;
  }

  if (direction > GPIOPIN_OUTPUT)
  {
    errno_r = EINVAL;
    return -1;
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

#define GPIO_CONFIG_SCL		0xF	// 50 MHz AF open-drain output
#define GPIO_CONFIG_SDA		0xF	// 50 MHz AF open-drain output
#define GPIO_CONFIG_TXD		0xB	// 50 MHz AF push-pull output
#define GPIO_CONFIG_RXD		0x4	// Floating input
#define GPIO_CONFIG_NSS		0x4	// Floating input
#define GPIO_CONFIG_SCK		0xB	// 50 MHz AF push-pull output
#define GPIO_CONFIG_MISO	0x4	// Floating input
#define GPIO_CONFIG_MOSI	0xB	// 50 MHz AF push-pull output

typedef struct
{
  unsigned devpin;
  unsigned gpiopin;
  unsigned config;
  unsigned remap1;
  unsigned remap2;
} PINMAPPING_t;

static const PINMAPPING_t AllowedMappings[] =
{
#ifdef I2C1
  { GPIOPIN_I2C1_SCL,   GPIOPIN22, GPIO_CONFIG_SCL,  0x00000000, 0x00000000 }, // PB6
  { GPIOPIN_I2C1_SDA,   GPIOPIN23, GPIO_CONFIG_SDA,  0x00000000, 0x00000000 }, // PB7
  { GPIOPIN_I2C1_SCL,   GPIOPIN24, GPIO_CONFIG_SCL,  0x00000002, 0x00000000 }, // PB8
  { GPIOPIN_I2C1_SDA,   GPIOPIN25, GPIO_CONFIG_SDA,  0x00000002, 0x00000000 }, // PB9
#endif
#ifdef I2C2
  { GPIOPIN_I2C2_SCL,   GPIOPIN26, GPIO_CONFIG_SCL,  0x00000000, 0x00000000 }, // PB10
  { GPIOPIN_I2C2_SDA,   GPIOPIN27, GPIO_CONFIG_SDA,  0x00000000, 0x00000000 }, // PB11
#endif
#ifdef SPI1
  { GPIOPIN_SPI1_SCK,   GPIOPIN5,  GPIO_CONFIG_SCK,  0x00000000, 0x00000000 }, // PA5
  { GPIOPIN_SPI1_MISO,  GPIOPIN6,  GPIO_CONFIG_MISO, 0x00000000, 0x00000000 }, // PA6
  { GPIOPIN_SPI1_MOSI,  GPIOPIN7,  GPIO_CONFIG_MOSI, 0x00000000, 0x00000000 }, // PA7
  { GPIOPIN_SPI1_SCK,   GPIOPIN19, GPIO_CONFIG_SCK,  0x00000001, 0x00000000 }, // PB3
  { GPIOPIN_SPI1_MISO,  GPIOPIN20, GPIO_CONFIG_MISO, 0x00000001, 0x00000000 }, // PB4
  { GPIOPIN_SPI1_MOSI,  GPIOPIN21, GPIO_CONFIG_MOSI, 0x00000001, 0x00000000 }, // PB5
#endif
#ifdef SPI2
  { GPIOPIN_SPI2_SCK,   GPIOPIN29, GPIO_CONFIG_SCK,  0x00000000, 0x00000000 }, // PB13
  { GPIOPIN_SPI2_MISO,  GPIOPIN30, GPIO_CONFIG_MISO, 0x00000000, 0x00000000 }, // PB14
  { GPIOPIN_SPI2_MOSI,  GPIOPIN31, GPIO_CONFIG_MOSI, 0x00000000, 0x00000000 }, // PB15
#endif
#ifdef SPI3
  { GPIOPIN_SPI3_SCK,   GPIOPIN19, GPIO_CONFIG_SCK,  0x00000000, 0x00000000 }, // PB3
  { GPIOPIN_SPI3_MISO,  GPIOPIN20, GPIO_CONFIG_MISO, 0x00000000, 0x00000000 }, // PB4
  { GPIOPIN_SPI3_MOSI,  GPIOPIN21, GPIO_CONFIG_MOSI, 0x00000000, 0x00000000 }, // PB5
  { GPIOPIN_SPI3_SCK,   GPIOPIN42, GPIO_CONFIG_SCK,  0x10000000, 0x00000000 }, // PC10
  { GPIOPIN_SPI3_MISO,  GPIOPIN43, GPIO_CONFIG_MISO, 0x10000000, 0x00000000 }, // PC11
  { GPIOPIN_SPI3_MOSI,  GPIOPIN44, GPIO_CONFIG_MOSI, 0x10000000, 0x00000000 }, // PC12
#endif
#ifdef USART1
  { GPIOPIN_USART1_TXD, GPIOPIN9,  GPIO_CONFIG_TXD,  0x00000000, 0x00000000 }, // PA9
  { GPIOPIN_USART1_RXD, GPIOPIN10, GPIO_CONFIG_RXD,  0x00000000, 0x00000000 }, // PA10
  { GPIOPIN_USART1_TXD, GPIOPIN22, GPIO_CONFIG_TXD,  0x00000004, 0x00000000 }, // PB6
  { GPIOPIN_USART1_RXD, GPIOPIN23, GPIO_CONFIG_RXD,  0x00000004, 0x00000000 }, // PB7
#endif
#ifdef USART2
  { GPIOPIN_USART2_TXD, GPIOPIN2,  GPIO_CONFIG_TXD,  0x00000000, 0x00000000 }, // PA2
  { GPIOPIN_USART2_RXD, GPIOPIN3,  GPIO_CONFIG_RXD,  0x00000000, 0x00000000 }, // PA3
  { GPIOPIN_USART2_TXD, GPIOPIN53, GPIO_CONFIG_TXD,  0x00000008, 0x00000000 }, // PD5
  { GPIOPIN_USART2_RXD, GPIOPIN54, GPIO_CONFIG_RXD,  0x00000008, 0x00000000 }, // PD6
#endif
#ifdef USART3
  { GPIOPIN_USART3_TXD, GPIOPIN26, GPIO_CONFIG_TXD,  0x00000000, 0x00000000 }, // PB10
  { GPIOPIN_USART3_RXD, GPIOPIN27, GPIO_CONFIG_RXD,  0x00000000, 0x00000000 }, // PB11
  { GPIOPIN_USART3_TXD, GPIOPIN42, GPIO_CONFIG_TXD,  0x00000010, 0x00000000 }, // PC10
  { GPIOPIN_USART3_RXD, GPIOPIN43, GPIO_CONFIG_RXD,  0x00000010, 0x00000000 }, // PC11
  { GPIOPIN_USART3_TXD, GPIOPIN56, GPIO_CONFIG_TXD,  0x00000030, 0x00000000 }, // PD8
  { GPIOPIN_USART3_RXD, GPIOPIN57, GPIO_CONFIG_RXD,  0x00000030, 0x00000000 }, // PD9
#endif
  { 0xFFFFFFFF, 0, 0, 0, 0 }
};

static unsigned ActualMappings[(int)GPIOPIN_DEVICEPINS_SENTINEL];

void gpiopin_device_defaults(void)
{
  int i;

  // Zero the ActualMappings table

  memset(ActualMappings, 0, sizeof(ActualMappings));

  // Copy default mappings from AllowedMappings[] to ActualMappings[]

  for (i = 0; AllowedMappings[i].devpin != 0xFFFFFFFF; i++)
  {
    PINMAPPING_t const *p = &AllowedMappings[i];

    if (ActualMappings[p->devpin] == 0)
      ActualMappings[p->devpin] = i+1;
  }
}

int gpiopin_device_map(unsigned int devpin, unsigned int gpiopin)
{
  int i;

  // Validate parameters

  if (devpin >= GPIOPIN_DEVICEPINS_SENTINEL)
  {
    errno_r = ENODEV;
    return -1;
  }

  // Look for a matching pin mapping

  for (i = 0; AllowedMappings[i].devpin != 0xFFFFFFFF; i++)
  {
    PINMAPPING_t const *p = &AllowedMappings[i];

    if ((p->devpin == devpin) && (p->gpiopin == gpiopin))
    {
      ActualMappings[p->devpin] = i+1;
      errno_r = 0;
      return 0;
    }
  }

  // No matching pin mapping available

  errno_r = EINVAL;
  return -1;
}

int gpiopin_device_configure(unsigned int devpin)
{
  PINMAPPING_t const *mapping;
  unsigned port;
  unsigned pin;

  // Validate parameters

  if (devpin >= GPIOPIN_DEVICEPINS_SENTINEL)
  {
    errno_r = ENODEV;
    return -1;
  }

  // Get pin mapping

  mapping = &AllowedMappings[ActualMappings[devpin]-1];

  // Split into port and pin components

  port = mapping->gpiopin / PINS_PER_GPIO_PORT;
  pin  = mapping->gpiopin % PINS_PER_GPIO_PORT;

  if (port >= MAX_GPIO_PORTS)
  {
    errno_r = ENODEV;
    return -1;
  }

  // Enable the GPIO port peripheral clock

  RCC->APB2ENR |= RCC_APB2ENR_AFIOEN|(1 << (port + 2));

  // Configure the pin

  if (pin < 8)
  {
    PORTS[port]->CRL &= ~(0xF << (pin*4));
    PORTS[port]->CRL |= mapping->config << (pin*4);
  }
  else
  {
    PORTS[port]->CRH &= ~(0xF << ((pin-8)*4));
    PORTS[port]->CRH |= mapping->config << ((pin-8)*4);
  }

  // Configure AFIO remapping

  AFIO->MAPR  |= mapping->remap1;
  AFIO->MAPR2 |= mapping->remap2;

  return 0;
}
