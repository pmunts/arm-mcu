// Simple byte stream message framing library

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

#ifdef MCUFAMILYNAME
#include <arm.h>
#ifdef errno
#undef errno
#define errno (*(__errno()))
#endif
#else
#include <cplusplus.h>
#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#endif

#include <stream_framing.h>
#include <unistd.h>

// Frame delimiters

#define DLE	0x10
#define STX	0x02
#define ETX	0x03

// The following CRC16-CCITT subroutine came from:
// http://stackoverflow.com/questions/10564491/function-to-calculate-a-crc16-checksum

static uint16_t crc16(const uint8_t* data_p, uint8_t length){
    uint8_t x;
    uint16_t crc = 0x1D0F;

    while (length--){
        x = crc >> 8 ^ *data_p++;
        x ^= x>>4;
        crc = (crc << 8) ^ ((uint16_t)(x << 12)) ^ ((uint16_t)(x <<5)) ^ ((uint16_t)x);
    }
    return crc;
}

// Encode a message frame, with DLE byte stuffing and CRC16-CCITT
// frame check sequence.  The size of the destination buffer should
// be twice the size of the source buffer, plus 8 bytes worst case.
// Return zero if successfully encoded.

int StreamEncodeFrame(void *src, size_t srclen, void *dst, size_t dstsize, size_t *dstlen)
{
  uint8_t *p = src;
  uint8_t *q = dst;
  uint16_t crc = 0;

  // Verify parameters

  if (dstsize < 6) return -1;

  // Calculate frame check sequence (CRC16-CCITT of payload bytes)

  crc = crc16(src, srclen);

  // Prefix start of frame delimiter

  *q++ = DLE;
  *q++ = STX;
  *dstlen = 2;

  // Copy data bytes, with DLE byte stuffing

  while (srclen--)
  {
    if (*p == DLE)
    {
      *q++ = DLE;
      *dstlen += 1;
      if (*dstlen == dstsize) return -1;
    }

    *q++ = *p++;
    *dstlen += 1;
    if (*dstlen == dstsize) return -1;
  }

  // Append frame check sequence high byte

  *q++ = crc >> 8;
  *dstlen += 1;
  if (*dstlen == dstsize) return -1;

  if (q[-1] == DLE)
  {
    *q++ = DLE;
    *dstlen += 1;
    if (*dstlen == dstsize) return -1;
  }

  // Append frame check sequence low byte

  *q++ = crc & 0xFF;
  *dstlen += 1;
  if (*dstlen == dstsize) return -1;

  if (q[-1] == DLE)
  {
    *q++ = DLE;
    *dstlen += 1;
    if (*dstlen == dstsize) return -1;
  }

  // Append end of frame delimiter

  if (*dstlen + 2 > dstsize) return -1;
 
  *q++ = DLE;
  *q++ = ETX;
  *dstlen += 2;
  return 0;
}

// Decode a message frame, with DLE byte stuffing and CRC16-CCITT
// frame check sequence.  Return zero if successfully decoded.

int StreamDecodeFrame(void *src, size_t srclen, void *dst, size_t dstsize, size_t *dstlen)
{
  uint8_t *p = src;
  uint8_t *q = dst;
  uint16_t crccalc;
  uint16_t crcsent;

  *dstlen = 0;

  // Verify minimum frame length

  if (srclen < 6) return -1;

  // Verify frame delimiters

  if (p[0] != DLE) return -1;
  if (p[1] != STX) return -1;
  if (p[srclen-2] != DLE) return -1;
  if (p[srclen-1] != ETX) return -1;

  // Skip delimiter bytes at both ends

  p += 2;
  srclen -= 4;

  // Verify DLE stuffing in frame check sequence

  if (p[srclen-1] != DLE)
    srclen--;
  else if ((p[srclen-1] == DLE) && (p[srclen-2] == DLE))
    srclen -= 2;
  else if ((p[srclen-1] == DLE) && (p[srclen-2] != DLE))
    return -1;

  if (p[srclen-1] != DLE)
    srclen--;
  else if ((p[srclen-1] == DLE) && (p[srclen-2] == DLE))
    srclen -= 2;
  else if ((p[srclen-1] == DLE) && (p[srclen-2] != DLE))
    return -1;

  // Copy payload bytes, removing any stuffed DLE's

  while (srclen)
  {
    if (*p == DLE)
    {
      p++;
      if (--srclen == 0) break;
    }

    *q++ = *p++;
    *dstlen += 1;
    srclen--;

    if ((srclen > 0) && (*dstlen == dstsize)) return -1;
  }

  // Calculate expected frame check sequence

  crccalc = crc16(dst, *dstlen);

  // Calculate received frame check sequences

  if (*p == DLE)
    p++;

  crcsent = *p++ << 8;

  if (*p == DLE)
    p++;

  crcsent += *p;

  // Compare expected and received frame check sequences

  if (crccalc == crcsent)
    return 0;
  else
    return -1;
}

#define FAILIF(c, e) if (c) { *framesize = 0; errno = e; return -1; }

// Receive a frame, one byte at a time.  Return -1 on any error,
// including EAGAIN (incomplete frame) and 0 on successful reception
// of a frame.  Invalid frames are silently discarded with errno set
// to EAGAIN.

int StreamReceiveFrame(int fd, void *buf, size_t bufsize, size_t *framesize)
{
  int status;
  uint8_t b;
  uint8_t *bp = buf;

  // Validate parameters

  FAILIF((bufsize < 6), EINVAL);
  FAILIF((*framesize >= bufsize), EINVAL);

  // Read a byte from the stream

  status = read(fd, &b, 1);

  // Special check for O_NONBLOCK and EAGAIN

  if ((status < 0) && (errno == EAGAIN)) return -1;

  // Check for other errors

  FAILIF((status < 0), errno);
  FAILIF((status == 0), EPIPE);

  // Process beginning frame delimiters

  switch (*framesize)
  {
    case 0 :
      FAILIF((b != DLE), EAGAIN);
      bp[*framesize] = b;
      *framesize += 1;
      errno = EAGAIN;
      return -1;

    case 1 :
      FAILIF((b != STX), EAGAIN);
      bp[*framesize] = b;
      *framesize += 1;
      errno = EAGAIN;
      return -1;

    default :
      bp[*framesize] = b;
      *framesize += 1;
      break;
  }

  // Check for complete frame

  if ((*framesize >= 6) && (bp[*framesize-2] == DLE) && (bp[*framesize-1] == ETX))
  {
    unsigned i;
    unsigned dc = 1;

    // Count the DLE's before the ETX

    for (i = 3;; i++)
    {
      if (bp[*framesize-i] == DLE)
        dc++;
      else
        break;
    }

    // Odd number of DLE's implies complete frame
    // Even number of DLE's implies DLE ETX in the payload data

    if (dc & 0x01)
    {
      errno = 0;
      return 0;
    }
  }

  // Check for impending buffer overrun

  FAILIF((*framesize == bufsize), EAGAIN);

  // Frame is still incomplete; try again

  errno = EAGAIN;
  return -1;
}
