/*******************************************************************************
* File Name          : adc.h
* Author               : Jevon
* Description        : This file provides all the initialization functions.

* History:
*  06/09/2017 : adc V1.00
*******************************************************************************/
#ifndef __ADC_H
#define __ADC_H
/* Includes ------------------------------------------------------------------*/
#include "stm8l15x_conf.h"
/* Extern variables ---------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
#ifndef ADC_SINGLE_CHANNEL_SUPPORT
#define ADC1_DR_ADDRESS 			((u16)0x5344)
#define ADC_BUFFER_SIZE 			((u8) 0x02)
#define ADC_BUFFER_ADDRESS 		((u16)(&AdcDmaBuffer))
#endif


// Variable Declared 
#ifndef ADC_SINGLE_CHANNEL_SUPPORT
extern u16 AdcDmaBuffer[ADC_BUFFER_SIZE];
#endif
//Function Declare
extern void ADC_Configuration(void);
extern void SetADCConversionStatus(u8 Status);
extern u8 GetADCConversionStatus(void);
extern void SetADCConversionValue(u16 BattValue, u16 VinValue);
extern u16 GetADCConversionBattValue(void);
extern u16 GetADCConversionVinValue(void);
extern void ADCConversionStart(void);
extern void ShowAdcConvertVoltage(void);
extern void PeriodicCheckAdcValue(void);

#endif
/*******************************************************************************
*   Copyrights (C) Asiatelco Technologies Co., 2003-2017. All rights reserved
*                                 End Of The File
*******************************************************************************/

