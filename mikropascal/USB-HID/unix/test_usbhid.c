// Simple USB HID device test program

// $Id$

// Copyright (C)2015, Philip Munts, President, Munts AM Corp.
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <hidapi/hidapi.h>

#define REPORTSIZE	65
#define COMMAND		argv[1]

int main(int argc, char* argv[])
{
  unsigned char buf[REPORTSIZE];
  hid_device *handle;

  // Validate parameters

  if (argc != 2)
  {
    fprintf(stderr, "Usage: test_usbhid on|off\n");
    exit(1);
  }

  if (strcasecmp(COMMAND, "on") && strcasecmp(COMMAND, "off"))
  {
    fprintf(stderr, "Usage: test_usbhid on|off\n");
    exit(1);
  }

  // Open USB hid device

  hid_init();

  handle = hid_open(0x16D0, 0x0AFA, NULL);
  if (handle == NULL)
  {
    fprintf(stderr, "ERROR: hid_open() failed, %s\n", strerror(errno));
    exit(1);
  }

  // Set the LED state

  memset(buf, 0, sizeof(buf));

  if (!strcasecmp(COMMAND, "on"))
    memcpy(buf+1, "LEDON", 5);
  else
    memcpy(buf+1, "LEDOFF", 6);

  hid_write(handle, buf, REPORTSIZE);

  hid_exit();

  exit(0);
}
