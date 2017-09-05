/*******************************************************************************
* File Name          : iic.h
* Author               : Jevon
* Description        : This file provides all the initialization functions.

* History:
*  03/29/2017 : iic V1.00
*******************************************************************************/
#ifndef __RTC_H
#define __RTC_H
/* Includes ------------------------------------------------------------------*/
#include "stm8l15x_conf.h"
/* Extern variables ---------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
#define LEAP_YEAR  			(366)
#define NORM_YEAR  			(365)
#define BASE_YEAR 			(1980)
#define LEAP_LOOP       			(366+(3*365))
#define BASE_OFFSET 			(432000)
#define SECONDS_PER_YEAR 	 (86400*365)
#define WAKE_S1_FOR_SECS	(1*60)
#define WAKE_S2_FOR_SECS	(4*60)
#define RTC_DEFAULT_TIME 		{2017,7,25,17,55,35,2}	// Year-month-day  hour:minute:second  weekday
#define RTC_TIMER_SHOW 		(25)
#define RTC_WAKEUP_PERIOD_SECONDS  (8)

typedef struct {
  uint16 year;
  uint8 month;
  uint8 day;
  uint8 hour;
  uint8 minute;
  uint8 second;
  uint8 weekday;
}TimeTableT;

// Variable Declared 


//Function Declare
extern void RTC_Configuration(void);
extern void RTC_WakeUpSet(uint16_t SecondsToWakeup);
extern void SetRTCWakeStatus(u8 Status);
extern u8 GetRTCWakeStatus(void);
extern uint16_t QuerySecondsLeft(void);
extern void DectoBCD(int Dec, u8 *Bcd, int length);
extern TimeTableT GetRTCDatetime(void);
extern void SetRTCDatetime(TimeTableT *tm);
extern void ShowCurrentTime(void);
#endif
/*******************************************************************************
*   Copyrights (C) Asiatelco Technologies Co., 2003-2017. All rights reserved
*                                 End Of The File
*******************************************************************************/

