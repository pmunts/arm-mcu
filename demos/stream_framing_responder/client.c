#include <assert.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "cplusplus.h"
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

  StreamSendFrame(fd, cmdbuf, cmdlen);
}

void ReceiveResponse(int fd)
{
  int status;
  uint8_t inbuf[256];
  size_t inlen;
  RESPONSEMSG_t resp;
  size_t respsize;
  int i;

  inlen = 0;

  for (;;)
  {
    status = StreamReceiveFrame(fd, inbuf, sizeof(inbuf), &inlen);
    if (status == 0) break;
    if ((status < 0) && (errno == EAGAIN)) continue;
    puts("ERROR: StreamReceiveFrame() failed");
    return;
  }

  printf("Received %ld bytes: ", inlen);

  for (i = 0; i < inlen; i++)
    printf("%02X ", inbuf[i]);
  putchar('\n');

  if (StreamDecodeFrame(inbuf, inlen, &resp, sizeof(resp), &respsize))
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
