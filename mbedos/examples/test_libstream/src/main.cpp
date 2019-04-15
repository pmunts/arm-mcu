// ARM Mbed OS Stream Framing Protocol Serial Port Loopback Test

// Copyright (C)2018-2019, Philip Munts, President, Munts AM Corp.
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

#include <mbed.h>

#include <assert.h>
#include <ctype.h>
#include <errno.h>

#include <libstream.h>

Serial console(SERIAL_TX, SERIAL_RX);

// We will replace the default read() function in libstream with the following:

static ssize_t reader(int fd, void *buf, size_t bufsize)
{
  while (!console.readable());
  uint8_t *dst = (uint8_t *) buf;
  *dst = console.getc();
  return 1;
}

// We will replace the default write() function in libstream with the following:

static ssize_t writer(int fd, const void *buf, size_t bufsize)
{
  uint8_t *src = (uint8_t *) buf;
  unsigned i;

  for (i = 0; i < bufsize; i++)
  {
    while (!console.writable());
    console.putc(*src++);
  }

  return bufsize;
}

#define MSGSIZE		1024
#define FRAMESIZE	(2*MSGSIZE + 8)

int main(void)
{
  int32_t fd = 0;
  int32_t error;
  char msg[MSGSIZE];
  int32_t msgsize;
  uint8_t frame[FRAMESIZE];
  int32_t framesize;
  int32_t count;
  int i;

  // Initialize the serial port

  console.baud(115200);

  // Replace the default stream reader and writer functions in libstream

  STREAM_change_readfn(reader, &error);
  assert(error == 0);

  STREAM_change_writefn(writer, &error);
  assert(error == 0);

  // Clear the frame buffer for the first incoming frame

  memset(frame, 0, sizeof(frame));
  framesize = 0;

  // Message loop

  for (;;)
  {
    // Receive an incoming frame

    STREAM_receive_frame(fd, frame, sizeof(frame), &framesize, &error);
    if (error == EAGAIN) continue;
    assert(error == 0);

    // Decode the frame and extract the incoming message

    STREAM_decode_frame(frame, framesize, msg, sizeof(msg), &msgsize, &error);
    assert(error == 0);

    // Transform the incoming message to ALL CAPS

    for (i = 0; i < msgsize; i++)
      msg[i] = toupper(msg[i]);

    // Encode the outgoing message

    STREAM_encode_frame(msg, msgsize, frame, sizeof(frame), &framesize, &error);
    assert(error == 0);

    // Send the outgoing frame

    STREAM_send_frame(fd, frame, framesize, &count, &error);
    assert(error == 0);

    // Clear the frame buffer for the next incoming frame

    memset(frame, 0, sizeof(frame));
    framesize = 0;
  }
}
