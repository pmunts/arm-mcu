#include <pthread.h>
#include <stdlib.h>

#include <console.h>
#include <tasklist.h>

// Start a list of tasks

void CreateTasks(const tasklist_item_t list[])
{
  tasklist_item_t *item = (tasklist_item_t *) list;

  while (item->func != NULL)
  {
    pthread_attr_t pAttrs;
    struct sched_param priParam;
    priParam.sched_priority = 1;

    pthread_attr_init(&pAttrs);
    pthread_attr_setdetachstate(&pAttrs, PTHREAD_CREATE_DETACHED);
    pthread_attr_setschedparam(&pAttrs, &priParam);
    pthread_attr_setstacksize(&pAttrs, item->stacksize);
    pthread_t thread;

    if (pthread_create(&thread, &pAttrs, (void *(*)(void *))item->func, NULL))
    {
      puts("FATAL ERROR: Unable to create ");
      puts(item->name);
      puts("\r\n");
      abort();
    }

    item++;
  }
}
