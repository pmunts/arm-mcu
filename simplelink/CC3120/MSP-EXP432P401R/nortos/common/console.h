#ifndef __CONSOLE_H__
#define __CONSOLE_H__

// TI-Driver includes
#include <ti/drivers/UART.h>
#include <Board.h>

//Defines

#define UART_PRINT Report
#define DBG_PRINT  Report
#define ERR_PRINT(x) Report("Error [%d] at line [%d] in function [%s]  \n\r", x,__LINE__, __FUNCTION__)

/* API */

UART_Handle InitTerm(void);

int Report(const char *pcFormat,
           ...);

int TrimSpace(char * pcInput);

int GetCmd(char *pcBuffer,
           unsigned int uiBufLen);

void Message(const char *str);

void ClearTerm();

char getch(void);

void putch(char ch);

#undef  printf
#define printf Report

#undef puts
#define puts Message

#undef  gets
#define gets(s) GetCmd(s, sizeof(s))

#endif // __CONSOLE_H__
