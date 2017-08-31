/*******************************************************************************
* File Name          : initialization.h
* Author               : Jevon
* Description        : This file provides all the initialization functions.

* History:
*  06/09/2017 : initialization V1.00
*******************************************************************************/
#ifndef _INITIALIZATION_SOFTWARE_H
#define _INITIALIZATION_SOFTWARE_H
/* Includes ------------------------------------------------------------------*/
#include "stm8l15x_conf.h"
#include "stm8l15x_clk.h"
/* Extern variables ---------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
#define SYSTEM_CLOCK			(8000000)
#define PWM_FREQ_500HZ		(SYSTEM_CLOCK/128/500-1)
#define PWM_FREQ_1KHZ		(SYSTEM_CLOCK/128/1000-1)
#define PWM_FREQ_2KHZ		(SYSTEM_CLOCK/128/2000-1)
#define PWM_DUTYCYCLE 		(50)

// Variable Declared 

//Function Declare
extern void DelayMsTime(u16 delay_time);	//delay delay_time * 1ms
extern void PWM_Configuration(u32 freq, u8 dutycycle, FunctionalState onoff);
extern void SystemReset(void);
extern void HaltPowerConsumption(void);
extern void SystemFromHaltToIdleReinit(void);
extern void LTEPowerControlEn(u8 status);
extern void LTEControlWakeup(u8 status);
extern void BuckPowerControlEn(u8 status);
extern void SystemInitialization(void);

#endif  /* _INITIALIZATION_SOFTWARE_H */
/*******************************************************************************
*   Copyrights (C) Asiatelco Technologies Co., 2003-2017. All rights reserved
*                                 End Of The File
*******************************************************************************/

