/*******************************************************************************
* File Name          : main.h
* Author               : Jevon
* Description        : This file provides all the sensor driver functions.

* History:
*  06/09/2017 : main V1.00
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _MAIN_APPLICATION_H
#define _MAIN_APPLICATION_H
 /* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "string.h"
#include "stm8l15x.h"

#define COMPANY_REG_INFO 	"\r\n\r\nCopyright (c) 2003-2017 ATEL Corp."
#define FIRMWARE_VERSION 	"\r\nVERSION: TM200L APPLICATION V1.4\r\n"

// GPS RESET (Output)
#define PA0_GPS_RESET_PIN 		GPIO_Pin_0
#define PA0_GPS_RESET_PORT 		GPIOA

// UART1 TXD
#define PA2_UART1_TXD_PIN 		GPIO_Pin_2
#define PA2_UART1_TXD_PORT 		GPIOA

// UART1 RXD
#define PA3_UART1_RXD_PIN 		GPIO_Pin_3
#define PA3_UART1_RXD_PORT 		GPIOA

// MEMS IT (INT Input)
#define PB0_MEMS_IT_PIN 			GPIO_Pin_0
#define PB0_MEMS_IT_PORT 		GPIOB

// PWM BEEP (Output)
#define PB1_PWM_BEEP_PIN 		GPIO_Pin_1
#define PB1_PWM_BEEP_PORT 		GPIOB
 
// ADC1 IN16 (Input)
#define PB2_ADC_IN16_PIN 		GPIO_Pin_2
#define PB2_ADC_IN16_PORT 		GPIOB

// ADC1 IN15 (Input)
#define PB3_ADC_IN15_PIN 		GPIO_Pin_3
#define PB3_ADC_IN15_PORT 		GPIOB

// EXT OUTPUT
#define PB4_EXT_OUTPUT_PIN 		GPIO_Pin_4
#define PB4_EXT_OUTPUT_PORT 		GPIOB

// EXT INPUT (INT Input)
#define PB5_EXT_INPUT_PIN 		GPIO_Pin_5
#define PB5_EXT_INPUT_PORT 		GPIOB

// BUCK ENABLE (Output)
#define PB6_BUCK_EN_PIN 			GPIO_Pin_6
#define PB6_BUCK_EN_PORT 		GPIOB

// MODULE ENABLE (Output)
#define PB7_MODULE_EN_PIN 		GPIO_Pin_7
#define PB7_MODULE_EN_PORT 		GPIOB

// I2C SDA
#define PC0_I2C_SDA_PIN 			GPIO_Pin_0
#define PC0_I2C_SDA_PORT 		GPIOC

// I2C SCL
#define PC1_I2C_SCL_PIN 			GPIO_Pin_1
#define PC1_I2C_SCL_PORT 		GPIOC

// WAKEUP LM61 (Output)
#define PC4_LM61_WAKE_PIN 		GPIO_Pin_4
#define PC4_LM61_WAKE_PORT 		GPIOC

// WAKEUP MCU (INT Input)
#define PD0_WAKEUP_MCU_PIN 		GPIO_Pin_0
#define PD0_WAKEUP_MCU_PORT 	GPIOD

#define I2C1_DEBUG

#define WDG_USE_WINDOW_WATCHDOG	(0)


typedef enum 
{
	MAIN_LOOP_IDLE = 0x0A,
	MAIN_LOOP_DEEP_SLEEP,

	MAIN_LOOP_MAX
} MainLoopStatT;

// Variable Declared
//extern uint16_t ADCdata;
//extern uint16_t PotVoltage;
extern u8 gInterruptWakeupMcuFlag;
extern u8 gInterruptMemsIntFlag;
extern u8 gInterruptExtInputFlag;

// Function Declare
extern void SetMainLoopMode(MainLoopStatT Mode);
extern MainLoopStatT GetMainLoopMode(void);
extern void PeriodicCheckInterrupt(void);
#endif  /* _MAIN_APPLICATION_H */

/*******************************************************************************
End Of The File
*******************************************************************************/
