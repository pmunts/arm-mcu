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

/* POSIX header files */
#include <pthread.h>

/* FreeRTOS header files */
#include <FreeRTOS.h>
#include <task.h>

/* Driver library header files */
#include <ti/drivers/GPIO.h>

/* Board header files */
#include <Board.h>
#include <console.h>

/* Implemented in the SimpleLink library */
extern void *sl_Task(void *arg0);

/* Implemented in application.c */
extern void *Main_Task(void *arg0);

int main(void)
{
  /* Call board init functions */
  Board_initGeneral();
  SPI_init();
  GPIO_init();
  InitTerm();

  /* Switch off all LEDs */
  GPIO_write(Board_GPIO_LED0, false);
  GPIO_write(Board_GPIO_LED1, false);
  GPIO_write(Board_GPIO_LED2, false);
  GPIO_write(Board_GPIO_LED3, false);

  /* Create the Simplelink task */
  pthread_t thread_simplelink;
  pthread_attr_t pAttrs_simplelink;
  struct sched_param priParam_simplelink;

  pthread_attr_init(&pAttrs_simplelink);
  priParam_simplelink.sched_priority = 9;
  pthread_attr_setschedparam(&pAttrs_simplelink, &priParam_simplelink);
  pthread_attr_setstacksize(&pAttrs_simplelink, 2048);
  pthread_attr_setdetachstate(&pAttrs_simplelink, PTHREAD_CREATE_DETACHED);

  if (pthread_create(&thread_simplelink, &pAttrs_simplelink, sl_Task, NULL))
  {
    puts("FATAL ERROR: Unable to create SimpleLink task\r\n");
    abort();
  }

  /* Create the main task */
  pthread_t thread_main;
  pthread_attr_t pAttrs_main;
  struct sched_param priParam_main;

  pthread_attr_init(&pAttrs_main);
  priParam_main.sched_priority = 1;
  pthread_attr_setschedparam(&pAttrs_main, &priParam_main);
  pthread_attr_setstacksize(&pAttrs_main, 4096);
  pthread_attr_setdetachstate(&pAttrs_main, PTHREAD_CREATE_DETACHED);

  if(pthread_create(&thread_main, &pAttrs_main, Main_Task, NULL))
  {
    puts("FATAL ERROR: Unable to create main task\r\n");
    abort();
  }

  /* Start the FreeRTOS scheduler */
  vTaskStartScheduler();
}

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
