#ifndef _WIFI_H_
#define _WIFI_H_

extern int WiFi_Register(char *newssid, char *newpass, uint8_t *newbssid);

extern int WiFi_Start(void);

extern int WiFi_Stop(void);

extern bool WiFi_Associated(void);

#endif
