#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#include <ti/drivers/GPIO.h>
#include <ti/drivers/net/wifi/simplelink.h>

#include <console.h>
#include <status.h>

static uint32_t slStatus = 0;
static SlNetCfgIpV4Args_t ipconfig = { 0 };

//*****************************************************************************
//                       SimpleLink Callback Functions
//*****************************************************************************

void SimpleLinkNetAppRequestMemFreeEventHandler(uint8_t *buffer)
{
}

void SimpleLinkNetAppRequestEventHandler(SlNetAppRequest_t *pNetAppRequest,
                                         SlNetAppResponse_t *pNetAppResponse)
{
}

void SimpleLinkWlanEventHandler(SlWlanEvent_t *pWlanEvent)
{
  switch(pWlanEvent->Id)
  {
    case SL_WLAN_EVENT_CONNECT:
      SET_STATUS_BIT(slStatus, STATUS_BIT_CONNECTION);
      break;

    case SL_WLAN_EVENT_DISCONNECT:
      CLR_STATUS_BIT(slStatus, STATUS_BIT_CONNECTION);
      CLR_STATUS_BIT(slStatus, STATUS_BIT_IP_ACQUIRED);
      break;

    default:
      printf("[WLAN EVENT] Unexpected event [0x%x]\n\r", pWlanEvent->Id);
      break;
  }
}

void SimpleLinkFatalErrorEventHandler(SlDeviceFatal_t *slFatalErrorEvent)
{
    switch(slFatalErrorEvent->Id)
    {
    case SL_DEVICE_EVENT_FATAL_DEVICE_ABORT:
    {
        printf(
            "[ERROR] - FATAL ERROR: Abort NWP event detected: AbortType=%d, AbortData=0x%x\n\r",
            slFatalErrorEvent->Data.DeviceAssert.Code,
            slFatalErrorEvent->Data.DeviceAssert.Value);
    }
    break;

    case SL_DEVICE_EVENT_FATAL_DRIVER_ABORT:
    {
        printf("[ERROR] - FATAL ERROR: Driver Abort detected. \n\r");
    }
    break;

    case SL_DEVICE_EVENT_FATAL_NO_CMD_ACK:
    {
        printf(
            "[ERROR] - FATAL ERROR: No Cmd Ack detected [cmd opcode = 0x%x] \n\r",
            slFatalErrorEvent->Data.NoCmdAck.Code);
    }
    break;

    case SL_DEVICE_EVENT_FATAL_SYNC_LOSS:
    {
        printf("[ERROR] - FATAL ERROR: Sync loss detected n\r");
    }
    break;

    case SL_DEVICE_EVENT_FATAL_CMD_TIMEOUT:
    {
        printf(
            "[ERROR] - FATAL ERROR: Async event timeout detected [event opcode =0x%x]  \n\r",
            slFatalErrorEvent->Data.CmdTimeout.Code);
    }
    break;

    default:
        printf("[ERROR] - FATAL ERROR: Unspecified error detected \n\r");
        break;
    }
}

void SimpleLinkNetAppEventHandler(SlNetAppEvent_t *pNetAppEvent)
{
  switch(pNetAppEvent->Id)
  {
    case SL_NETAPP_EVENT_IPV4_ACQUIRED:
      SET_STATUS_BIT(slStatus, STATUS_BIT_IP_ACQUIRED);
      break;

    default:
      printf("[NETAPP EVENT] Unexpected event [0x%x] \n\r", pNetAppEvent->Id);
      break;
  }
}

void SimpleLinkHttpServerEventHandler(SlNetAppHttpServerEvent_t *pHttpEvent,
  SlNetAppHttpServerResponse_t * pHttpResponse)
{
}

void SimpleLinkGeneralEventHandler(SlDeviceEvent_t *pDevEvent)
{
  printf("[GENERAL EVENT] - ID=[%d] Sender=[%d]\n\n",
    pDevEvent->Data.Error.Code, pDevEvent->Data.Error.Source);
}

void SimpleLinkSockEventHandler(SlSockEvent_t *pSock)
{
}

void SimpleLinkSocketTriggerEventHandler(SlSockTriggerEvent_t *pSlTriggerEvent)
{
}

int32_t wlanConnect(char *ssid, char *pass, uint8_t secmode)
{
  SlWlanSecParams_t secParams = {0};

  secParams.Key = (signed char *) pass;
  secParams.KeyLen = strlen(pass);
  secParams.Type = secmode;

  // Connect to specified SSID

  int32_t status = sl_WlanConnect((signed char *) ssid, strlen(ssid),
    NULL, &secParams, NULL);

  if (status)
  {
    printf("ERROR: sl_WlanConnect() failed, error=%d\r\n", status);
    return status;
  }

  // Wait until connected

  while (!IS_CONNECTED(slStatus) || !IS_IP_ACQUIRED(slStatus))
  {
    sl_Task(NULL);
  }

  // Turn on LED to indicate we have associated with the access point
  GPIO_write(LED1, true);

  // Fetch IP address configuration
  uint16_t len = sizeof(ipconfig);
  uint16_t opt = 0;

  status = sl_NetCfgGet(SL_NETCFG_IPV4_STA_ADDR_MODE, &opt, &len, (_u8 *) &ipconfig);

  if (status)
  {
    printf("ERROR: sl_NetCfgGet() failed, error=%d\r\n", status);
    return status;
  }

  return 0;
}

void mainThread(void *pvParameters)
{
  int32_t status;
  char ssid[32] = { 0 };
  char pass[32] = { 0 };

  // Initialize hardware
  Board_initGPIO();
  Board_initSPI();
  InitTerm();

  // Display startup message
  printf("\033[H\033[2JSimpleLink CC3120 WiFi Associate Test (" __DATE__ " " __TIME__ ")\r\n\n");

  GPIO_write(LED1, false);

  // Get SSID to connect to
  puts("SSID?     ");
  gets(ssid);
  puts("\r\n");

  // Get WPA2 password
  puts("Password? ");
  gets(pass);
  puts("\r\n\n");

  // Start WiFi subsystem
  status = sl_Start(NULL, NULL, NULL);

  if (status)
  {
    printf("ERROR: sl_Start() failed, error=%d\r\n", status);
    abort();
  }

  // Connect to access point
  status = wlanConnect(ssid, pass, SL_WLAN_SEC_TYPE_WPA_WPA2);

  if (status)
  {
    printf("ERROR: wlanConnect() failed, error=%d\r\n", status);
    abort();
  }

  // Display IP address configuration
  printf("Address:  %d.%d.%d.%d\r\n"
         "Netmask:  %d.%d.%d.%d\r\n"
         "Gateway:  %d.%d.%d.%d\r\n"
         "DNS:      %d.%d.%d.%d\r\n\n",
    SL_IPV4_BYTE(ipconfig.Ip,3),
    SL_IPV4_BYTE(ipconfig.Ip,2),
    SL_IPV4_BYTE(ipconfig.Ip,1),
    SL_IPV4_BYTE(ipconfig.Ip,0),
    SL_IPV4_BYTE(ipconfig.IpMask,3),
    SL_IPV4_BYTE(ipconfig.IpMask,2),
    SL_IPV4_BYTE(ipconfig.IpMask,1),
    SL_IPV4_BYTE(ipconfig.IpMask,0),
    SL_IPV4_BYTE(ipconfig.IpGateway,3),
    SL_IPV4_BYTE(ipconfig.IpGateway,2),
    SL_IPV4_BYTE(ipconfig.IpGateway,1),
    SL_IPV4_BYTE(ipconfig.IpGateway,0),
    SL_IPV4_BYTE(ipconfig.IpDnsServer,3),
    SL_IPV4_BYTE(ipconfig.IpDnsServer,2),
    SL_IPV4_BYTE(ipconfig.IpDnsServer,1),
    SL_IPV4_BYTE(ipconfig.IpDnsServer,0));

  // Main event loop
  while(1)
  {
    sl_Task(NULL);
  }
}
