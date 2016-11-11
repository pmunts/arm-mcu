// LabView LINX Remote I/O Protocol Server Main Module

// Copyright (C)2016, Philip Munts, President, Munts AM Corp.
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

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <cpu.h>

#include "common.h"
#include "executive.h"

// Device identification constants

extern const uint8_t LINX_DEVICE_FAMILY		= 255;
extern const uint8_t LINX_DEVICE_ID		= 4;
extern const char LINX_DEVICE_NAME[]		= BOARDNAME " C++ LabView LINX Remote I/O Server";

// Command handler installers

extern void common_init(void);

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

  // Process commands

  executive(fd, &error);
}
