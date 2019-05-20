#ifndef _TASKLIST_H
#define _TASKLIST_H

#include <FreeRTOS.h>
#include <task.h>

typedef struct
{
  TaskFunction_t func;
  char *name;
  unsigned stacksize;
  unsigned priority;
} tasklist_item_t;

extern void CreateTasks(const tasklist_item_t list[]);

#endif
