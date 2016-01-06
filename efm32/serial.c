/******************************************************************************/
/*                                                                            */
/*          Simple serial port I/O routines for the EFM32 ARM MCU             */
/*                                                                            */
/******************************************************************************/

// $Id$

// Copyright (C)2012-2015, Philip Munts, President, Munts AM Corp.
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
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SERIAL_PORTS	5

static USART_TypeDef * const UARTS[MAX_SERIAL_PORTS] =
{
#ifdef UART0
  UART0,
#else
  NULL,
#endif

#ifdef UART1
  UART1,
#else
  NULL,
#endif

#ifdef USART0
  USART0,
#else
  NULL,
#endif

#ifdef USART1
  USART1,
#else
  NULL,
#endif

#ifdef USART2
  USART2,
#else
  NULL,
#endif
};

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
  else
  {
    errno_r = ENODEV;
    return -1;
  }
}

/* Initialize serial port */

int serial_open(char *name, unsigned int *subdevice)
{
  unsigned int port;
  unsigned int baudrate;
  USART_InitAsync_TypeDef usartInit;

  errno_r = 0;

// Look up serial port number

  port = serial_name_to_port(name);
  if (port < 0) return port;

// Pass up port number, if requested

  if (subdevice != NULL)
    *subdevice = port;

// Extract baud rate from device name

  baudrate = atoi(name+5);

  switch (port)
  {
#ifdef UART0
    case 0 :

// Enable peripheral clocks

      CMU_ClockEnable(cmuClock_GPIO, true);
      CMU_ClockEnable(cmuClock_UART0, true);

// Configure the serial port

      usartInit.enable = usartEnable;
      usartInit.refFreq = 0;
      usartInit.baudrate = baudrate;
      usartInit.oversampling = usartOVS16;
      usartInit.databits = usartDatabits8;
      usartInit.parity = usartNoParity;
      usartInit.stopbits = usartStopbits1;

      USART_InitAsync(UART0, &usartInit);

// Configure I/O pins

#ifdef EFM32_G8XX_STK
      // Route UART0 pins to PE0 and PE1
      UART0[port]->ROUTE = USART_ROUTE_RXPEN|USART_ROUTE_TXPEN|USART_ROUTE_LOCATION_LOC1;

      // Configure PE0 and PE1
      GPIO_PinModeSet(gpioPortE, 0, gpioModePushPull, 1);
      GPIO_PinModeSet(gpioPortE, 1, gpioModeInput, 1);

      // Clear BC_EN to disconnect UART0 from board controller
      GPIO_PinModeSet(gpioPortD, 13, gpioModePushPull, 1);
      GPIO_PinOutClear(gpioPortD, 13);
#endif
      break;
#endif

#ifdef UART1
    case 1 :

// Enable peripheral clocks

      CMU_ClockEnable(cmuClock_GPIO, true);
      CMU_ClockEnable(cmuClock_UART1, true);

// Configure the serial port

      usartInit.enable = usartEnable;
      usartInit.refFreq = 0;
      usartInit.baudrate = baudrate;
      usartInit.oversampling = usartOVS16;
      usartInit.databits = usartDatabits8;
      usartInit.parity = usartNoParity;
      usartInit.stopbits = usartStopbits1;

      USART_InitAsync(UART1, &usartInit);

// Configure I/O pins

      break;
#endif

#ifdef USART0
    case 2 :

// Enable peripheral clocks

      CMU_ClockEnable(cmuClock_GPIO, true);
      CMU_ClockEnable(cmuClock_USART0, true);

// Configure the serial port

      usartInit.enable = usartEnable;
      usartInit.refFreq = 0;
      usartInit.baudrate = baudrate;
      usartInit.oversampling = usartOVS16;
      usartInit.databits = usartDatabits8;
      usartInit.parity = usartNoParity;
      usartInit.stopbits = usartStopbits1;

      USART_InitAsync(USART0, &usartInit);

// Configure I/O pins

      break;
#endif

#ifdef USART1
    case 3 :

// Enable peripheral clocks

      CMU_ClockEnable(cmuClock_GPIO, true);
      CMU_ClockEnable(cmuClock_USART1, true);

// Configure the serial port

      usartInit.enable = usartEnable;
      usartInit.refFreq = 0;
      usartInit.baudrate = baudrate;
      usartInit.oversampling = usartOVS16;
      usartInit.databits = usartDatabits8;
      usartInit.parity = usartNoParity;
      usartInit.stopbits = usartStopbits1;

      USART_InitAsync(USART1, &usartInit);

// Configure I/O pins

#ifdef EFM32G230F128_PROTOTYPE
      // Route USART1 pins to PD0 and PD1
      USART1->ROUTE = USART_ROUTE_RXPEN|USART_ROUTE_TXPEN|USART_ROUTE_LOCATION_LOC1;

      // Configure I/O pins PD0 and PD1
      GPIO_PinModeSet(gpioPortD, 0, gpioModePushPull, 1);
      GPIO_PinModeSet(gpioPortD, 1, gpioModeInput, 1);
#endif

      break;
#endif

#ifdef USART2
    case 4 :

// Enable peripheral clocks

      CMU_ClockEnable(cmuClock_GPIO, true);
      CMU_ClockEnable(cmuClock_USART2, true);

// Configure the serial port

      usartInit.enable = usartEnable;
      usartInit.refFreq = 0;
      usartInit.baudrate = baudrate;
      usartInit.oversampling = usartOVS16;
      usartInit.databits = usartDatabits8;
      usartInit.parity = usartNoParity;
      usartInit.stopbits = usartStopbits1;

      USART_InitAsync(USART2, &usartInit);

// Configure I/O pins

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
  unsigned int subdevice;

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
  unsigned int port;

// Look up serial port number

  port = serial_name_to_port(name);
  if (port < 0) return port;

// Register the serial port driver

  return device_register_char(name, port, serial_open, NULL, serial_write, serial_read, serial_txready, serial_rxready, NULL);
}

/* Return TRUE if transmitter is ready to accept data */

int serial_txready(unsigned int port)
{
  errno_r = 0;

  if (port >= MAX_SERIAL_PORTS)
  {
    errno_r = ENODEV;
    return -1;
  }

  if (UARTS[port] == NULL)
  {
    errno_r = ENODEV;
    return -1;
  }

  if (UARTS[port]->STATUS & USART_STATUS_TXBL)
    return 1;
  else
    return 0;
}

/* Send a buffer to the serial port */

int serial_write(unsigned int port, char *buf, unsigned int count)
{
  errno_r = 0;

  if (port >= MAX_SERIAL_PORTS)
  {
    errno_r = ENODEV;
    return -1;
  }

  if (UARTS[port] == NULL)
  {
    errno_r = ENODEV;
    return -1;
  }

  if (serial_txready(port))
  {
    UARTS[port]->TXDATA = *buf++;
    return 1;
  }

  return 0;
}

/* Return TRUE if receive data is available */

int serial_rxready(unsigned int port)
{
  errno_r = 0;

  if (port >= MAX_SERIAL_PORTS)
  {
    errno_r = ENODEV;
    return -1;
  }

  if (UARTS[port] == NULL)
  {
    errno_r = ENODEV;
    return -1;
  }

  if (UARTS[port]->STATUS & USART_STATUS_RXDATAV)
    return 1;
  else
    return 0;
}

/* Read buffer from the serial port */

int serial_read(unsigned int port, char *buf, unsigned int count)
{
  errno_r = 0;

  if (port >= MAX_SERIAL_PORTS)
  {
    errno_r = ENODEV;
    return -1;
  }

  if (UARTS[port] == NULL)
  {
    errno_r = ENODEV;
    return -1;
  }

  if (serial_rxready(port))
  {
    *buf++ = UARTS[port]->RXDATA;
    return 1;
  }

  return 0;
}
