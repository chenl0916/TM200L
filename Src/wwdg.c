/*******************************************************************************
* File Name          : wwdg.c
* Author               : Yangjie GU
* Description        : This file provides all the version functions.

* History:
*  03/21/2017 : iic V1.00
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "stm8l15x.h"
#include "wwdg.h"
/* Extern variables ---------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void WWDG_Configuration(void)
{

  /* Check if the MCU has resumed from WWDG reset */
  if (RST_GetFlagStatus(RST_FLAG_WWDGF) != RESET)
  {
    /* Clear WWDGF Flag */
    RST_ClearFlag(RST_FLAG_WWDGF);
  }

  /* WWDG configuration: WWDG is clocked by SYSCLK = 8MHz */
  /* WWDG timeout is equal to 251,9 ms */
  /* Watchdog Window = (COUNTER_INIT - 63) * 1 step
                     = 64 * (12288 / 8Mhz)
                     = 98.3 ms
  */
  WWDG_Init(COUNTER_INIT, WINDOW_VALUE);
}

void TickWindowWatchdog(void)
{
  WWDG_SetCounter(COUNTER_INIT);
}

/*******************************************************************************
*   Copyrights (C) Asiatelco Technologies Co., 2003-2017. All rights reserved
*                                 End Of The File
*******************************************************************************/