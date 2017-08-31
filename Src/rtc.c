/*******************************************************************************
* File Name          : iic.c
* Author               : Jevon
* Description        : This file provides all the version functions.

* History:
*  06/12/2017 : iic V1.00
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "stm8l15x.h"
#include "iic.h"
#include "adc.h"
#include "rtc.h"
#include "uartdrv.h"
/* Extern variables ---------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void DectoBCD(int Dec, u8 *Bcd, int length)
{
	int i;
	int temp;
	for(i=length-1; i>=0; i--)
	{
		temp = Dec%100;
		Bcd[i] = ((temp/10)<<4) + ((temp%10) & 0x0F);
		Dec /= 100;
	}
}

void RTC_Configuration(void)
{
	TimeTableT timeTable = RTC_DEFAULT_TIME;	
	RTC_InitTypeDef RTC_InitStructure;

	//RTC_DeInit();
	//clock configuration 
#ifndef CRYSTAL_OSCILLATOR_32K_SUPPORT
	CLK_LSICmd(ENABLE);
        // Waiting for LST readys
	while (CLK_GetFlagStatus(CLK_FLAG_LSIRDY) == RESET);
        // RTC based on LSI, 1 division = 38Khz
	CLK_RTCClockConfig(CLK_RTCCLKSource_LSI, CLK_RTCCLKDiv_1);
	
	RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;
	RTC_InitStructure.RTC_AsynchPrediv = 0x7C;
	RTC_InitStructure.RTC_SynchPrediv = 0x012F;
	RTC_Init(&RTC_InitStructure);

#else
	CLK_LSEConfig(CLK_LSE_ON);	
        // Waiting for LST readys
	while (CLK_GetFlagStatus(CLK_FLAG_LSERDY) == RESET);
        // RTC based on LSE, 1 division = 32.768Khz
	CLK_RTCClockConfig(CLK_RTCCLKSource_LSE, CLK_RTCCLKDiv_1);

	RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;
	RTC_InitStructure.RTC_AsynchPrediv = 0x7F;
	RTC_InitStructure.RTC_SynchPrediv = 0x00FF;
	RTC_Init(&RTC_InitStructure);
#endif
	// Set time
	SetRTCDatetime(&timeTable);
	// Disable wakeup
	RTC_WakeUpCmd(DISABLE);
}

TimeTableT GetRTCDatetime(void)
{
	TimeTableT timeTable;
	RTC_TimeTypeDef rtc_time;
	RTC_DateTypeDef rtc_date;

	/* gather RTC time */
	while (RTC_WaitForSynchro() == ERROR);
	/* Get the RTC current Time */
	RTC_GetTime(RTC_Format_BIN, &rtc_time);
	/* Get the RTC current Date */
	RTC_GetDate(RTC_Format_BIN, &rtc_date);
  
	/* Display time Format : hh:mm:ss */
	timeTable.year = rtc_date.RTC_Year/* + 2000*/;
	timeTable.month = rtc_date.RTC_Month;
	timeTable.day = rtc_date.RTC_Date;
	timeTable.hour = rtc_time.RTC_Hours;
	timeTable.minute = rtc_time.RTC_Minutes;
	timeTable.second = rtc_time.RTC_Seconds;

	return timeTable;
}

void SetRTCDatetime(TimeTableT *tm)
{
	//sync time response
	RTC_TimeTypeDef RTC_TimeStructure;
	RTC_DateTypeDef RTC_DateStructure;

	// Data
	if(tm->year < 1900)
		DectoBCD(tm->year+2000, &RTC_DateStructure.RTC_Year, 1);
	else
		DectoBCD(tm->year, &RTC_DateStructure.RTC_Year, 1);
	DectoBCD(tm->month,(u8*) (&RTC_DateStructure.RTC_Month), 1);
	DectoBCD(tm->day, &RTC_DateStructure.RTC_Date, 1);
	// Week
	DectoBCD(tm->weekday, (u8*)&RTC_DateStructure.RTC_WeekDay, 1);
	// Time
	DectoBCD(tm->hour, &RTC_TimeStructure.RTC_Hours, 1);
	DectoBCD(tm->minute, &RTC_TimeStructure.RTC_Minutes, 1);
	DectoBCD(tm->second, &RTC_TimeStructure.RTC_Seconds, 1);
	// Set date & time
	RTC_SetTime(RTC_Format_BCD, &RTC_TimeStructure);
	RTC_SetDate(RTC_Format_BCD, &RTC_DateStructure);
	//while (RTC_WaitForSynchro() == ERROR);
}

void ShowCurrentTime(void)
{
	TimeTableT timeTable = GetRTCDatetime();
	
	PutStringToUart((char*)"\r\nRTC Time: ");
	// Year
	SerialPutChar(timeTable.year/10%10 + '0');
	SerialPutChar(timeTable.year%10 + '0');
	SerialPutChar('/');
	// Month
	SerialPutChar(timeTable.month/10%10 + '0');
	SerialPutChar(timeTable.month%10 + '0');
	SerialPutChar('/');
	// Day
	SerialPutChar(timeTable.day/10%10 + '0');
	SerialPutChar(timeTable.day%10 + '0');
	SerialPutChar(' ');
	// Hour
	SerialPutChar(timeTable.hour/10%10 + '0');
	SerialPutChar(timeTable.hour%10 + '0');
	SerialPutChar(':');
	// Minute
	SerialPutChar(timeTable.minute/10%10 + '0');
	SerialPutChar(timeTable.minute%10 + '0');
	SerialPutChar(':');
	// Second
	SerialPutChar(timeTable.second/10%10 + '0');
	SerialPutChar(timeTable.second%10 + '0');
	PutStringToUart((char*)"\r\n");
}
/*******************************************************************************
*   Copyrights (C) Asiatelco Technologies Co., 2003-2017. All rights reserved
*                                 End Of The File
*******************************************************************************/

