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

/*******************************************************************************
End Of The File
*******************************************************************************/
