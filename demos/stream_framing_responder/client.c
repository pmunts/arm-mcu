#include <assert.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "messages.h"
#include "stream_framing.h"
#include "tcp.h"

void SendCommand(int fd, uint32_t sequence, uint32_t command, uint32_t payload)
{
  COMMANDMSG_t cmd;
  uint8_t cmdbuf[256];
  size_t cmdlen;
  int i;

  cmd.sequence = htonl(sequence);
  cmd.command = htonl(command);
  cmd.payload = htonl(payload);

  printf("Command:  sequence=%d command=%d payload=%d\n",
    ntohl(cmd.sequence), ntohl(cmd.command), ntohl(cmd.payload));
  
  if (StreamEncodeFrame(&cmd, sizeof(cmd), cmdbuf, sizeof(cmdbuf), &cmdlen))
  {
    puts("ERROR: StreamEncodeFrame() failed");
    return;
  }

  printf("Sending  %ld bytes: ", cmdlen);
  for (i = 0; i < cmdlen; i++)
    printf("%02X ", cmdbuf[i]);
  putchar('\n');

  write(fd, cmdbuf, cmdlen);
}

void ReceiveResponse(int fd)
{
  uint8_t buf[256];
  size_t len;
  uint8_t *p;
  int status;
  RESPONSEMSG_t resp;
  size_t respsize;
  int i;

  p = buf;
  len = 0;

  for (;;)
  {
    status = read(fd, p, 1);
    if (status < 1) return;

    p++;
    len++;

    if ((buf[len-2] == DLE) && (buf[len-1] == ETX))
      break;
  }

  printf("Received %ld bytes: ", len);

  for (i = 0; i < len; i++)
    printf("%02X ", buf[i]);
  putchar('\n');

  if (StreamDecodeFrame(buf, len, &resp, sizeof(resp), &respsize))
  {
    puts("ERROR: StreamDecodeFrame() failed");
    return;
  }

  printf("Response: sequence=%d command=%d payload=%d error=%d\n\n",
    ntohl(resp.sequence), ntohl(resp.command), ntohl(resp.payload),
    ntohl(resp.error));
}

int main(int argc, char *argv[])
{
  int fd;

  if (argc != 2)
  {
    printf("\nUsage: %s <servername>\n\n", argv[0]);
    exit(1);
  }

  fd = tcp_call(resolve(argv[1]), 23);
  if (fd < 0)
  {
    fprintf(stderr, "ERROR: tcp_call() failed, %s\n", strerror(errno));
    exit(1);
  }

  SendCommand(fd, 0, NOP, 1234);
  ReceiveResponse(fd);

  SendCommand(fd, 1, LOOPBACK, 2345);
  ReceiveResponse(fd);

  SendCommand(fd, 2, VERSION, 0);
  ReceiveResponse(fd);

  close(fd);
  exit(0);
}
