/* Simple blocking I/O test program */

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

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cpu.h>

int main(void)
{
  char buf[256];
  int result;

  cpu_init(DEFAULT_CPU_FREQ);
  serial_stdio(CONSOLE_PORT);

  printf("\033[H\033[2J%s Blocking I/O Test (" __DATE__ " " __TIME__ ")\n\n", MCUFAMILYNAME);
  printf("CPU Freq:%u Hz  Compiler:%s %s %s\n\n", (unsigned int) SystemCoreClock,
    __COMPILER__, __VERSION__, __ABI__);

  systick_init(100, NULL);

  puts("Test case 1: Default should be cooked, blocking\n");

  result = fcntl(fileno(stdin), F_GETFL, 0);
  if (result < 0)
  {
    printf("ERROR: fcntl() failed, %s\n", strerror(errno));
    exit(1);
  }

  printf("O_BINARY   is %s\n", (result & O_BINARY)   ? "set" : "not set");
  printf("O_NONBLOCK is %s\n", (result & O_NONBLOCK) ? "set" : "not set");

  printf("\nEnter some data: ");
  fflush(stdout);

  result = read(fileno(stdin), buf, sizeof(buf));
  if (result < 0)
  {
    printf("ERROR: read() failed, %s\n", strerror(errno));
    exit(1);
  }

  printf("\nread() returned %d bytes\n\n", result);

  puts("Test case 2: raw, blocking\n");

  result = fcntl(fileno(stdin), F_GETFL, 0);
  if (result < 0)
  {
    printf("ERROR: fcntl() failed, %s\n", strerror(errno));
    exit(1);
  }

  result |= O_BINARY;

  result = fcntl(fileno(stdin), F_SETFL, result);
  if (result < 0)
  {
    printf("ERROR: fcntl() failed, %s\n", strerror(errno));
    exit(1);
  }

  result = fcntl(fileno(stdin), F_GETFL, 0);
  if (result < 0)
  {
    printf("ERROR: fcntl() failed, %s\n", strerror(errno));
    exit(1);
  }

  printf("O_BINARY   is %s\n", (result & O_BINARY)   ? "set" : "not set");
  printf("O_NONBLOCK is %s\n", (result & O_NONBLOCK) ? "set" : "not set");

  printf("\nEnter some data: ");
  fflush(stdout);

  result = read(fileno(stdin), buf, sizeof(buf));
  if (result < 0)
  {
    printf("ERROR: read() failed, %s\n", strerror(errno));
    exit(1);
  }

  printf("\n\nread() returned %d bytes\n\n", result);

  puts("Test case 3: raw, nonblocking\n");

  result = fcntl(fileno(stdin), F_GETFL, 0);
  if (result < 0)
  {
    printf("ERROR: fcntl() failed, %s\n", strerror(errno));
    exit(1);
  }

  result |= O_NONBLOCK;

  result = fcntl(fileno(stdin), F_SETFL, result);
  if (result < 0)
  {
    printf("ERROR: fcntl() failed, %s\n", strerror(errno));
    exit(1);
  }

  result = fcntl(fileno(stdin), F_GETFL, 0);
  if (result < 0)
  {
    printf("ERROR: fcntl() failed, %s\n", strerror(errno));
    exit(1);
  }

  printf("O_BINARY   is %s\n", (result & O_BINARY)   ? "set" : "not set");
  printf("O_NONBLOCK is %s\n", (result & O_NONBLOCK) ? "set" : "not set");

  printf("\nEnter some data: ");
  fflush(stdout);

  result = read(fileno(stdin), buf, sizeof(buf));
  if (result < 0)
  {
    printf("ERROR: read() failed, %s\n", strerror(errno));
    exit(1);
  }

  printf("\n\nread() returned %d bytes\n\n", result);

  printf("Keep trying:\n\n");
  fflush(stdout);

  for (;;)
  {
    sleep(1);

    memset(buf, 0, sizeof(buf));

    result = read(fileno(stdin), buf, sizeof(buf));
    if (result < 0)
    {
      printf("ERROR: read() failed, %s\n", strerror(errno));
      exit(1);
    }

    if (result == 0)
    {
      putchar('.');
      fflush(stdout);
    }

    if (result > 0)
    {
      printf("\nread() returned %d bytes\n", result);
      printf("You entered: %s\n", buf);
      fflush(stdout);
    }
  }
}
