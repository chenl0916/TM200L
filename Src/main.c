/*******************************************************************************
* File Name          : main.c
* Author               : Jevon
* Description        : This file provides all the sensor driver functions.

* History:
*  06/09/2017 : main V1.00
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm8l15x.h"
#include "iic.h"
#include "adc.h"
#include "rtc.h"
#include "main.h"
#include "atcmd.h"
#include "uartdrv.h"
#include "wwdg.h"
#include "iwdg.h"
#include "initialization.h"

/* Private defines -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#ifdef I2C1_DEBUG
extern uint8_t i2c_control0;
extern uint8_t i2c_control1;
extern uint8_t i2c_control2;
#endif
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static MainLoopStatT MainLoopStat = MAIN_LOOP_IDLE;

//uint16_t ADCdata = 0;
//uint16_t PotVoltage = 0;

u8 gInterruptWakeupMcuFlag = TRUE;
u8 gInterruptMemsIntFlag = TRUE;
u8 gInterruptExtInputFlag = TRUE;

void SetMainLoopMode(MainLoopStatT Mode)
{
	MainLoopStat = Mode;
}

MainLoopStatT GetMainLoopMode(void)
{
	return MainLoopStat;
}

void PeriodicCheckInterrupt(void)
{
	//if(gInterruptWakeupMcuFlag == TRUE)
	{
		static BitStatus WakeupPinOld = RESET;
		static BitStatus WakeupPinNew = RESET;
		//gInterruptWakeupMcuFlag = FALSE;
		// PD0
		WakeupPinNew = GPIO_ReadInputDataBit(PD0_WAKEUP_MCU_PORT , PD0_WAKEUP_MCU_PIN);
		if(WakeupPinNew != WakeupPinOld)
		{
			WakeupPinOld = WakeupPinNew;
			if(WakeupPinNew == RESET)
				PutStringToUart((char*)"\r\nINT: WAK PD0<LOW>\r\n");
			else
				PutStringToUart((char*)"\r\nINT: WAK PD0<HIGH>\r\n");
		}
	}
	//if(gInterruptMemsIntFlag == TRUE)
	{
		static BitStatus MemsPinOld = RESET;
		static BitStatus MemsPinNew = RESET;
		//gInterruptMemsIntFlag = FALSE;
		// PB1
		MemsPinNew = GPIO_ReadInputDataBit(PB0_MEMS_IT_PORT , PB0_MEMS_IT_PIN);
		if(MemsPinNew != MemsPinOld)
		{
			MemsPinOld = MemsPinNew;
			if(MemsPinNew == RESET)
				PutStringToUart((char*)"\r\nINT: MEMS PB0<LOW>\r\n");
			else
				PutStringToUart((char*)"\r\nINT: MEMS PB0<HIGH>\r\n");
		}
	}
	if(gInterruptExtInputFlag == TRUE)
	{
		gInterruptExtInputFlag = FALSE;
		if(GPIO_ReadInputDataBit(PB5_EXT_INPUT_PORT, PB5_EXT_INPUT_PIN) == RESET)
		{
			GPIO_WriteBit(PB4_EXT_OUTPUT_PORT , PB4_EXT_OUTPUT_PIN , SET);
			PutStringToUart((char*)"\r\nINT: EXT PB5<LOW>\r\n");
		}
		else
		{
			GPIO_WriteBit(PB4_EXT_OUTPUT_PORT , PB4_EXT_OUTPUT_PIN , RESET);
			PutStringToUart((char*)"\r\nINT: EXT PB5<HIGH>\r\n");
		}
	}
}

static void Tick_WatchDog(void)
{
	#if WDG_USE_WINDOW_WATCHDOG
	TickWindowWatchdog();
	#else
	TickIndependentWatchdog();
	#endif
}

void main(void)
{
	SystemInitialization();

	// ENABLE RTC wakeup
	RTC_WakeUpCmd(ENABLE);
	// Man Loop
	while (1)
	{
		switch(GetMainLoopMode())
		{
			case MAIN_LOOP_IDLE:
			{
				// AT command
				ATCmdDetection();

				Tick_WatchDog();

				// ADC check 
				PeriodicCheckAdcValue();

				Tick_WatchDog();

				#ifdef I2C1_DEBUG
				if (i2c_control0)
				{
					PutStringToUart("\r\ni2c_control0");
					i2c_control0 = 0;
				}

				if (i2c_control1)
				{
					PutStringToUart("\r\ni2c_control1");
					i2c_control1 = 0;
				}

				if (i2c_control2)
				{
					PutStringToUart("\r\ni2c_control2");
					i2c_control2 = 0;
				}
				#endif

				if (GetRTCWakeStatus())
				{
					PutStringToUart("\r\nWakeup");
					SetRTCWakeStatus(FALSE);
				}

				Tick_WatchDog();

				// Interrupt check
				PeriodicCheckInterrupt();
			}
			break;
			case MAIN_LOOP_DEEP_SLEEP:
			{
				PutStringToUart("\r\nSleep: Deep Sleep");
				// Delay
				DelayMsTime(10);
				// De-Init
				HaltPowerConsumption();
				// Sleep now
				halt();
				// Re-Init
				SystemFromHaltToIdleReinit();

				Tick_WatchDog();

				// Delay
				DelayMsTime(10);
				PutStringToUart("\r\nSleep: WAKE UP");
				SetMainLoopMode(MAIN_LOOP_IDLE);
			}
			break;
			default:
			SetMainLoopMode(MAIN_LOOP_IDLE);
			break;
		}
	} 
}

#ifdef USE_FULL_ASSERT
void assert_failed(u8* file, u32 line)
{ 
  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
