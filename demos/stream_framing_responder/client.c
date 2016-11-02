#include <assert.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "messages.h"
#include "libstream.h"
#include "libtcp4.h"

void SendCommand(int fd, uint32_t sequence, uint32_t command, uint32_t payload)
{
  COMMANDMSG_t cmd;
  uint8_t cmdbuf[256];
  int32_t cmdlen;
  int32_t error;
  int i;
  int32_t tcount;

  cmd.sequence = htonl(sequence);
  cmd.command = htonl(command);
  cmd.payload = htonl(payload);

  printf("Command:  sequence=%d command=%d payload=%d\n",
    ntohl(cmd.sequence), ntohl(cmd.command), ntohl(cmd.payload));
 
  STREAM_encode_frame(&cmd, sizeof(cmd), cmdbuf, sizeof(cmdbuf), &cmdlen, &error);
 
  if (error)
  {
    fprintf(stderr, "ERROR: STREAM_encode_frame() failed, %s\n", strerror(error));
    return;
  }

  printf("Sending  %d bytes: ", cmdlen);
  for (i = 0; i < cmdlen; i++)
    printf("%02X ", cmdbuf[i]);
  putchar('\n');

  STREAM_send_frame(fd, cmdbuf, cmdlen, &tcount, &error);

  if (error)
  {
    fprintf(stderr, "ERROR: STREAM_send_frame() failed, %s\n", strerror(error));
    return;
  }
}

void ReceiveResponse(int fd)
{
  uint8_t inbuf[256];
  int32_t inlen;
  int32_t error;
  RESPONSEMSG_t resp;
  int32_t respsize;
  int i;

  inlen = 0;

  for (;;)
  {
    STREAM_receive_frame(fd, inbuf, sizeof(inbuf), &inlen, &error);

    if (error == 0) break;
    if (error == EAGAIN) continue;
    fprintf(stderr, "ERROR: STREAM_receive_frame() failed, %s\n", strerror(error));
    return;
  }

  printf("Received %d bytes: ", inlen);

  for (i = 0; i < inlen; i++)
    printf("%02X ", inbuf[i]);
  putchar('\n');

  STREAM_decode_frame(inbuf, inlen, &resp, sizeof(resp), &respsize, &error);

  if (error)
  {
    fprintf(stderr, "ERROR: StreamDecodeFrame() failed, %s\n", strerror(error));
    return;
  }

  printf("Response: sequence=%d command=%d payload=%d error=%d\n\n",
    ntohl(resp.sequence), ntohl(resp.command), ntohl(resp.payload),
    ntohl(resp.error));
}

int main(int argc, char *argv[])
{
  IPV4_ADDR server;
  int32_t fd;
  int32_t error;

  if (argc != 2)
  {
    fprintf(stderr, "\nUsage: %s <servername>\n\n", argv[0]);
    exit(1);
  }

  TCP4_resolve(argv[1], &server, &error);

  if (error != 0)
  {
    fprintf(stderr, "ERROR: TCP4_resolve() failed, %s\n", strerror(error));
    exit(1);
  }

  TCP4_connect(server, 23, &fd, &error);

  if (error != 0)
  {
    fprintf(stderr, "ERROR: TCP4_connect() failed, %s\n", strerror(error));
    exit(1);
  }

  SendCommand(fd, 0, NOP, 1234);
  ReceiveResponse(fd);

  SendCommand(fd, 1, LOOPBACK, 2345);
  ReceiveResponse(fd);

  SendCommand(fd, 2, VERSION, 0);
  ReceiveResponse(fd);

  TCP4_close(fd, &error);

  if (error != 0)
  {
    fprintf(stderr, "ERROR: TCP4_close() failed, %s\n", strerror(error));
    exit(1);
  }

  exit(0);
}
