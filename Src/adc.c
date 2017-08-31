/*******************************************************************************
* File Name          : adc.c
* Author               : Jevon
* Description        : This file provides all the version functions.

* History:
*  06/09/2017 : adc V1.00
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "stm8l15x.h"
#include "adc.h"
#include "uartdrv.h"
/* Extern variables ---------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static u16 ADCConversionBattValue = 0;
static u16 ADCConversionVinValue = 0;
static u8 ADCConversionFinished = FALSE;
#ifndef ADC_SINGLE_CHANNEL_SUPPORT
u16 AdcDmaBuffer[ADC_BUFFER_SIZE]  = {0, 0};
#endif

void ADC_Configuration(void)
{
	#ifndef ADC_SINGLE_CHANNEL_SUPPORT
	/* Initialize and configure ADC1 */
	ADC_Init(ADC1, ADC_ConversionMode_Single, ADC_Resolution_12Bit, ADC_Prescaler_1);
	ADC_SamplingTimeConfig(ADC1, ADC_Group_SlowChannels, ADC_SamplingTime_384Cycles);

	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);

	/* Enable ADC1 Channels 2 */
	ADC_ChannelCmd(ADC1, ADC_Channel_15, ENABLE); /* connected to battery */
	/* Enable ADC1 Channels 3 */
	ADC_ChannelCmd(ADC1, ADC_Channel_16, ENABLE); /* connected to Vin */

	/* Enable End of conversion ADC1 Interrupt */
	//ITC_SetSoftwarePriority(ADC1_COMP_IRQn, ITC_PriorityLevel_1);
	//ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);

	/* Connect ADC to DMA channel 0 */
	SYSCFG_REMAPDMAChannelConfig(REMAP_DMA1Channel_ADC1ToChannel0);

	DMA_Init(DMA1_Channel0, ADC_BUFFER_ADDRESS,
		ADC1_DR_ADDRESS,
		ADC_BUFFER_SIZE,
		DMA_DIR_PeripheralToMemory,
		DMA_Mode_Circular,
		DMA_MemoryIncMode_Inc,
		DMA_Priority_High,
		DMA_MemoryDataSize_HalfWord);

	/* DMA Channel0 enable */
	DMA_Cmd(DMA1_Channel0, ENABLE);

	/* Enable DMA1 channel0 Transfer complete interrupt */
	ITC_SetSoftwarePriority(DMA1_CHANNEL0_1_IRQn, ITC_PriorityLevel_1);
	DMA_ITConfig(DMA1_Channel0, DMA_ITx_TC, ENABLE);

	/* DMA enable */
	DMA_GlobalCmd(ENABLE);

	/* Enable ADC1 DMA requests*/
	ADC_DMACmd(ADC1, ENABLE);
	#else
	/* Initialise and configure ADC1 */
	ADC_Init(ADC1, ADC_ConversionMode_Continuous, ADC_Resolution_12Bit, ADC_Prescaler_2);
	ADC_SamplingTimeConfig(ADC1, ADC_Group_SlowChannels, ADC_SamplingTime_384Cycles);

	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);

	/* Enable ADC1 Channel 3 */
	ADC_ChannelCmd(ADC1, ADC_Channel_14, ENABLE);

	/* Enable End of conversion ADC1 Interrupt */
	ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);

	/* Clear IT Pending Bit */
	DMA_ClearITPendingBit(DMA1_IT_TC0);
		
	/* Start ADC1 Conversion using Software trigger*/
	//ADC_SoftwareStartConv(ADC1);
	#endif
}

void SetADCConversionStatus(u8 Status)
{
	ADCConversionFinished = Status;
}

u8 GetADCConversionStatus(void)
{
	return ADCConversionFinished;
}

void SetADCConversionValue(u16 BattValue, u16 VinValue)
{
	ADCConversionBattValue = BattValue;
	ADCConversionVinValue = VinValue;
}

u16 GetADCConversionBattValue(void)
{
	return ADCConversionBattValue;
}

u16 GetADCConversionVinValue(void)
{
	return ADCConversionVinValue;
}

void ADCConversionStart(void)
{	
	/* Clear IT Pending Bit */
	DMA_ClearITPendingBit(DMA1_IT_TC0);
	// Start adc convert
	ADC_SoftwareStartConv (ADC1);
}

void ShowAdcConvertVoltage(void)
{
	#define CONVERT_ACCURACY 	5
	u8 idx;
	u8 VbatAdcTemp[CONVERT_ACCURACY];
	u8 VinAdcTemp[CONVERT_ACCURACY];
	u8 VbatVoltTemp[CONVERT_ACCURACY];
	u8 VinVoltTemp[CONVERT_ACCURACY];
	
	u16 VBattAdcValue = GetADCConversionBattValue();
	u16 VVinAdcValue = GetADCConversionVinValue();
	u16 VBattVoltValue = ((((u32)VBattAdcValue *3300)/4096)*2);
	u16 VVinVoltValue = ((((u32)VVinAdcValue *3300)/4096)*33);
	// Convert
	for(idx = 0; idx < CONVERT_ACCURACY; idx++)
	{
		VbatAdcTemp[idx] = VBattAdcValue % 10 + '0';
		VBattAdcValue = VBattAdcValue /10;  
	}
	for(idx = 0; idx < CONVERT_ACCURACY; idx++)
	{
		VinAdcTemp[idx] = VVinAdcValue % 10 + '0';
		VVinAdcValue = VVinAdcValue /10;  
	}
	for(idx = 0; idx < CONVERT_ACCURACY; idx++)
	{
		VbatVoltTemp[idx] = VBattVoltValue % 10 + '0';
		VBattVoltValue = VBattVoltValue /10;  
	}
	for(idx = 0; idx < CONVERT_ACCURACY; idx++)
	{
		VinVoltTemp[idx] = VVinVoltValue % 10 + '0';
		VVinVoltValue = VVinVoltValue /10;  
	}
	// Show Battery Voltage
	PutStringToUart((char*)"\r\nADC: Value(");
	SerialPutChar(VbatAdcTemp[3]);
	SerialPutChar(VbatAdcTemp[2]);
	SerialPutChar(VbatAdcTemp[1]);
	SerialPutChar(VbatAdcTemp[0]);
	SerialPutChar(' ');
	SerialPutChar(VinAdcTemp[3]);
	SerialPutChar(VinAdcTemp[2]);
	SerialPutChar(VinAdcTemp[1]);
	SerialPutChar(VinAdcTemp[0]);
	PutStringToUart((char*)") VBattery(");
	SerialPutChar(VbatVoltTemp[3]);
	SerialPutChar(VbatVoltTemp[2]);
	SerialPutChar(VbatVoltTemp[1]);
	SerialPutChar(VbatVoltTemp[0]);
	PutStringToUart((char*)" mV)  Vin(");
	SerialPutChar(VinVoltTemp[4]);
	SerialPutChar(VinVoltTemp[3]);
	SerialPutChar(VinVoltTemp[2]);
	SerialPutChar(VinVoltTemp[1]);
	SerialPutChar(VinVoltTemp[0]);
	PutStringToUart((char*)" mV)\r\n");
}

void PeriodicCheckAdcValue(void)
{
	if(GetADCConversionStatus() == TRUE)
	{
		SetADCConversionStatus(FALSE);
		// Show adc value
		ShowAdcConvertVoltage();
		// Show OK
		PutStringToUart((char*)"\r\nOK\r\n");
	}
}

/*******************************************************************************
*   Copyrights (C) Asiatelco Technologies Co., 2003-2017. All rights reserved
*                                 End Of The File
*******************************************************************************/

