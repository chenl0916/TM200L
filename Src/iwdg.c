/*******************************************************************************
* File Name          : wwdg.c
* Author               : Yangjie GU
* Description        : This file provides all the version functions.

* History:
*  03/21/2017 : iic V1.00
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "stm8l15x.h"
#include "iwdg.h"
/* Extern variables ---------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void IWDG_Configuration(void)
{
    #define OPT0    (*((uint8_t *)0x004800))
    #define OPT3    (*((uint8_t *)0x004808))
    uint8_t ReadOpt = 0;

    /* Check if the system has resumed from IWDG reset */
    if (RST_GetFlagStatus(RST_FLAG_IWDGF) != RESET)
    {
        /* Clear IWDGF Flag */
        RST_ClearFlag(RST_FLAG_IWDGF);
    }

    OPT0 = 0xaa;
	ReadOpt = OPT3;
	if ((ReadOpt & 0x02) == 0x00)
	{
		FLASH->CR2 |= (0x01 << 7);
		FLASH->DUKR = 0xAE;
		FLASH->DUKR = 0x56;
		for (; (FLASH->IAPSR & (0x01 << 3) == 0x00);)
			;
		ReadOpt = OPT3;
		OPT3 |= (0x01 << 1);
		//FLASH->IAPSR |= (0x01 << 3);
		//for(;!(FLASH->IAPSR & (0x01 << 3)););
		ReadOpt = OPT3;
		FLASH->CR2 &= ~(0x01 << 7);
	}

    /* Enable IWDG (the LSI oscillator will be enabled by hardware) */
    IWDG_Enable();

    /* IWDG timeout equal to 214 ms (the timeout may varies due to LSI frequency
     dispersion) */
    /* Enable write access to IWDG_PR and IWDG_RLR registers */
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);

    /* IWDG configuration: IWDG is clocked by LSI = 38KHz */
    IWDG_SetPrescaler(IWDG_Prescaler_256);

    /* IWDG timeout equal to 1717.6 ms (the timeout may varies due to LSI frequency dispersion) */
    /* IWDG timeout = (RELOAD_VALUE + 1) * Prescaler / LSI 
                  = (254 + 1) * 256 / 38 000 
                  = 1717.6 ms */
    IWDG_SetReload((uint8_t)RELOAD_VALUE);

    /* Reload IWDG counter */
    IWDG_ReloadCounter();
}

void TickIndependentWatchdog(void)
{
    /* Reload IWDG counter */
    IWDG_ReloadCounter();
}

/*******************************************************************************
*   Copyrights (C) Asiatelco Technologies Co., 2003-2017. All rights reserved
*                                 End Of The File
*******************************************************************************/