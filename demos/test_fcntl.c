/* Simple fcntl() test program */

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
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cpu.h>

// fcntl() handler for a fictitious device

int mydevice_fcntl(unsigned subdevice, int cmd, va_list args)
{
  errno_r = 0;

  switch (cmd)
  {
    // Single integer argument
    case 1111 :
      printf("subdevice=>%d cmd=>%d arg=>%d\n",
        subdevice, cmd, va_arg(args, int));
      return 1234;

    // Multiple integer arguments
    case 2222 :
      printf("subdevice=>%d cmd=>%d arg1=>%d arg2=>%d arg3=>%d arg4=>%d\n",
        subdevice, cmd, va_arg(args, int), va_arg(args, int), va_arg(args, int), va_arg(args, int));
      return 2345;

    // String argument
    case 3333 :
      printf("subdevice=>%d cmd=>%d buf=%s\n",
        subdevice, cmd, va_arg(args, char *));
      return 3456;

    // Address and length
    case 4444 :
    {
      char *buf = va_arg(args, char *);
      int len = va_arg(args, int);

      printf("subdevice=>%d cmd=>%d len=%d\n",
        subdevice, cmd, len);

      snprintf(buf, len, "Hello, world");
      return 4567;
    }

    default :
      errno_r = EIO;
      return -1;
  };

  return 0;
}

int main(void)
{
  int result;
  char buf[256];

  cpu_init(DEFAULT_CPU_FREQ);
  serial_stdio(CONSOLE_PORT);

  printf("\033[H\033[2J%s fcntl() Test (" __DATE__ " " __TIME__ ")\n\n", MCUFAMILYNAME);
  puts(revision);
  printf("\nCPU Freq:%u Hz  Compiler:%s %s %s\n\n", (unsigned int) SystemCoreClock,
    __COMPILER__, __VERSION__, __ABI__);

  result = fcntl(fileno(stdin),  F_GETFL, 0);
  if (result < 0)
  {
    printf("ERROR: fcntl() failed, %s\n", strerror(errno));
    exit(1);
  }
  else
  {
    printf("stdin  flags are %08X\n", result);
  }

  result = fcntl(fileno(stdout),  F_GETFL, 0);
  if (result < 0)
  {
    printf("ERROR: fcntl() failed, %s\n", strerror(errno));
    exit(1);
  }
  else
  {
    printf("stdout flags are %08X\n", result);
  }

  result = fcntl(fileno(stderr),  F_GETFL, 0);
  if (result < 0)
  {
    printf("ERROR: fcntl() failed, %s\n", strerror(errno));
    exit(1);
  }
  else
  {
    printf("stderr flags are %08X\n", result);
  }

  // Register dummy device "mydevice"

  result = device_register_char("mydevice:", 1234, NULL, NULL, NULL, NULL, NULL, NULL, mydevice_fcntl);
  if (result < 0)
  {
    printf("ERROR: device_register_char() failed, %s\n", strerror(errno));
    exit(1);
  }

  puts("\nOpening mydevice:...\n");

  int fd = open("mydevice:", O_RDWR);
  if (fd < 0)
  {
    printf("ERROR: open() failed, %s\n", strerror(errno));
    exit(1);
  }

  // Single integer argument
  result = fcntl(fd, 1111, 2222);
  if (result < 0)
    printf("ERROR: fcntl() failed, %s\n", strerror(errno));
  else
    printf("fcntl() returned %d\n", result);

  // Multiple integer arguments
  result = fcntl(fd, 2222, 44, 33, 22, 11);
  if (result < 0)
    printf("ERROR: fcntl() failed, %s\n", strerror(errno));
  else
    printf("fcntl() returned %d\n", result);

  // String argument
  result = fcntl(fd, 3333, "This is a test");
  if (result < 0)
    printf("ERROR: fcntl() failed, %s\n", strerror(errno));
  else
    printf("fcntl() returned %d\n", result);

  // Address and length arguments
  result = fcntl(fd, 4444, buf, sizeof(buf));
  if (result < 0)
    printf("ERROR: fcntl() failed, %s\n", strerror(errno));
  else
  {
    printf("fcntl() returned %d\n", result);
    puts(buf);
  }

  // Invalid command
  result = fcntl(fd, 5555, 0);
  if (result < 0)
    printf("ERROR: fcntl() failed, %s\n", strerror(errno));
  else
    printf("fcntl() returned %d\n", result);

  puts("\nClosing mydevice:...\n");

  if (close(fd))
  {
    printf("ERROR: close() failed, %s\n", strerror(errno));
    exit(1);
  }

  exit(0);
}
