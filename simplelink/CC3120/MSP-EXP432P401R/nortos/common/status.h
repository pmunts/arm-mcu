#ifndef __STATUS_H__
#define __STATUS_H__

typedef enum
{
  STATUS_BIT_NWP_INIT,
  STATUS_BIT_CONNECTION,
  STATUS_BIT_IP_LEASED,
  STATUS_BIT_IP_ACQUIRED,
  STATUS_BIT_SMARTCONFIG_START,
  STATUS_BIT_P2P_DEV_FOUND,
  STATUS_BIT_P2P_REQ_RECEIVED,
  STATUS_BIT_CONNECTION_FAILED,
  STATUS_BIT_PING_DONE,
  STATUS_BIT_IPV6L_ACQUIRED,
  STATUS_BIT_IPV6G_ACQUIRED,
  STATUS_BIT_AUTHENTICATION_FAILED,
  STATUS_BIT_RESET_REQUIRED,
} e_StatusBits;

#define CLR_STATUS_BIT_ALL(status_variable)  (status_variable = 0)
#define SET_STATUS_BIT(status_variable, bit) status_variable |= (1 << (bit))
#define CLR_STATUS_BIT(status_variable, bit) status_variable &= ~(1 << (bit))
#define CLR_STATUS_BIT_ALL(status_variable)  (status_variable = 0)
#define GET_STATUS_BIT(status_variable, bit) (0 != (status_variable & (1 << (bit))))

#define IS_CONNECTED(status_variable)        GET_STATUS_BIT( \
        status_variable, \
        STATUS_BIT_CONNECTION)

#define IS_IP_ACQUIRED(status_variable)       GET_STATUS_BIT( \
        status_variable, \
        STATUS_BIT_IP_ACQUIRED)

#endif //__STATUS_H__
