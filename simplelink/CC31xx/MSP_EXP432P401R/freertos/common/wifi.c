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
#include <wifi.h>

/*****************************************************************************/

// Type declarations

typedef enum
{
  SL_STARTED,
  SL_CONNECTED,
  SL_DISCONNECTED,
  SL_IPV4CONFIGURED,
  SL_IPV4UNCONFIGURED,
  CMD_START,
  CMD_STOP,
  CMD_ASSOCIATE,
  MAX_EVENT_CODES
} event_code_t;

typedef struct
{
  uint8_t bssid[6];
  char ssid[32];
} payload_SL_CONNECTED_t;

typedef struct
{
  uint8_t bssid[6];
  char ssid[32];
} payload_SL_DISCONNECTED_t;

/*****************************************************************************/

// Global variables

static QueueHandle_t mqueue = NULL;
static volatile bool connected = false;
static char ssid[32];
static char password[32];
static uint8_t bssid[6] = { 0 };

/*****************************************************************************/

// Public API functions

int WiFi_Register(char *newssid, char *newpass, uint8_t *newbssid)
{
  // Wait for WiFi task to finish initializing
  while (mqueue == NULL) vTaskDelay(pdMS_TO_TICKS(100));

  strncpy(ssid, newssid, sizeof(ssid) - 1);
  strncpy(password, newpass, sizeof(password) - 1);

  if (newbssid == NULL)
    memset(bssid, 0, sizeof(bssid));
  else
    memcpy(bssid, newbssid, sizeof(bssid));

  return 0;
}

int WiFi_Start(void)
{
  // Wait for WiFi task to finish initializing
  while (mqueue == NULL) vTaskDelay(pdMS_TO_TICKS(100));

  return event_enqueue(mqueue, CMD_START, NULL, 0, 0);
}

int WiFi_Stop(void)
{
  // Wait for WiFi task to finish initializing
  while (mqueue == NULL) vTaskDelay(pdMS_TO_TICKS(100));

  return event_enqueue(mqueue, CMD_STOP, NULL, 0, 0);
}

bool WiFi_Associated(void)
{
  // Wait for WiFi task to finish initializing
  while (mqueue == NULL) vTaskDelay(pdMS_TO_TICKS(100));

  return connected;
}

/*****************************************************************************/

// Callbacks required by SimpleLink WiFi

void SimpleLinkStartCallback(uint32_t Status, SlDeviceInitInfo_t *DeviceInitInfo)
{
  // Enqueue event message

  event_enqueue(mqueue, SL_STARTED, NULL, 0, 0);
}

void SimpleLinkWlanEventHandler(SlWlanEvent_t *pWlanEvent)
{
  switch (pWlanEvent->Id)
  {
    case SL_WLAN_EVENT_CONNECT:
    {
      payload_SL_CONNECTED_t payload;

      // Build payload structure

      memset(&payload, 0, sizeof(payload));
      memcpy(payload.bssid, pWlanEvent->Data.Connect.Bssid, 6);
      memcpy(payload.ssid, pWlanEvent->Data.Connect.SsidName,
        pWlanEvent->Data.Connect.SsidLen);

      // Enqueue event message

      event_enqueue(mqueue, SL_CONNECTED, &payload, sizeof(payload), 0);
    }
    break;

    case SL_WLAN_EVENT_DISCONNECT:
    {
      payload_SL_DISCONNECTED_t payload;

      // Build payload structure

      memset(&payload, 0, sizeof(payload));
      memcpy(payload.bssid, pWlanEvent->Data.Disconnect.Bssid, 6);
      memcpy(payload.ssid, pWlanEvent->Data.Disconnect.SsidName,
        pWlanEvent->Data.Disconnect.SsidLen);

      // Enqueue event message

      event_enqueue(mqueue, SL_DISCONNECTED, &payload, sizeof(payload), 0);
    }
    break;

    default:
    {
#ifdef DEBUG
      char outbuf[256];

      snprintf(outbuf, sizeof(outbuf), "DEBUG: Line %d: Unexpected WLAN Event: "
        " %ld\r\n", __LINE__ - 5, pWlanEvent->Id);
      puts(outbuf);
#endif
    }
    break;
  }
}

void SimpleLinkNetAppEventHandler(SlNetAppEvent_t *pNetAppEvent)
{
  switch (pNetAppEvent->Id)
  {
    case SL_NETAPP_EVENT_IPV4_ACQUIRED:
    {
      // Enqueue event message

      event_enqueue(mqueue, SL_IPV4CONFIGURED, NULL, 0, 0);
    }
    break;

    case SL_NETAPP_EVENT_IPV4_LOST:
    {
      // Enqueue event message

      event_enqueue(mqueue, SL_IPV4UNCONFIGURED, NULL, 0, 0);
    }
    break;

    default:
    {
#ifdef DEBUG
      char outbuf[256];

      snprintf(outbuf, sizeof(outbuf), "DEBUG: Line %d: Unexpected Net App Event: "
        "%ld\r\n", __LINE__ - 5, pNetAppEvent->Id);
      puts(outbuf);
#endif
    }
    break;
  }
}

void SimpleLinkHttpServerEventHandler(SlNetAppHttpServerEvent_t *pHttpEvent,
  SlNetAppHttpServerResponse_t *pHttpResponse)
{
}

void SimpleLinkGeneralEventHandler(SlDeviceEvent_t *pDevEvent)
{
  switch (pDevEvent->Id)
  {
    default:
    {
#ifdef DEBUG
      char outbuf[256];

      snprintf(outbuf, sizeof(outbuf), "DEBUG: Line %d: Unexpected Device Event: "
        "%ld\r\n", __LINE__ - 5, pDevEvent->Id);
      puts(outbuf);
#endif
    }
    break;
  }
}

void SimpleLinkSockEventHandler(SlSockEvent_t *pSock)
{
  switch (pSock->Event)
  {
    default:
    {
#ifdef DEBUG
      char outbuf[256];

      snprintf(outbuf, sizeof(outbuf), "DEBUG: Line %d: Unexpected Socket Event: "
        "%ld\r\n", __LINE__ - 5, pSock->Event);
      puts(outbuf);
#endif
    }
    break;
  }
}

void SimpleLinkFatalErrorEventHandler(SlDeviceFatal_t *pFatalErrorEvent)
{
  switch (pFatalErrorEvent->Id)
  {
    default:
    {
#ifdef DEBUG
      char outbuf[256];

      snprintf(outbuf, sizeof(outbuf), "DEBUG: Line %d: Unexpected Error Event: "
        "%ld\r\n", __LINE__ - 5, pFatalErrorEvent->Id);
      puts(outbuf);
#endif
    }
    break;
  }
}

void SimpleLinkNetAppRequestEventHandler(SlNetAppRequest_t *pNetAppRequest,
  SlNetAppResponse_t *pNetAppResponse)
{
}

void SimpleLinkNetAppRequestMemFreeEventHandler(uint8_t *buffer)
{
}

/*****************************************************************************/

// Event handlers

static int Handle_SL_STARTED(const event_msg_t * const event)
{
#ifdef DEBUG
  puts("EVENT:     WIFI STARTED\r\n");
#endif

  // Make LED2 red

  GPIO_write(Board_GPIO_LED0, true);
  GPIO_write(Board_GPIO_LED1, false);

  // Now associate with the specified access point

  return event_enqueue(mqueue, CMD_ASSOCIATE, NULL, 0, 0);
}

static int Handle_SL_CONNECTED(const event_msg_t * const event)
{
#ifdef DEBUG
  payload_SL_CONNECTED_t *p = (payload_SL_CONNECTED_t *) event->payload;

  puts("EVENT:     WIFI CONNECTED\r\n");

  printf(" SSID:     %s\r\n", p->ssid);

  printf(" BSSID:    %02X:%02X:%02X:%02X:%02X:%02X\r\n",
    p->bssid[0], p->bssid[1], p->bssid[2],
    p->bssid[3], p->bssid[4], p->bssid[5]);
#endif

  // Make LED2 yellow

  GPIO_write(Board_GPIO_LED0, true);
  GPIO_write(Board_GPIO_LED1, true);

  return 0;
}

static int Handle_SL_DISCONNECTED(const event_msg_t * const event)
{
#ifdef DEBUG
  payload_SL_DISCONNECTED_t *p = (payload_SL_DISCONNECTED_t *) event->payload;

  puts("EVENT:     WIFI DISCONNECTED\r\n");

  printf(" SSID:     %s\r\n", p->ssid);

  printf(" BSSID:    %02X:%02X:%02X:%02X:%02X:%02X\r\n",
    p->bssid[0], p->bssid[1], p->bssid[2], p->bssid[3], p->bssid[4], p->bssid[5]);
#endif

  // Make LED2 red

  GPIO_write(Board_GPIO_LED0, true);
  GPIO_write(Board_GPIO_LED1, false);

  connected = false;

  // Try to reconnect to the specified access point

  return event_enqueue(mqueue, CMD_ASSOCIATE, NULL, 0, 0);
}

static int Handle_SL_IPV4CONFIGURED(const event_msg_t * const event)
{
  GPIO_write(Board_GPIO_LED0, false);
  GPIO_write(Board_GPIO_LED1, true);

#ifdef DEBUG
  puts("EVENT:     IPV4 CONFIGURED\r\n");

  // Fetch IP address configuration

  SlNetCfgIpV4Args_t ipconfig = { 0 };
  uint16_t len = sizeof(ipconfig);
  uint16_t opt = 0;

  int16_t status = sl_NetCfgGet(SL_NETCFG_IPV4_STA_ADDR_MODE, &opt, &len, (_u8 *) &ipconfig);

  if (status)
  {
    printf("ERROR: sl_NetCfgGet() failed, error=%d\r\n", status);
    return status;
  }

  printf(" Address:  %ld.%ld.%ld.%ld\r\n",
    SL_IPV4_BYTE(ipconfig.Ip, 3),
    SL_IPV4_BYTE(ipconfig.Ip, 2),
    SL_IPV4_BYTE(ipconfig.Ip, 1),
    SL_IPV4_BYTE(ipconfig.Ip, 0));

  printf(" Netmask:  %ld.%ld.%ld.%ld\r\n",
    SL_IPV4_BYTE(ipconfig.IpMask, 3),
    SL_IPV4_BYTE(ipconfig.IpMask, 2),
    SL_IPV4_BYTE(ipconfig.IpMask, 1),
    SL_IPV4_BYTE(ipconfig.IpMask, 0));

  printf(" Gateway:  %ld.%ld.%ld.%ld\r\n",
    SL_IPV4_BYTE(ipconfig.IpGateway, 3),
    SL_IPV4_BYTE(ipconfig.IpGateway, 2),
    SL_IPV4_BYTE(ipconfig.IpGateway, 1),
    SL_IPV4_BYTE(ipconfig.IpGateway, 0));

  printf(" DNS:      %ld.%ld.%ld.%ld\r\n",
    SL_IPV4_BYTE(ipconfig.IpDnsServer, 3),
    SL_IPV4_BYTE(ipconfig.IpDnsServer, 2),
    SL_IPV4_BYTE(ipconfig.IpDnsServer, 1),
    SL_IPV4_BYTE(ipconfig.IpDnsServer, 0));
#endif

  // Make LED2 green

  GPIO_write(Board_GPIO_LED0, false);
  GPIO_write(Board_GPIO_LED1, true);

  connected = true;

  return 0;
}

static int Handle_SL_IPV4UNCONFIGURED(const event_msg_t * const event)
{
#ifdef DEBUG
  puts("EVENT:     IPV4 UNCONFIGURED\r\n");
#endif

  // Make LED2 yellow

  GPIO_write(Board_GPIO_LED0, true);
  GPIO_write(Board_GPIO_LED1, true);

  connected = false;

  return 0;
}

static int Handle_CMD_START(const event_msg_t * const event)
{
#ifdef DEBUG
  puts("COMMAND:   WIFI START\r\n");
#endif

  int16_t status = sl_Start(NULL, NULL, SimpleLinkStartCallback);

  if (status < 0)
  {
    printf("FATAL ERROR: sl_Start() failed, error=%d\r\n", status);
    abort();
  }

  return 0;
}

static int Handle_CMD_STOP(const event_msg_t * const event)
{
#ifdef DEBUG
  puts("COMMAND:   WIFI STOP\r\n");
#endif

  int16_t status = sl_Stop(0);

  if (status < 0)
  {
    printf("FATAL ERROR: sl_Stop() failed, error=%d\r\n", status);
    abort();
  }

  // Turn LED2 off

  GPIO_write(Board_GPIO_LED0, false);
  GPIO_write(Board_GPIO_LED1, false);

  connected = false;

  return 0;
}

static int Handle_CMD_ASSOCIATE(const event_msg_t * const event)
{
#ifdef DEBUG
  puts("COMMAND:   WIFI ASSOCIATE\r\n");

  printf(" SSID:     %s\r\n", ssid);

  printf(" BSSID:    %02X:%02X:%02X:%02X:%02X:%02X\r\n",
    bssid[0], bssid[1], bssid[2], bssid[3], bssid[4], bssid[5]);
#endif

  // Build credentials structure

  SlWlanSecParams_t secParams;
  memset(&secParams, 0, sizeof(secParams));
  secParams.Key = (signed char *) password;
  secParams.KeyLen = strlen(password);
  secParams.Type = SL_WLAN_SEC_TYPE_WPA_WPA2;

  // Try to connect to the specified access point

  int16_t status = sl_WlanConnect((signed char *) ssid, strlen(ssid), bssid,
    &secParams, NULL);

  if (status)
  {
#ifdef DEBUG
    printf("ERROR: sl_WlanConnect() failed, error=%d\r\n", status);
#endif
  }

  return status;
}

// Event handler table

static const event_handler_t EventHandlers[MAX_EVENT_CODES] =
{
  Handle_SL_STARTED,
  Handle_SL_CONNECTED,
  Handle_SL_DISCONNECTED,
  Handle_SL_IPV4CONFIGURED,
  Handle_SL_IPV4UNCONFIGURED,
  Handle_CMD_START,
  Handle_CMD_STOP,
  Handle_CMD_ASSOCIATE,
};

/*****************************************************************************/

// WiFi task function

__attribute__((noreturn)) void WiFi_Task(void *arg0)
{
  static event_msg_t event;

  puts("SimpleLink CC31xx WiFi Task\r\n");

  // Initialize hardware subsystems

  GPIO_init();
  SPI_init();

  // Turn off LEDs

  GPIO_write(Board_GPIO_LED0, false);
  GPIO_write(Board_GPIO_LED1, false);
  GPIO_write(Board_GPIO_LED2, false);
  GPIO_write(Board_GPIO_LED3, false);

  // Create event message queue

  mqueue = xQueueCreate(10, sizeof(event_msg_t));

  if (mqueue == NULL)
  {
    puts("FATAL ERROR: xQueueCreate() failed\r\n");
    abort();
  }

  // Main event loop

  for (;;)
  {
    if (xQueueReceive(mqueue, &event, pdMS_TO_TICKS(1000)) == pdPASS)
      event_dispatch(EventHandlers, MAX_EVENT_CODES, &event);
    else
      GPIO_toggle(Board_GPIO_LED3);
  }
}
