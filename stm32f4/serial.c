/******************************************************************************/
/*                                                                            */
/*     Simple serial port I/O routines for the STM32F4 Cortex-M4 ARM MCU      */
/*                                                                            */
/******************************************************************************/

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

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <cpu.h>

#define MAX_SERIAL_PORTS	6	// com1: through com6:
#define BUFSIZE			64	// Must be power of 2!

typedef struct
{
  uint8_t data[BUFSIZE];
  unsigned head;
  unsigned tail;
  unsigned count;
} ringbuffer_t;

typedef struct
{
  volatile ringbuffer_t *rxbuffer;	// receiver buffer structure
  volatile ringbuffer_t *txbuffer;	// transmit buffer structure
  volatile unsigned * const TXEIE;	// TXEIE bit band address
} uart_t;

static uart_t UARTS[MAX_SERIAL_PORTS] =
{
  { NULL, NULL, (volatile unsigned *) 0x4222019C},
  { NULL, NULL, (volatile unsigned *) 0x4208819C},
  { NULL, NULL, (volatile unsigned *) 0x4209019C},
  { NULL, NULL, (volatile unsigned *) 0x4209819C},
  { NULL, NULL, (volatile unsigned *) 0x420A019C},
  { NULL, NULL, (volatile unsigned *) 0x4222819C},
};

static int InitializeRingBuffers(unsigned port)
{
  errno_r = 0;

// Allocate buffer structures

  if (UARTS[port].rxbuffer == NULL)
  {
    UARTS[port].rxbuffer = malloc(sizeof(ringbuffer_t));
    if (UARTS[port].rxbuffer == NULL)
    {
      errno_r = ENOMEM;
      return -1;
    }
  }

  if (UARTS[port].txbuffer == NULL)
  {
    UARTS[port].txbuffer = malloc(sizeof(ringbuffer_t));
    if (UARTS[port].txbuffer == NULL)
    {
      errno_r = ENOMEM;
      return -1;
    }
  }

  memset((void *) UARTS[port].rxbuffer, 0, sizeof(ringbuffer_t));
  memset((void *) UARTS[port].txbuffer, 0, sizeof(ringbuffer_t));
  return 0;
}

static unsigned CalcBRR(unsigned port, unsigned baudrate)
{
  unsigned BAUDCLOCK = SystemCoreClock;
  unsigned divisor;
  unsigned fract;

  // Account for AHB divider

  switch (RCC->CFGR & RCC_CFGR_HPRE)
  {
    case RCC_CFGR_HPRE_DIV1 :
      break;

    case RCC_CFGR_HPRE_DIV2 :
      BAUDCLOCK /= 2;
      break;

    case RCC_CFGR_HPRE_DIV4 :
      BAUDCLOCK /= 4;
      break;

    case RCC_CFGR_HPRE_DIV8 :
      BAUDCLOCK /= 8;
      break;

    case RCC_CFGR_HPRE_DIV16 :
      BAUDCLOCK /= 16;
      break;

    case RCC_CFGR_HPRE_DIV64 :
      BAUDCLOCK /= 64;
      break;

    case RCC_CFGR_HPRE_DIV128 :
      BAUDCLOCK /= 128;
      break;

    case RCC_CFGR_HPRE_DIV256 :
      BAUDCLOCK /= 256;
      break;

    case RCC_CFGR_HPRE_DIV512 :
      BAUDCLOCK /= 512;
      break;

    default :
      assert(false);
      break;
  }

  // Account for APBx divider

  switch (port)
  {
    case 0 :
    case 5 :
      // Serial ports on APB2
      switch (RCC->CFGR & RCC_CFGR_PPRE2)
      {
        case RCC_CFGR_PPRE2_DIV1 :
          break;

        case RCC_CFGR_PPRE2_DIV2 :
          BAUDCLOCK /= 2;
          break;

        case RCC_CFGR_PPRE2_DIV4 :
          BAUDCLOCK /= 4;
          break;

        case RCC_CFGR_PPRE2_DIV8 :
          BAUDCLOCK /= 8;
          break;

        case RCC_CFGR_PPRE2_DIV16 :
          BAUDCLOCK /= 16;
          break;

        default :
          assert(false);
          break;
      }
      break;

    case 1 :
    case 2 :
    case 3 :
    case 4 :
      // Serial ports on APB1
      switch (RCC->CFGR & RCC_CFGR_PPRE1)
      {
        case RCC_CFGR_PPRE1_DIV1 :
          break;

        case RCC_CFGR_PPRE1_DIV2 :
          BAUDCLOCK /= 2;
          break;

        case RCC_CFGR_PPRE1_DIV4 :
          BAUDCLOCK /= 4;
          break;

        case RCC_CFGR_PPRE1_DIV8 :
          BAUDCLOCK /= 8;
          break;

        case RCC_CFGR_PPRE1_DIV16 :
          BAUDCLOCK /= 16;
          break;

        default :
          assert(false);
          break;
      }
      break;
  }

  // Account for sampling interval

  BAUDCLOCK /= 8;

  // Calculate baud rate divisor and fractional part

  divisor = BAUDCLOCK / baudrate;
  fract   = (BAUDCLOCK % baudrate)*16 / baudrate;

  return (divisor << 4) + fract;
}

/* Map serial port device name to port number */

int serial_name_to_port(char *name)
{
  errno_r = 0;

  if (!strncasecmp(name, "com1:", 5))
    return 0;
  else if (!strncasecmp(name, "com2:", 5))
    return 1;
  else if (!strncasecmp(name, "com3:", 5))
    return 2;
  else if (!strncasecmp(name, "com4:", 5))
    return 3;
  else if (!strncasecmp(name, "com5:", 5))
    return 4;
  else if (!strncasecmp(name, "com6:", 5))
    return 5;
  else
  {
    errno_r = ENODEV;
    return -1;
  }
}

/* Initialize serial port */

int serial_open(char *name, unsigned *subdevice)
{
  unsigned port;
  unsigned baudrate;

  errno_r = 0;

// Look up serial port number

  port = serial_name_to_port(name);
  if (port < 0) return port;

// Pass up port number, if requested

  if (subdevice != NULL)
    *subdevice = port;

// Extract baud rate from device name

  baudrate = atoi(name+5);
  if (baudrate == 0)
  {
    errno_r = EINVAL;
    return -1;
  }

// Configure the serial port

  switch (port)
  {
#ifdef USART1
    case 0 : // USART1

// Initialize ring buffers

      if (InitializeRingBuffers(port))
        return -1;

// Turn on USART1 peripheral clock

      RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

#ifdef STM32_M4_CLICKER
// Configure TX pin on PB6

      RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

      GPIOB->AFR[0] &= ~(0xF << 24);
      GPIOB->AFR[0] |= 7 << 24;
      GPIOB->MODER &= ~GPIO_MODER_MODER6;
      GPIOB->MODER |= GPIO_MODER_MODER6_1;
      GPIOB->OTYPER &= ~GPIO_OTYPER_OT_6;
      GPIOB->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR6;
      GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6_1;
      GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR6;

// Configure RX pin PB7

      RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

      GPIOB->AFR[0] &= ~(0xF << 28);
      GPIOB->AFR[0] |= 7 << 28;
      GPIOB->MODER &= ~GPIO_MODER_MODER7;
      GPIOB->MODER |= GPIO_MODER_MODER7_1;
      GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR7;
      GPIOB->PUPDR |= GPIO_PUPDR_PUPDR7_0;
#else
// Configure TX pin on PA9

      RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

      GPIOA->AFR[1] &= ~(0xF << 4);
      GPIOA->AFR[1] |= 7 << 4;
      GPIOA->MODER &= ~GPIO_MODER_MODER9;
      GPIOA->MODER |= GPIO_MODER_MODER9_1;
      GPIOA->OTYPER &= ~GPIO_OTYPER_OT_9;
      GPIOA->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR9;
      GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR9_1;
      GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR9;

// Configure RX pin PA10

      RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

      GPIOA->AFR[1] &= ~(0xF << 8);
      GPIOA->AFR[1] |= 7 << 8;
      GPIOA->MODER &= ~GPIO_MODER_MODER10;
      GPIOA->MODER |= GPIO_MODER_MODER10_1;
      GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR10;
      GPIOA->PUPDR |= GPIO_PUPDR_PUPDR10_0;
#endif

// Configure USART1

      USART1->CR1 = USART_CR1_OVER8|USART_CR1_UE|USART_CR1_RXNEIE|USART_CR1_TE|USART_CR1_RE;
      USART1->CR2 = 0x0000;
      USART1->CR3 = 0x0000;
      USART1->BRR = CalcBRR(port, baudrate);
      USART1->GTPR = 0x0000;

// Enable USART1 interrupts

      NVIC->IP[USART1_IRQn] = 0x88;
      NVIC->ISER[USART1_IRQn / 32] = 1 << USART1_IRQn % 32;
      break;
#endif

#ifdef USART2
    case 1 : // USART2

// Initialize ring buffers

      if (InitializeRingBuffers(port))
        return -1;

// Turn on USART2 peripheral clock

      RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

// Configure TX pin on PA2

      RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

      GPIOA->AFR[0] &= ~(0xF << 8);
      GPIOA->AFR[0] |= 7 << 8;
      GPIOA->MODER &= ~GPIO_MODER_MODER2;
      GPIOA->MODER |= GPIO_MODER_MODER2_1;
      GPIOA->OTYPER &= ~GPIO_OTYPER_OT_2;
      GPIOA->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR2;
      GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR2_1;
      GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR2;

// Configure RX pin on PA3

      RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

      GPIOA->AFR[0] &= ~(0xF << 12);
      GPIOA->AFR[0] |= 7 << 12;
      GPIOA->MODER &= ~GPIO_MODER_MODER3;
      GPIOA->MODER |= GPIO_MODER_MODER3_1;
      GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR3;
      GPIOA->PUPDR |= GPIO_PUPDR_PUPDR3_0;

// Configure USART2

      USART2->CR1 = USART_CR1_OVER8|USART_CR1_UE|USART_CR1_RXNEIE|USART_CR1_TE|USART_CR1_RE;
      USART2->CR2 = 0x0000;
      USART2->CR3 = 0x0000;
      USART2->BRR = CalcBRR(port, baudrate);
      USART2->GTPR = 0x0000;

// Enable USART2 interrupts

      NVIC->IP[USART2_IRQn] = 0x88;
      NVIC->ISER[USART2_IRQn / 32] = 1 << USART2_IRQn % 32;
      break;
#endif

#ifdef USART3
    case 2 : // USART3

// Initialize ring buffers

      if (InitializeRingBuffers(port))
        return -1;

// Turn on USART3 peripheral clock

      RCC->APB1ENR |= RCC_APB1ENR_USART3EN;

// Configure TX pin on PB10

      RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

      GPIOA->AFR[1] &= ~(0xF << 8);
      GPIOA->AFR[1] |= 7 << 8;
      GPIOB->MODER &= ~GPIO_MODER_MODER10;
      GPIOB->MODER |= GPIO_MODER_MODER10_1;
      GPIOB->OTYPER &= ~GPIO_OTYPER_OT_10;
      GPIOB->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR10;
      GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR10_1;
      GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR10;

// Configure RX pin on PB11

      RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

      GPIOA->AFR[1] &= ~(0xF << 12);
      GPIOA->AFR[1] |= 7 << 12;
      GPIOB->MODER &= ~GPIO_MODER_MODER11;
      GPIOB->MODER |= GPIO_MODER_MODER11_1;
      GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR11;
      GPIOB->PUPDR |= GPIO_PUPDR_PUPDR11_0;

// Configure USART3

      USART3->CR1 = USART_CR1_OVER8|USART_CR1_UE|USART_CR1_RXNEIE|USART_CR1_TE|USART_CR1_RE;
      USART3->CR2 = 0x0000;
      USART3->CR3 = 0x0000;
      USART3->BRR = CalcBRR(port, baudrate);
      USART3->GTPR = 0x0000;

// Enable USART3 interrupts

      NVIC->IP[USART3_IRQn] = 0x88;
      NVIC->ISER[USART3_IRQn / 32] = 1 << USART3_IRQn % 32;
      break;
#endif

#ifdef UART4
    case 3 : // UART4

// Initialize ring buffers

      if (InitializeRingBuffers(port))
        return -1;

// Turn on UART4 peripheral clock

      RCC->APB1ENR |= RCC_APB1ENR_UART4EN;

// Configure TX pin on PA0

      RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

      GPIOA->AFR[0] &= ~(0xF << 0);
      GPIOA->AFR[0] |= 8 << 0;
      GPIOA->MODER &= ~GPIO_MODER_MODER0;
      GPIOA->MODER |= GPIO_MODER_MODER0_1;
      GPIOA->OTYPER &= ~GPIO_OTYPER_OT_0;
      GPIOA->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR0;
      GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR0_1;
      GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR0;

// Configure RX pin on PA1

      RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

      GPIOA->AFR[0] &= ~(0xF << 4);
      GPIOA->AFR[0] |= 8 << 4;
      GPIOA->MODER &= ~GPIO_MODER_MODER1;
      GPIOA->MODER |= GPIO_MODER_MODER1_1;
      GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR1;
      GPIOA->PUPDR |= GPIO_PUPDR_PUPDR1_0;

// Configure UART4

      UART4->CR1 = USART_CR1_OVER8|USART_CR1_UE|USART_CR1_RXNEIE|USART_CR1_TE|USART_CR1_RE;
      UART4->CR2 = 0x0000;
      UART4->CR3 = 0x0000;
      UART4->BRR = CalcBRR(port, baudrate);
      UART4->GTPR = 0x0000;

// Enable UART4 interrupts

      NVIC->IP[UART4_IRQn] = 0x88;
      NVIC->ISER[UART4_IRQn / 32] = 1 << UART4_IRQn % 32;
      break;
#endif

#ifdef UART5
    case 4 : // UART5

// Initialize ring buffers

      if (InitializeRingBuffers(port))
        return -1;

// Turn on UART5 peripheral clock

      RCC->APB1ENR |= RCC_APB1ENR_UART5EN;

// Configure TX pin on PC12

      RCC->AHB1ENR|= RCC_AHB1ENR_GPIOCEN;

      GPIOA->AFR[1] &= ~(0xF << 16);
      GPIOA->AFR[1] |= 8 << 16;
      GPIOC->MODER &= ~GPIO_MODER_MODER12;
      GPIOC->MODER |= GPIO_MODER_MODER12_1;
      GPIOC->OTYPER &= ~GPIO_OTYPER_OT_12;
      GPIOC->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR12;
      GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR12_1;
      GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR12;

// Configure RX pin on PD2

      RCC->AHB1ENR|= RCC_AHB1ENR_GPIODEN;

      GPIOA->AFR[0] &= ~(0xF << 8);
      GPIOA->AFR[0] |= 8 << 8;
      GPIOD->MODER &= ~GPIO_MODER_MODER2;
      GPIOD->MODER |= GPIO_MODER_MODER2_1;
      GPIOD->PUPDR &= ~GPIO_PUPDR_PUPDR2;
      GPIOD->PUPDR |= GPIO_PUPDR_PUPDR2_0;

// Configure UART5

      UART5->CR1 = USART_CR1_OVER8|USART_CR1_UE|USART_CR1_RXNEIE|USART_CR1_TE|USART_CR1_RE;
      UART5->CR2 = 0x0000;
      UART5->CR3 = 0x0000;
      UART5->BRR = CalcBRR(port, baudrate);
      UART5->GTPR = 0x0000;

// Enable UART5 interrupts

      NVIC->IP[UART5_IRQn] = 0x88;
      NVIC->ISER[UART5_IRQn / 32] = 1 << UART5_IRQn % 32;
      break;
#endif

#ifdef USART6
    case 5 : //  USART6

// Initialize ring buffers

      if (InitializeRingBuffers(port))
        return -1;

// Turn on USART6 peripheral clock

      RCC->APB2ENR |= RCC_APB2ENR_USART6EN;

#ifdef NUCLEO_F411RE
// Configure TX pin on PA11 (aka Arduino D1, wire wrap CN10 pin 35 to CN10 pin 14)

      RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

      GPIOA->AFR[1] &= ~(0xF << 12);
      GPIOA->AFR[1] |= 8 << 12;
      GPIOA->MODER &= ~GPIO_MODER_MODER11;
      GPIOA->MODER |= GPIO_MODER_MODER11_1;
      GPIOA->OTYPER &= ~GPIO_OTYPER_OT_11;
      GPIOA->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR11;
      GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR11_1;
      GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR11;

// Configure RX pin on PA12 (aka Arduino D0, wire wrap CN10 pin 37 to CN 10 pin 12)

      RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

      GPIOA->AFR[1] &= ~(0xF << 16);
      GPIOA->AFR[1] |= 8 << 16;
      GPIOA->MODER &= ~GPIO_MODER_MODER12;
      GPIOA->MODER |= GPIO_MODER_MODER12_1;
      GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR12;
      GPIOA->PUPDR |= GPIO_PUPDR_PUPDR12_0;
#else
// Configure TX pin on PC6

      RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

      GPIOA->AFR[0] &= ~(0xF << 24);
      GPIOA->AFR[0] |= 8 << 24;
      GPIOC->MODER &= ~GPIO_MODER_MODER6;
      GPIOC->MODER |= GPIO_MODER_MODER6_1;
      GPIOC->OTYPER &= ~GPIO_OTYPER_OT_6;
      GPIOC->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR6;
      GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6_1;
      GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR6;

// Configure RX pin on PC7

      RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

      GPIOA->AFR[0] &= ~(0xF << 28);
      GPIOA->AFR[0] |= 8 << 28;
      GPIOC->MODER &= ~GPIO_MODER_MODER7;
      GPIOC->MODER |= GPIO_MODER_MODER7_1;
      GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR7;
      GPIOC->PUPDR |= GPIO_PUPDR_PUPDR7_0;
#endif

// Configure USART6

      USART6->CR1 = USART_CR1_OVER8|USART_CR1_UE|USART_CR1_RXNEIE|USART_CR1_TE|USART_CR1_RE;
      USART6->CR2 = 0x0000;
      USART6->CR3 = 0x0000;
      USART6->BRR = CalcBRR(port, baudrate);
      USART6->GTPR = 0x0000;

// Enable USART6 interrupts

      NVIC->IP[USART6_IRQn] = 0x88;
      NVIC->ISER[USART6_IRQn / 32] = 1 << USART6_IRQn % 32;
      break;
#endif

    default :
      errno_r = ENODEV;
      return -1;
  }

  return 0;
}

/* Register serial port for standard I/O */

int serial_stdio(char *name)
{
  unsigned subdevice;

  if (serial_open(name, &subdevice))
    return -1;

  // Nuke existing stdin, stdout, stderr

  device_unregister(0);
  device_unregister(1);
  device_unregister(2);

  // Register new stdin, stdout, stderr

  device_register_char_fd(0, subdevice, NULL, serial_read, NULL, serial_rxready, NULL);
  device_register_char_fd(1, subdevice, serial_write, NULL, serial_txready, NULL, NULL);
  device_register_char_fd(2, subdevice, serial_write, NULL, serial_txready, NULL, NULL);

  return 0;
}

/* Register a serial port device */

int serial_register(char *name)
{
  unsigned port;

// Look up serial port number

  port = serial_name_to_port(name);
  if (port < 0) return port;

// Register the serial port driver

  return device_register_char(name, port, serial_open, NULL, serial_write, serial_read, serial_txready, serial_rxready, NULL);
}

/* Return true if receive data is available */

int serial_rxready(unsigned port)
{
  volatile ringbuffer_t *bufptr;

  errno_r = 0;

  if (port >= MAX_SERIAL_PORTS)
  {
    errno_r = ENODEV;
    return -1;
  }

  bufptr = UARTS[port].rxbuffer;

  if (bufptr == NULL)
  {
    errno_r = ENODEV;
    return -1;
  }

  return (bufptr->count > 0);
}

/* Read data from the serial port */

int serial_read(unsigned port, char *buf, unsigned count)
{
  volatile ringbuffer_t *bufptr;
  int len = 0;

  errno_r = 0;

  if (port >= MAX_SERIAL_PORTS)
  {
    errno_r = ENODEV;
    return -1;
  }

  if (buf == NULL)
  {
    errno_r = EINVAL;
    return -1;
  }

  bufptr = UARTS[port].rxbuffer;

  if (bufptr == NULL)
  {
    errno_r = ENODEV;
    return -1;
  }

  while ((bufptr->count > 0) && (count > 0))
  {
    *buf++ = bufptr->data[bufptr->tail];
    count--;
    __disable_irq();
    bufptr->count--;
    __enable_irq();
    bufptr->tail++;
    bufptr->tail &= BUFSIZE-1;
    len++;
  }

  return len;
}

/* Return true if transmitter is ready to accept data */

int serial_txready(unsigned port)
{
  volatile ringbuffer_t *bufptr;

  errno_r = 0;

  if (port >= MAX_SERIAL_PORTS)
  {
    errno_r = ENODEV;
    return -1;
  }

  bufptr = UARTS[port].txbuffer;

  if (bufptr == NULL)
  {
    errno_r = ENODEV;
    return -1;
  }

  return (bufptr->count < BUFSIZE);
}

/* Send data out the serial port */

int serial_write(unsigned port, char *buf, unsigned count)
{
  volatile ringbuffer_t *bufptr;
  int len = 0;

  errno_r = 0;

  if (port >= MAX_SERIAL_PORTS)
  {
    errno_r = ENODEV;
    return -1;
  }

  if (buf == NULL)
  {
    errno_r = EINVAL;
    return -1;
  }

  bufptr = UARTS[port].txbuffer;

  if (bufptr == NULL)
  {
    errno_r = ENODEV;
    return -1;
  }

  while ((bufptr->count < BUFSIZE) && (count > 0))
  {
    bufptr->data[bufptr->head] = *buf++;
    count--;
    __disable_irq();
    bufptr->count++;
    __enable_irq();
    bufptr->head++;
    bufptr->head &= BUFSIZE-1;
    len++;

    // Enable TXEIE interrupt
    *UARTS[port].TXEIE = true;
  }

  return len;
}

//*************** UART interrupt service routines follow ****************

#ifdef USART1
#define USART1_DR	(*((volatile unsigned *) 0x40011004))
#define USART1_RXNE	(*((volatile unsigned *) 0x42220014))
#define USART1_TXE	(*((volatile unsigned *) 0x4222001C))
#define USART1_RXNEIE	(*((volatile unsigned *) 0x42220194))
#define USART1_TXEIE	(*((volatile unsigned *) 0x4222019C))

void USART1_IRQHandler(void)
{
  if (USART1_RXNEIE && USART1_RXNE)
  {
    volatile ringbuffer_t *bufptr = UARTS[0].rxbuffer;

    if (bufptr->count == BUFSIZE)
    {
      // Receive buffer is full; discard overrun data
      USART1_DR;
    }
    else
    {
      bufptr->data[bufptr->head] = USART1_DR;
      bufptr->count++;
      bufptr->head++;
      bufptr->head &= BUFSIZE-1;
    }
  }

  if (USART1_TXEIE && USART1_TXE)
  {
    volatile ringbuffer_t *bufptr = UARTS[0].txbuffer;

    if (bufptr->count == 0)
    {
      // Transmit buffer is empty; disable interrupt
      USART1_TXEIE = 0;	
    }
    else
    {
      USART1_DR = bufptr->data[bufptr->tail];
      bufptr->count--;
      bufptr->tail++;
      bufptr->tail &= BUFSIZE-1;
    }
  }
}
#endif

#ifdef USART2
#define USART2_DR	(*((volatile unsigned *) 0x40004404))
#define USART2_RXNE	(*((volatile unsigned *) 0x42088014))
#define USART2_TXE	(*((volatile unsigned *) 0x4208801C))
#define USART2_RXNEIE	(*((volatile unsigned *) 0x42088194))
#define USART2_TXEIE	(*((volatile unsigned *) 0x4208819C))

void USART2_IRQHandler(void)
{
  if (USART2_RXNEIE && USART2_RXNE)
  {
    volatile ringbuffer_t *bufptr = UARTS[1].rxbuffer;

    if (bufptr->count == BUFSIZE)
    {
      // Receive buffer is full; discard overrun data
      USART2_DR;
    }
    else
    {
      bufptr->data[bufptr->head] = USART2_DR;
      bufptr->count++;
      bufptr->head++;
      bufptr->head &= BUFSIZE-1;
    }
  }

  if (USART2_TXEIE && USART2_TXE)
  {
    volatile ringbuffer_t *bufptr = UARTS[1].txbuffer;

    if (bufptr->count == 0)
    {
      // Transmit buffer is empty; disable interrupt
      USART2_TXEIE = 0;	
    }
    else
    {
      USART2_DR = bufptr->data[bufptr->tail];
      bufptr->count--;
      bufptr->tail++;
      bufptr->tail &= BUFSIZE-1;
    }
  }
}
#endif

#ifdef USART3
#define USART3_DR	(*((volatile unsigned *) 0x40004804))
#define USART3_RXNE	(*((volatile unsigned *) 0x42090014))
#define USART3_TXE	(*((volatile unsigned *) 0x4209001C))
#define USART3_RXNEIE	(*((volatile unsigned *) 0x42090194))
#define USART3_TXEIE	(*((volatile unsigned *) 0x4209019C))

void USART3_IRQHandler(void)
{
  if (USART3_RXNEIE && USART3_RXNE)
  {
    volatile ringbuffer_t *bufptr = UARTS[2].rxbuffer;

    if (bufptr->count == BUFSIZE)
    {
      // Receive buffer is full; discard overrun data
      USART3_DR;
    }
    else
    {
      bufptr->data[bufptr->head] = USART3_DR;
      bufptr->count++;
      bufptr->head++;
      bufptr->head &= BUFSIZE-1;
    }
  }

  if (USART3_TXEIE && USART3_TXE)
  {
    volatile ringbuffer_t *bufptr = UARTS[2].txbuffer;

    if (bufptr->count == 0)
    {
      // Transmit buffer is empty; disable interrupt
      USART3_TXEIE = 0;	
    }
    else
    {
      USART3_DR = bufptr->data[bufptr->tail];
      bufptr->count--;
      bufptr->tail++;
      bufptr->tail &= BUFSIZE-1;
    }
  }
}
#endif

#ifdef UART4
#define UART4_DR	(*((volatile unsigned *) 0x40004C04))
#define UART4_RXNE	(*((volatile unsigned *) 0x42098014))
#define UART4_TXE	(*((volatile unsigned *) 0x4209801C))
#define UART4_RXNEIE	(*((volatile unsigned *) 0x42098194))
#define UART4_TXEIE	(*((volatile unsigned *) 0x4209819C))

void UART4_IRQHandler(void)
{
  if (UART4_RXNEIE && UART4_RXNE)
  {
    volatile ringbuffer_t *bufptr = UARTS[3].rxbuffer;

    if (bufptr->count == BUFSIZE)
    {
      // Receive buffer is full; discard overrun data
      UART4_DR;
    }
    else
    {
      bufptr->data[bufptr->head] = UART4_DR;
      bufptr->count++;
      bufptr->head++;
      bufptr->head &= BUFSIZE-1;
    }
  }

  if (UART4_TXEIE && UART4_TXE)
  {
    volatile ringbuffer_t *bufptr = UARTS[3].txbuffer;

    if (bufptr->count == 0)
    {
      // Transmit buffer is empty; disable interrupt
      UART4_TXEIE = 0;	
    }
    else
    {
      UART4_DR = bufptr->data[bufptr->tail];
      bufptr->count--;
      bufptr->tail++;
      bufptr->tail &= BUFSIZE-1;
    }
  }
}
#endif

#ifdef UART5
#define UART5_DR	(*((volatile unsigned *) 0x40005004))
#define UART5_RXNE	(*((volatile unsigned *) 0x420A0014))
#define UART5_TXE	(*((volatile unsigned *) 0x420A001C))
#define UART5_RXNEIE	(*((volatile unsigned *) 0x420A0194))
#define UART5_TXEIE	(*((volatile unsigned *) 0x420A019C))

void UART5_IRQHandler(void)
{
  if (UART5_RXNEIE && UART5_RXNE)
  {
    volatile ringbuffer_t *bufptr = UARTS[4].rxbuffer;

    if (bufptr->count == BUFSIZE)
    {
      // Receive buffer is full; discard overrun data
      UART5_DR;
    }
    else
    {
      bufptr->data[bufptr->head] = UART5_DR;
      bufptr->count++;
      bufptr->head++;
      bufptr->head &= BUFSIZE-1;
    }
  }

  if (UART5_TXEIE && UART5_TXE)
  {
    volatile ringbuffer_t *bufptr = UARTS[4].txbuffer;

    if (bufptr->count == 0)
    {
      // Transmit buffer is empty; disable interrupt
      UART5_TXEIE = 0;	
    }
    else
    {
      UART5_DR = bufptr->data[bufptr->tail];
      bufptr->count--;
      bufptr->tail++;
      bufptr->tail &= BUFSIZE-1;
    }
  }
}
#endif

#ifdef USART6
#define USART6_DR	(*((volatile unsigned *) 0x40011404))
#define USART6_RXNE	(*((volatile unsigned *) 0x42228014))
#define USART6_TXE	(*((volatile unsigned *) 0x4222801C))
#define USART6_RXNEIE	(*((volatile unsigned *) 0x42228194))
#define USART6_TXEIE	(*((volatile unsigned *) 0x4222819C))

void USART6_IRQHandler(void)
{
  if (USART6_RXNEIE && USART6_RXNE)
  {
    volatile ringbuffer_t *bufptr = UARTS[5].rxbuffer;

    if (bufptr->count == BUFSIZE)
    {
      // Receive buffer is full; discard overrun data
      USART6_DR;
    }
    else
    {
      bufptr->data[bufptr->head] = USART6_DR;
      bufptr->count++;
      bufptr->head++;
      bufptr->head &= BUFSIZE-1;
    }
  }

  if (USART6_TXEIE && USART6_TXE)
  {
    volatile ringbuffer_t *bufptr = UARTS[5].txbuffer;

    if (bufptr->count == 0)
    {
      // Transmit buffer is empty; disable interrupt
      USART6_TXEIE = 0;	
    }
    else
    {
      USART6_DR = bufptr->data[bufptr->tail];
      bufptr->count--;
      bufptr->tail++;
      bufptr->tail &= BUFSIZE-1;
    }
  }
}
#endif
