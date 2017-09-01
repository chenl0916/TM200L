/*******************************************************************************
* File Name          : uartdrv.c
* Author               : Jevon
* Description        : This file provides all the uartdrv driver functions.

* History:
*  06/09/2017 : uartdrv V1.00
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm8l15x.h"
#include <string.h>
#include "uartdrv.h"

u8 UART_RX_NUM = 0;
u8 UartRxBuffer[UART_BUF_MAX_LENGTH] = {'\0'};

void SerialPutChar(uint8_t c)
{
    USART_SendData8(USART1 , (u8)c);
    while(USART_GetFlagStatus(USART1 , USART_FLAG_TXE) == 0);

/*    UART1_SendData8(c);
    while ((UART1->SR & UART1_SR_TXE ) != UART1_SR_TXE );*/
}

void PutStringToUart(char *DataBuf)
{
	u8 Count;
	
	for(Count=0;Count<strlen(DataBuf);Count++)
	{
		SerialPutChar(DataBuf[Count]);
	}
}

void format_int_to_string(int data, char *string)
{
  char format = 0;
  int i;
  string[0] = '0';
  string[1] = 'x';
  for(i = 7; i >= 0; i--)
  {
    format = (data&(0xF<<(4*i))) >> (4*i);
    if(format > 9)
      string[9-i] = format - 10 + 'A';
    else
      string[9-i] = format + '0';
  }
  string[10] = '\r';
  string[11] = '\n';
  string[12] = '\0';
}

void putint(int32_t data)
{
  char buf[16] = {0};
  format_int_to_string(data, buf);
  PutStringToUart(buf);
}

/*******************************************************************************
End Of The File
*******************************************************************************/
