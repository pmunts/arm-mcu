// LabView LINX Remote I/O Protocol Server Main Module

// Copyright (C)2016-2018, Philip Munts, President, Munts AM Corp.
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

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <cpu.h>

#include <linx-server/common.h>
#include <linx-server/gpio-gpiopins.h>

// Device identification constants

extern const uint8_t LINX_DEVICE_FAMILY	= 255;
extern const uint8_t LINX_DEVICE_ID	= 4;
extern const char LINX_DEVICE_NAME[]	= BOARDNAME " C++ LabView LINX Remote I/O Server";

int main(void)
{
  int32_t fd;
  int32_t error;

  cpu_init(DEFAULT_CPU_FREQ);
  serial_stdio((char *) CONSOLE_PORT);

  printf("\033[H\033[2J%s C++ LabView LINX Test Server (" __DATE__ " " __TIME__ ")\n\n", MCUFAMILYNAME);
  printf("CPU Freq:%u Hz  Compiler:%s %s %s\n\n", (unsigned int) SystemCoreClock,
    __COMPILER__, __VERSION__, __ABI__);

  // Initialize the serial port connected to the controlling device

  if (serial_register((char *) AUX_PORT) < 0)
  {
    printf("ERROR: serial_register() for control port failed, %s\n", strerror(errno));
    exit(1);
  }

  fd = open((char *) AUX_PORT, O_RDWR|O_BINARY);
  if (fd < 0)
  {
    printf("ERROR: open() for control port failed, %s\n", strerror(errno));
    exit(1);
  }

  // Register command handlers

  common_init();
  analog_init();
  gpio_init();
  pwm_init();
  servo_init();

  // Register peripheral channel objects

  try
  {
#ifdef NUCLEO_F411RE
    // Arduino digital I/O pins on expansion headers CN9 and CN5.
    // Note that D0 and D1 are dedicated to the USART6 serial port and
    // are not available for digital I/O.

    gpio_add_channel(2,  new GPIO_GPIOPIN(GPIOPIN10, &GPIOPIN10IN, &GPIOPIN10OUT)); // PA10 aka Arduino D2
    gpio_add_channel(3,  new GPIO_GPIOPIN(GPIOPIN19, &GPIOPIN19IN, &GPIOPIN19OUT)); // PB3  aka Arduino D3
    gpio_add_channel(4,  new GPIO_GPIOPIN(GPIOPIN21, &GPIOPIN21IN, &GPIOPIN21OUT)); // PB5  aka Arduino D4
    gpio_add_channel(5,  new GPIO_GPIOPIN(GPIOPIN20, &GPIOPIN20IN, &GPIOPIN20OUT)); // PB4  aka Arduino D5
    gpio_add_channel(6,  new GPIO_GPIOPIN(GPIOPIN26, &GPIOPIN26IN, &GPIOPIN26OUT)); // PB10 aka Arduino D6
    gpio_add_channel(7,  new GPIO_GPIOPIN(GPIOPIN8,  &GPIOPIN8IN,  &GPIOPIN8OUT));  // PA8  aka Arduino D7
    gpio_add_channel(8,  new GPIO_GPIOPIN(GPIOPIN9,  &GPIOPIN9IN,  &GPIOPIN9OUT));  // PA9  aka Arduino D8
    gpio_add_channel(9,  new GPIO_GPIOPIN(GPIOPIN39, &GPIOPIN39IN, &GPIOPIN39OUT)); // PC7  aka Arduino D9
    gpio_add_channel(10, new GPIO_GPIOPIN(GPIOPIN22, &GPIOPIN22IN, &GPIOPIN22OUT)); // PB6  aka Arduino D10
    gpio_add_channel(11, new GPIO_GPIOPIN(GPIOPIN7,  &GPIOPIN7IN,  &GPIOPIN7OUT));  // PA7  aka Arduino D11
    gpio_add_channel(12, new GPIO_GPIOPIN(GPIOPIN6,  &GPIOPIN6IN,  &GPIOPIN6OUT));  // PA6  aka Arduino D12
    gpio_add_channel(13, new GPIO_GPIOPIN(GPIOPIN5,  &GPIOPIN5IN,  &GPIOPIN5OUT));  // PA5  aka Arduino D13 aka LED
    gpio_add_channel(14, new GPIO_GPIOPIN(GPIOPIN25, &GPIOPIN25IN, &GPIOPIN25OUT)); // PB9  aka Arduino D14
    gpio_add_channel(15, new GPIO_GPIOPIN(GPIOPIN24, &GPIOPIN24IN, &GPIOPIN24OUT)); // PB8  aka Arduino D15
#endif
  }

  catch (...)
  {
    printf("ERROR: A peripheral channel constructor failed\n");
    exit(1);
  }

  // Process commands

  executive(fd, &error);
}
