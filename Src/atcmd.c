/*******************************************************************************
* File Name          : atcmd.c
* Author               : Jevon
* Description        : This file provides all the atcmd driver functions.

* History:
*  06/09/2017 : atcmd V1.00
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm8l15x.h"
#include "adc.h"
#include "rtc.h"
#include "main.h"
#include "atcmd.h"
#include "uartdrv.h"
#include "initialization.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
void ATCmdDetection(void)
{
	#define AT_STRING_ADC 			"ADC"
	#define AT_STRING_RTC 			"RTC"
	#define AT_STRING_RESET 			"RESET"
	#define AT_STRING_SLEEP 			"SLEEP"
	#define AT_STRING_LTEON 			"LTEON"
	#define AT_STRING_LTEOFF 			"LTEOFF"
	#define AT_STRING_WAKEON 		"WAKEON"
	#define AT_STRING_WAKEOFF 		"WAKEOFF"
	#define AT_STRING_PWMON 		"PWMON"
	#define AT_STRING_PWMOFF 		"PWMOFF"
	#define AT_STRING_BUCKON 		"BUCKON"
	#define AT_STRING_BUCKOFF 		"BUCKOFF"
	#define AT_STRING_VERSIOIN 		"VERSION"
	
	if(UART_RX_NUM & UART_FINISHED_RECV)
	{
		u8 DataLen = 0;
		u8 UartData[UART_BUF_MAX_LENGTH];
		
		DataLen = UART_RX_NUM & UART_BUF_MAX_LENGTH;
		UART_RX_NUM = 0;
		memcpy((char *)UartData, (char *)UartRxBuffer, DataLen);
		memset((char *)UartRxBuffer,0,sizeof(UartRxBuffer));

		// Parse AT Cmd
		//PutStringToUart((char*)UartData);
		
		// Get ADC
		if(strncmp((char *)UartData,(char *)AT_STRING_ADC,strlen((char *)AT_STRING_ADC)) == 0)
		{
			// Show OK
			PutStringToUart((char*)"\r\nADC start conversion\r\n");
			// Start Conversion
			ADCConversionStart();
			return;
		}
		// Show RTC time
		if(strncmp((char *)UartData,(char *)AT_STRING_RTC,strlen((char *)AT_STRING_RTC)) == 0)
		{
			uint16_t seconds_left = 0;
			// // Show Time
			// ShowCurrentTime();
			seconds_left = QuerySecondsLeftBeforePowerReset();
			putint(seconds_left);
			// Show OK
			PutStringToUart((char*)"\r\nOK\r\n");
			return;			
		}
		// Reset
		if(strncmp((char *)UartData,(char *)AT_STRING_RESET,strlen((char *)AT_STRING_RESET)) == 0)
		{
			PutStringToUart((char*)"\r\nReset\r\n");
			// Show OK
			PutStringToUart((char*)"\r\nOK\r\n");
			SystemReset();
			return;
		}
		// Modem SLEEP
		if(strncmp((char *)UartData,(char *)AT_STRING_SLEEP,strlen((char *)AT_STRING_SLEEP)) == 0)
		{
			// Enable STM32 Sleep
			LTEControlWakeup(FALSE);
			PutStringToUart((char*)"\r\nMCU & Modem Deep Sleep\r\n");
			// Show OK
			PutStringToUart((char*)"\r\nOK\r\n");
			SetMainLoopMode(MAIN_LOOP_DEEP_SLEEP);
			return;
		}
		// LTE POWER ON
		if(strncmp((char *)UartData,(char *)AT_STRING_LTEON,strlen((char *)AT_STRING_LTEON)) == 0)
		{
			// Enable Modem Power Supply
			LTEPowerControlEn(TRUE);
			PutStringToUart((char*)"\r\nLTE Power ON\r\n");
			// Show OK
			PutStringToUart((char*)"\r\nOK\r\n");
			return;			
		}
		// LTE POWER OFF
		if(strncmp((char *)UartData,(char *)AT_STRING_LTEOFF,strlen((char *)AT_STRING_LTEOFF)) == 0)
		{
			PutStringToUart((char*)"\r\nLTE Power OFF\r\n");
			// Disable LTE Power Supply
			LTEPowerControlEn(FALSE);
			// Show OK
			PutStringToUart((char*)"\r\nOK\r\n");
			return;
		}
		// WAKE ON
		if(strncmp((char *)UartData,(char *)AT_STRING_WAKEON,strlen((char *)AT_STRING_WAKEON)) == 0)
		{
			PutStringToUart((char*)"\r\nWAKE ON\r\n");
			// Wakeup on
			LTEControlWakeup(TRUE);
			// Show OK
			PutStringToUart((char*)"\r\nOK\r\n");
			return;
		}
		// WAKE OFF
		if(strncmp((char *)UartData,(char *)AT_STRING_WAKEOFF,strlen((char *)AT_STRING_WAKEOFF)) == 0)
		{
			PutStringToUart((char*)"\r\nWAKE OFF\r\n");
			// Wakeup off
			LTEControlWakeup(FALSE);
			// Show OK
			PutStringToUart((char*)"\r\nOK\r\n");
			return;
		}
		// PWM PLAYING
		if(strncmp((char *)UartData,(char *)AT_STRING_PWMON,strlen((char *)AT_STRING_PWMON)) == 0)
		{
			// Pwm playing
			PWM_Configuration(PWM_FREQ_1KHZ, PWM_DUTYCYCLE, ENABLE);
			PutStringToUart((char*)"\r\nPWM PLAYING\r\n");
			// Show OK
			PutStringToUart((char*)"\r\nOK\r\n");
			return;
		}
		// PWM STOP
		if(strncmp((char *)UartData,(char *)AT_STRING_PWMOFF,strlen((char *)AT_STRING_PWMOFF)) == 0)
		{
			// Pwm stop
			PWM_Configuration(PWM_FREQ_1KHZ, PWM_DUTYCYCLE, DISABLE);
			PutStringToUart((char*)"\r\nPWM STOP\r\n");
			// Show OK
			PutStringToUart((char*)"\r\nOK\r\n");
			return;
		}
		// Buck POWERON
		if(strncmp((char *)UartData,(char *)AT_STRING_BUCKON,strlen((char *)AT_STRING_BUCKON)) == 0)
		{
			// Enable Buck Power Supply
			BuckPowerControlEn(TRUE);
			PutStringToUart((char*)"\r\nBuck Power ON\r\n");
			// Show OK
			PutStringToUart((char*)"\r\nOK\r\n");
			return;
		}
		// Buck POWEROFF
		if(strncmp((char *)UartData,(char *)AT_STRING_BUCKOFF,strlen((char *)AT_STRING_BUCKOFF)) == 0)
		{
			// Disable Buck Power Supply
			BuckPowerControlEn(FALSE);
			PutStringToUart((char*)"\r\nBuck Power OFF\r\n");
			// Show OK
			PutStringToUart((char*)"\r\nOK\r\n");
			return;
		}
		// Get Version
		if(strncmp((char *)UartData,(char *)AT_STRING_VERSIOIN,strlen((char *)AT_STRING_VERSIOIN)) == 0)
		{
			PutStringToUart((char*)FIRMWARE_VERSION);
			// Show OK
			PutStringToUart((char*)"\r\nOK\r\n");
			return;
		}
		// Show Error
		PutStringToUart((char*)"\r\nERROR\r\n");
	}
}

/*******************************************************************************
End Of The File
*******************************************************************************/
