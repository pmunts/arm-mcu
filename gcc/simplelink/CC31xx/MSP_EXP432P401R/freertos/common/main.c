/*
 * Copyright (c) 2016, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdint.h>
#include <stdlib.h>

/* FreeRTOS header files */
#include <FreeRTOS.h>
#include <task.h>

/* Board header files */
#include <Board.h>
#include <console.h>
#include <tasklist.h>

#define WEAK __attribute__((weak))

/* Implemented in the SimpleLink library */
extern void sl_Task(void *arg0);

/* Implemented in wifi.c */
extern void WiFi_Task(void *arg0);

/* Framework base tasks */
static const tasklist_item_t BaseTasks[] =
{
  { sl_Task,   "SimpleLink Task", 2048, 9 },
  { WiFi_Task, "WiFi Task",       4096, 1 },
  { NULL }
};

/* User application tasks (placeholder) */
WEAK const tasklist_item_t UserTasks[] =
{
  { NULL }
};

/*****************************************************************************/

// Callbacks required by FreeRTOS -- These are defined as weak so they can
// be overridden in user code, if necessary.

WEAK void vApplicationMallocFailedHook()
{
}

WEAK void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
}

WEAK void vApplicationTickHook(void)
{
}

WEAK void vPreSleepProcessing(uint32_t ulExpectedIdleTime)
{
}

WEAK void vApplicationIdleHook(void)
{
}

/*****************************************************************************/

int main(void)
{
  // Call board init functions

  Board_initGeneral();
  InitTerm();

  // Display startup banner

  puts("\033[H\033[2JSimpleLink CC31xx WiFi Framework using FreeRTOS ("
    __DATE__ " " __TIME__ ")\r\n");

  // Create framework base tasks

  CreateTasks(BaseTasks);

  // Create user application tasks

  CreateTasks(UserTasks);

  // Start the FreeRTOS scheduler

  vTaskStartScheduler();
}

/*****************************************************************************/

#if defined (__GNUC__)
void * _sbrk(uint32_t delta)
{
  extern char _end;     /* Defined by the linker */
  extern char __HeapLimit;
  static char *heap_end;
  static char *heap_limit;
  char *prev_heap_end;

  if(heap_end == 0)
  {
    heap_end = &_end;
    heap_limit = &__HeapLimit;
  }

  prev_heap_end = heap_end;

  if(prev_heap_end + delta > heap_limit)
  {
    return((void *) -1L);
  }

  heap_end += delta;

  return((void *) prev_heap_end);
}
#endif
