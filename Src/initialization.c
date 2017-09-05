/*******************************************************************************
* File Name          : initialization.h
* Author               : Jevon
* Description        : This file provides all the initialization functions.

* History:
*  06/09/2017 : initialization V1.00
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "stm8l15x.h"
#include "iic.h"
#include "adc.h"
#include "rtc.h"
#include "main.h"
#include "uartdrv.h"
#include "wwdg.h"
#include "iwdg.h"
#include "initialization.h"
/* Extern variables ---------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
****Function instructions:The internal high speed clock configuration 
*******************************************************************************/
// DelayMsTime
void DelayMsTime(u16 delay_time)	//delay delay_time * 1ms
{
	u16 i;
	u8 j;
	u8 Count = 255;

	for (i = 0; i < delay_time; i++)
	{
		for (j = 0; j < 10; j++)
		{
			while(--Count);
		}
	}
}

static void CLK_Configuration(void)
{
	/*High speed internal clock prescaler: 1  Fmaster = 8MHz Clock divider to HSI/1*/
	CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_2);

	// /* Enable Time3 clock */
	// CLK_PeripheralClockConfig(CLK_Peripheral_TIM3 , ENABLE);
	// /* Enable RTC clock */
	// CLK_PeripheralClockConfig(CLK_Peripheral_RTC, ENABLE);
	// /* Enable CLK_Peripheral_USART1 clock */
	// CLK_PeripheralClockConfig(CLK_Peripheral_USART1 , ENABLE);
	// /* Enable ADC1 clock */
	// CLK_PeripheralClockConfig(CLK_Peripheral_ADC1, ENABLE);
	// #ifndef ADC_SINGLE_CHANNEL_SUPPORT
	// /* Enable DMA1 clock */
	// CLK_PeripheralClockConfig(CLK_Peripheral_DMA1, ENABLE);
	// #endif
	// /* Enable I2C1 clock */
	// CLK_PeripheralClockConfig(CLK_Peripheral_I2C1, ENABLE);

	/* Enable the peripheral Clock */
	CLK->PCKENR1 |= (uint8_t)(	(uint8_t)1 << ((uint8_t)CLK_Peripheral_TIM3 & (uint8_t)0x0F)
								| (uint8_t)1 << ((uint8_t)CLK_Peripheral_I2C1 & (uint8_t)0x0F)
								| (uint8_t)1 << ((uint8_t)CLK_Peripheral_USART1 & (uint8_t)0x0F));

	/* Enable the peripheral Clock */
	CLK->PCKENR2 |= (uint8_t)(	(uint8_t)1 << ((uint8_t)CLK_Peripheral_ADC1 & (uint8_t)0x0F)
								| (uint8_t)1 << ((uint8_t)CLK_Peripheral_RTC & (uint8_t)0x0F)
								| (uint8_t)1 << ((uint8_t)CLK_Peripheral_DMA1 & (uint8_t)0x0F));
}

static void GPIO_Configuration(void)
{
	// GPIOD Reset 
/*	GPIO_DeInit(GPIOA);
	GPIO_DeInit(GPIOB);
	GPIO_DeInit(GPIOC);
	GPIO_DeInit(GPIOD);

	// Low Power for no user pin
	GPIO_Init(GPIOA, GPIO_Pin_All,GPIO_Mode_In_FL_No_IT );
	GPIO_Init(GPIOB, GPIO_Pin_All,GPIO_Mode_In_FL_No_IT );
	GPIO_Init(GPIOC, GPIO_Pin_All,GPIO_Mode_In_FL_No_IT );
	GPIO_Init(GPIOD, GPIO_Pin_All,GPIO_Mode_In_FL_No_IT );
*/
	SYSCFG_REMAPDeInit();
	SYSCFG_REMAPPinConfig(REMAP_Pin_USART1TxRxPortA , ENABLE);

	// GPIO Output
	GPIO_Init(PA0_GPS_RESET_PORT , PA0_GPS_RESET_PIN , GPIO_Mode_Out_PP_Low_Fast);
	GPIO_Init(PA2_UART1_TXD_PORT, PA2_UART1_TXD_PIN, GPIO_Mode_Out_PP_High_Fast);
	GPIO_Init(PA3_UART1_RXD_PORT, PA3_UART1_RXD_PIN, GPIO_Mode_In_PU_No_IT);
	GPIO_Init(PB4_EXT_OUTPUT_PORT , PB4_EXT_OUTPUT_PIN , GPIO_Mode_Out_PP_Low_Fast);
	GPIO_Init(PB6_BUCK_EN_PORT , PB6_BUCK_EN_PIN , GPIO_Mode_Out_PP_Low_Fast);
	GPIO_Init(PB7_MODULE_EN_PORT , PB7_MODULE_EN_PIN , GPIO_Mode_Out_PP_Low_Fast);
	GPIO_Init(PC4_LM61_WAKE_PORT , PC4_LM61_WAKE_PIN , GPIO_Mode_Out_PP_Low_Fast);
	// PWM
	GPIO_Init(PB1_PWM_BEEP_PORT, PB1_PWM_BEEP_PIN, GPIO_Mode_Out_PP_Low_Fast);
	
	// GPIO Input without Int
	//GPIO_Init(PB2_ADC_IN16_PORT , PB2_ADC_IN16_PIN , GPIO_Mode_In_FL_No_IT);
	//GPIO_Init(PB3_ADC_IN15_PORT , PB3_ADC_IN15_PIN , GPIO_Mode_In_FL_No_IT);
	
	// GPIO Input with Int
	GPIO_Init(PB0_MEMS_IT_PORT , PB0_MEMS_IT_PIN , GPIO_Mode_In_FL_No_IT/*GPIO_Mode_In_FL_IT*/);
	GPIO_Init(PD0_WAKEUP_MCU_PORT , PD0_WAKEUP_MCU_PIN , GPIO_Mode_In_FL_IT);
	GPIO_Init(PB5_EXT_INPUT_PORT , PB5_EXT_INPUT_PIN , GPIO_Mode_In_FL_IT);
	
	// Interrupt Configuration
	EXTI_SetPinSensitivity(EXTI_Pin_0 , EXTI_Trigger_Rising_Falling);
	EXTI_SetPinSensitivity(EXTI_Pin_5 , EXTI_Trigger_Rising_Falling);

	// Default value
	GPIO_WriteBit(PA0_GPS_RESET_PORT , PA0_GPS_RESET_PIN ,SET);		// Keep high
	GPIO_WriteBit(PB4_EXT_OUTPUT_PORT , PB4_EXT_OUTPUT_PIN , SET);	// Keep high
	GPIO_WriteBit(PB6_BUCK_EN_PORT , PB6_BUCK_EN_PIN , SET);		// Keep high(DC-DC on)	
	GPIO_WriteBit(PB7_MODULE_EN_PORT , PB7_MODULE_EN_PIN , RESET);	// Keep low(LTE off)
	GPIO_WriteBit(PC4_LM61_WAKE_PORT , PC4_LM61_WAKE_PIN , RESET);	// Keep low(LTE sleep)
}

static void UART_Configuration(void)
{
	// UART1
	USART_DeInit(USART1);
	USART_Init(USART1,
	    115200,
	    USART_WordLength_8b,
	    USART_StopBits_1,
	    USART_Parity_No,
	    USART_Mode_RxTx);

	// USART_ITConfig(USART1, USART_IT_RXNE , ENABLE);
	USART1->CR2 |= (uint8_t)((uint8_t)1 << (uint8_t)0x05);
	// USART_Cmd(USART1 , ENABLE);
	USART1->CR1 &= (uint8_t)(~USART_CR1_USARTD); /**< USART Enable */
}

void PWM_Configuration(u32 freq, u8 dutycycle, FunctionalState onoff)
{	
	// System clock 8MHz
	TIM3_TimeBaseInit(TIM3_Prescaler_128 ,
	        TIM3_CounterMode_Up ,
	        freq);
	TIM3_OC1Init(TIM3_OCMode_PWM2 ,
	   TIM3_OutputState_Enable , 
	   (freq * dutycycle / 100) ,
	   TIM3_OCPolarity_Low ,
	   TIM3_OCIdleState_Set);

	// TIM3_CCxCmd(TIM3_Channel_1 , ENABLE);
	TIM3->CCER1 |= TIM_CCER1_CC1E ;
	TIM3_SetCompare1(freq * dutycycle / 100);
	TIM3_CtrlPWMOutputs(onoff);
	TIM3_Cmd(onoff);
}

void SystemReset(void)
{
	typedef  void (*pFunction)(void);
	typedef  void (*Function_Pointer)(void);
	
	Function_Pointer  Jump_Function;

	/* Jump to the illegal opcode address */
	Jump_Function = (Function_Pointer) 0x8000;
	Jump_Function();
}

void HaltPowerConsumption(void)
{
	// Deep sleep
	LTEControlWakeup(FALSE);
	// LTE OFF
	LTEPowerControlEn(FALSE);
	// Disable Buck Power Supply
	//BuckPowerControlEn(FALSE);  // Cannot close, it will make system lose power supply
			
	// Close Peripherals
	ADC_DeInit(ADC1);
	USART_DeInit(USART1);
	I2C_DeInit(I2C1);
	TIM3_DeInit();

	// Delay
	//DelayMsTime(1000);

	GPIO_Init(PA0_GPS_RESET_PORT, PA0_GPS_RESET_PIN,GPIO_Mode_In_FL_No_IT );
	GPIO_Init(PB1_PWM_BEEP_PORT, PB1_PWM_BEEP_PIN,GPIO_Mode_In_FL_No_IT );
	GPIO_Init(PB4_EXT_OUTPUT_PORT, PB4_EXT_OUTPUT_PIN,GPIO_Mode_In_FL_No_IT );
	GPIO_Init(PC0_I2C_SDA_PORT, PC0_I2C_SDA_PIN | PC1_I2C_SCL_PIN,GPIO_Mode_In_FL_No_IT );
	GPIO_Init(PC4_LM61_WAKE_PORT, PC4_LM61_WAKE_PIN,GPIO_Mode_In_FL_No_IT );
	
	// GPIOD Reset 
/*	GPIO_DeInit(GPIOA);
	GPIO_DeInit(GPIOB);
	GPIO_DeInit(GPIOC);
	GPIO_DeInit(GPIOD);

	// Low Power for no user pin
	GPIO_Init(GPIOA, GPIO_Pin_All,GPIO_Mode_In_FL_No_IT );
	GPIO_Init(GPIOB, GPIO_Pin_All,GPIO_Mode_In_FL_No_IT );
	GPIO_Init(GPIOC, GPIO_Pin_All,GPIO_Mode_In_FL_No_IT );
	GPIO_Init(GPIOD, GPIO_Pin_All,GPIO_Mode_In_FL_No_IT );*/


	// // Close Clock
	// CLK_PeripheralClockConfig(CLK_Peripheral_TIM3 , DISABLE);
	// //CLK_PeripheralClockConfig(CLK_Peripheral_RTC, DISABLE);
	// CLK_PeripheralClockConfig(CLK_Peripheral_USART1 , DISABLE);
	// CLK_PeripheralClockConfig(CLK_Peripheral_ADC1, DISABLE);
	// #ifndef ADC_SINGLE_CHANNEL_SUPPORT
	// CLK_PeripheralClockConfig(CLK_Peripheral_DMA1, DISABLE);
	// #endif
	// CLK_PeripheralClockConfig(CLK_Peripheral_I2C1, DISABLE);

	/* Disable the peripheral Clock */
	CLK->PCKENR1 &= ~(uint8_t)(	(uint8_t)1 << ((uint8_t)CLK_Peripheral_TIM3 & (uint8_t)0x0F)
								| (uint8_t)1 << ((uint8_t)CLK_Peripheral_I2C1 & (uint8_t)0x0F)
								| (uint8_t)1 << ((uint8_t)CLK_Peripheral_USART1 & (uint8_t)0x0F));

	/* Disable the peripheral Clock */
	CLK->PCKENR2 &= ~(uint8_t)(	(uint8_t)1 << ((uint8_t)CLK_Peripheral_ADC1 & (uint8_t)0x0F)
								| (uint8_t)1 << ((uint8_t)CLK_Peripheral_DMA1 & (uint8_t)0x0F));

	CLK_HaltConfig(CLK_Halt_SlowWakeup, ENABLE);
}

void SystemFromHaltToIdleReinit(void)
{
	// // Open Clock
	// /* Enable CLK_Peripheral_USART1 clock */
	// CLK_PeripheralClockConfig(CLK_Peripheral_USART1 , ENABLE);
	// /* Enable ADC1 clock */
	// CLK_PeripheralClockConfig(CLK_Peripheral_ADC1, ENABLE);

	/* Enable the peripheral Clock */
	CLK->PCKENR1 |= (uint8_t)(	/*(uint8_t)1 << ((uint8_t)CLK_Peripheral_TIM3 & (uint8_t)0x0F)
								| (uint8_t)1 << ((uint8_t)CLK_Peripheral_I2C1 & (uint8_t)0x0F)
								| */(uint8_t)1 << ((uint8_t)CLK_Peripheral_USART1 & (uint8_t)0x0F));

	/* Enable the peripheral Clock */
	CLK->PCKENR2 |= (uint8_t)(	(uint8_t)1 << ((uint8_t)CLK_Peripheral_ADC1 & (uint8_t)0x0F)
								/*| (uint8_t)1 << ((uint8_t)CLK_Peripheral_RTC & (uint8_t)0x0F)
								| (uint8_t)1 << ((uint8_t)CLK_Peripheral_DMA1 & (uint8_t)0x0F)*/);

	// Open Peripherals
	UART_Configuration();
	ADC_Configuration();
}

void LTEPowerControlEn(u8 status)
{
	if(status == TRUE)
	{
		// LDO ON
		GPIO_WriteBit(PB7_MODULE_EN_PORT , PB7_MODULE_EN_PIN ,SET);
	}
	else
	{
		// LDO OFF
		GPIO_WriteBit(PB7_MODULE_EN_PORT , PB7_MODULE_EN_PIN ,RESET);
	}
}

void LTEControlWakeup(u8 status)
{
	if(status == TRUE)
	{
		// WAKEOUT ON
		GPIO_WriteBit(PC4_LM61_WAKE_PORT , PC4_LM61_WAKE_PIN ,SET);
	}
	else
	{
		// WAKEOUT OFF(deepsleep)
		GPIO_WriteBit(PC4_LM61_WAKE_PORT , PC4_LM61_WAKE_PIN ,RESET);
	}
}

void BuckPowerControlEn(u8 status)
{
	if(status == TRUE)
	{
		// LDO ON
		GPIO_WriteBit(PB6_BUCK_EN_PORT , PB6_BUCK_EN_PIN ,SET);
	}
	else
	{
		// LDO OFF
		GPIO_WriteBit(PB6_BUCK_EN_PORT , PB6_BUCK_EN_PIN ,RESET);
	}
}

void SystemInitialization(void)
{
	disableInterrupts();

	/* Configures clocks */
	CLK_Configuration();

	/* Configures GPIOs */
	GPIO_Configuration();
	
	/* Configures UARTs */
	UART_Configuration();

	/* Configures ADCs */
	ADC_Configuration();

	/* Configures I2C1s */
	I2C1_Configuration();

	/* Configures TIMEs */
	PWM_Configuration(PWM_FREQ_1KHZ, PWM_DUTYCYCLE, DISABLE);
		
	// Enable Interrupts
	enableInterrupts();

	/* Configures RTC */
	RTC_Configuration();

	// DC-DC ON
	BuckPowerControlEn(TRUE);

	// Delay
	DelayMsTime(1);

	PWR_FastWakeUpCmd(ENABLE);
	PWR_UltraLowPowerCmd(ENABLE);

	// Show System Status
	PutStringToUart((char*)COMPANY_REG_INFO);
	PutStringToUart((char*)FIRMWARE_VERSION);

	ShowCurrentTime();

	// Delay
	DelayMsTime(1000);

	// Enable Power Supply
	LTEPowerControlEn(TRUE);
	// Wakeup
	LTEControlWakeup(TRUE);

	#if	WDG_USE_WINDOW_WATCHDOG
	WWDG_Configuration();
	#else
	IWDG_Configuration();
	#endif
}

/*******************************************************************************
*   Copyrights (C) Asiatelco Technologies Co., 2003-2017. All rights reserved
*                                 End Of The File
*******************************************************************************/

