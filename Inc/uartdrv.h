/*******************************************************************************
* File Name          : uartdrv.h
* Author               : Jevon
* Description        : This file provides all the uartdrv driver functions.

* History:
*  06/09/2017 : uartdrv V1.00
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _HYPERTERMINAL_H
#define _HYPERTERMINAL_H
#include "stm8l15x.h"


#define UART_FINISHED_RECV 		0x80
#define UART_FIRST_END_CHAR 		0x40
#define UART_BUF_MAX_LENGTH 	0x3F

//uartdrv
extern u8 UART_RX_NUM;
extern u8 UartRxBuffer[UART_BUF_MAX_LENGTH];

//uartdrv
extern void SerialPutChar(uint8_t c);
extern  void PutStringToUart(char *DataBuf);
#endif  /* _HYPERTERMINAL_H */
/*******************************************************************************
End Of The File
*******************************************************************************/
