// STM32F411 FreeRTOS Stream Framing Responder Program

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

#ifndef FREERTOS
#error You must define FREERTOS to compile this FreeRTOS application (WITH_FREERTOS=yes)
#endif

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <inet.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cpu.h>

#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

#include "stream_framing.h"
#include "messages.h"

#define FIRMWARE_VERSION	11277

#ifdef NUCLEO_F103RB
#define CONTROLPORT		"com3:115200,n8,1"
#endif

#ifdef NUCLEO_F411RE
#define CONTROLPORT		"com6:115200,n8,1"
#endif

//***************************************************************************

void ExecuteCommand(COMMANDMSG_t *cmd, RESPONSEMSG_t *resp)
{
  resp->sequence = cmd->sequence;
  resp->command = cmd->command;
  resp->payload = 0;
  resp->error = 0;

  // Execute individual commands

  switch(cmd->command)
  {
    case NOP :
      break;

    case LOOPBACK :
      resp->payload = cmd->payload;
      break;

    case VERSION :
      resp->payload = FIRMWARE_VERSION;
      break;

    default :
      resp->error = EINVAL;
      break;
  }
}

//***************************************************************************

// Inter-task message queues

xQueueHandle CommandQueue;
xQueueHandle ResponseQueue;

// Statistics counters

volatile unsigned dropped_commands = 0;
volatile unsigned dropped_responses = 0;
volatile unsigned receive_errors = 0;
volatile unsigned transmit_errors = 0;

// The Receiver task will have exclusive control over the
// control UART receiver.  It will receive incoming bytes,
// assemble them into frames, decode them, and then push
// commands onto the Command Queue.

void ReceiverTask(void *parameters)
{
  int fd = (int) parameters;
  int status;
  uint8_t inbuf[256];
  size_t inlen;
  COMMANDMSG_t cmd;
  size_t cmdlen;

  // Receiver task event loop

  for (;;)
  {
    // Receive an incoming command message frame

    inlen = 0;

    for (;;)
    {
      status = StreamReceiveFrame(fd, inbuf, sizeof(inbuf), &inlen);
      if (status == 0) break;
      if ((status < 0) && (errno != EAGAIN)) receive_errors++;
    }

    // Decode the command message frame

    if (StreamDecodeFrame(inbuf, inlen, &cmd, sizeof(cmd), &cmdlen))
    {
      receive_errors++;
      continue;
    }

    // Check for wrong frame size

    if (cmdlen != sizeof(cmd))
    {
      receive_errors++;
      continue;
    }

    // Convert command message from network byte order

    cmd.sequence = ntohl(cmd.sequence);
    cmd.command = ntohl(cmd.command);
    cmd.payload = ntohl(cmd.payload);

    // Enqueue the command message

    if (xQueueSend(CommandQueue, &cmd, 0) == errQUEUE_FULL)
      dropped_commands++;
  }
}

// The Transmitter task will have exclusive control over the
// control UART transmitter.  It will pop responses from the
// Response Queue, pack them into frames, and transmit them.

void TransmitterTask(void *parameters)
{
  int fd = (int) parameters;
  RESPONSEMSG_t resp;
  uint8_t outbuf[2*sizeof(resp)+8];
  size_t outlen;

  for (;;)
  {
    // Dequeue a response message

    if (xQueueReceive(ResponseQueue, &resp, portMAX_DELAY) != pdPASS)
    {
      taskYIELD();
      continue;
    }

    // Convert the response message to network byte order

    resp.sequence = htonl(resp.sequence);
    resp.command = htonl(resp.command);
    resp.payload = htonl(resp.payload);
    resp.error = htonl(resp.error);

    // Encode the response message

    if (StreamEncodeFrame(&resp, sizeof(resp), outbuf, sizeof(outbuf), &outlen))
    {
      transmit_errors++;
      continue;
    }

    // Transmit the response message

    if (StreamSendFrame(fd, outbuf, outlen) < 0)
      transmit_errors++;
  }
}

// The Executor task will pop commands from the Command Queue,
// execute them, and push responses onto the Response Queue.

void ExecutorTask(void *parameters)
{
  COMMANDMSG_t cmd;
  RESPONSEMSG_t resp;

  for (;;)
  {
    if (xQueueReceive(CommandQueue, &cmd, portMAX_DELAY) != pdPASS)
    {
      taskYIELD();
      continue;
    }

    ExecuteCommand(&cmd, &resp);

    if (xQueueSend(ResponseQueue, &resp, 0) != pdPASS)
      dropped_responses++;
  };
}

void StatisticsTask(void *parameters)
{
  for (;;)
  {
    vTaskDelay(30000/portTICK_RATE_MS);
    printf("Dropped commands: %d Dropped responses: %d\n",
      dropped_commands, dropped_responses);
    printf("Receive errors: %d Transmit errors: %d\n",
      receive_errors, transmit_errors);
    fflush(stdout);
  }
}

void vApplicationStackOverflowHook(xTaskHandle *pxTask, signed char *pcTaskName)
{
  fprintf(stderr, "ERROR: vApplicationStackOverflowHook(): Task \"%s\" overflowed its stack\n", pcTaskName);
  assert(false);
}

//***************************************************************************

int main(void)
{
  int fd;
  xTaskHandle tasks[4];

  cpu_init(DEFAULT_CPU_FREQ);
  serial_stdio(CONSOLE_PORT);

  // Display startup banner and version information

  printf("\033[H\033[2J%s FreeRTOS Stream Framing Responder (" __DATE__ " " __TIME__ ")\n\n", MCUFAMILYNAME);
  printf("CPU Freq:%u Hz  Compiler:%s %s %s  FreeRTOS:%s\n\n", (unsigned int) SystemCoreClock,
    __COMPILER__, __VERSION__, __ABI__, tskKERNEL_VERSION_NUMBER);
  fflush(stdout);

  // Initialize the serial port connected to the controlling device

  if (serial_register(CONTROLPORT) < 0)
  {
    fprintf(stderr, "ERROR: serial_register() for control port failed, %s\n", strerror(errno));
    exit(1);
  }

  fd = open(CONTROLPORT, O_RDWR|O_BINARY);
  if (fd < 0)
  {
    fprintf(stderr, "ERROR: open() for control port failed, %s\n", strerror(errno));
    exit(1);
  }

  // Create message queues

  CommandQueue = xQueueCreate(10, sizeof(COMMANDMSG_t));
  if (CommandQueue == NULL)
  {
    fprintf(stderr, "ERROR: Cannot create Command Queue\n");
    exit(1);
  }

  ResponseQueue = xQueueCreate(10, sizeof(RESPONSEMSG_t));
  if (ResponseQueue == NULL)
  {
    fprintf(stderr, "ERROR: Cannot create Response Queue\n");
    exit(1);
  }

  // Create tasks

  if (xTaskCreate(ReceiverTask, "Receiver", 512, (void *) fd, 1, &tasks[0]) != pdPASS)
  {
    fprintf(stderr, "ERROR: xTaskCreate() for Receiver task failed!\n");
    exit(1);
  }

  if (xTaskCreate(TransmitterTask, "Transmitter", 512, (void *) fd, 1, &tasks[1]) != pdPASS)
  {
    fprintf(stderr, "ERROR: xTaskCreate() for Transmitter task failed!\n");
    exit(1);
  }

  if (xTaskCreate(ExecutorTask, "Executor", 512, NULL, 1, &tasks[2]) != pdPASS)
  {
    fprintf(stderr, "ERROR: xTaskCreate() for Executor task failed!\n");
    exit(1);
  }

  if (xTaskCreate(StatisticsTask, "Statistics", 512, NULL, 1, &tasks[2]) != pdPASS)
  {
    fprintf(stderr, "ERROR: xTaskCreate() for Statistics task failed!\n");
    exit(1);
  }

  // Start FreeRTOS scheduler, enter multitasking mode

  vTaskStartScheduler();
  fprintf(stderr, "ERROR: vTaskStartScheduler returned!\n");
  exit(1);
}
