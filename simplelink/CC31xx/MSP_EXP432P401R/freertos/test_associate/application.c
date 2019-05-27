#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <FreeRTOS.h>
#include <queue.h>
#include <task.h>

#include <ti/drivers/net/wifi/simplelink.h>

#include <Board.h>
#include <console.h>
#include <events.h>
#include <tasklist.h>
#include <wifi.h>

// Override TEST_SSID and TEST_PASS with useful values with something like:
//
// export CFLAGS="-DTEST_SSID='\"MySSID\"' -DTEST_PASS='\"MyPassword\"'"
//
// before running make.

#ifndef TEST_SSID
#define TEST_SSID	"undefined"
#endif

#ifndef TEST_PASS
#define TEST_PASS	"undefined"
#endif

/*****************************************************************************/

void Application_Task(void *arg0)
{
  WiFi_Register(TEST_SSID, TEST_PASS, NULL);
  WiFi_Start();
}

/*****************************************************************************/

const tasklist_item_t UserTasks[] =
{
  { Application_Task, "Application Task", 2048, 1 },
  { NULL }
};
