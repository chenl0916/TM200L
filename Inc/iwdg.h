/*******************************************************************************
* File Name          : wwdg.h
* Author               : Yangjie GU
* Description        : This file provides all the initialization functions.

* History:
*  03/29/2017 : iic V1.00
*******************************************************************************/
#ifndef __IWDG_H
#define __IWDG_H
/* Includes ------------------------------------------------------------------*/
#include "stm8l15x_conf.h"
/* Extern variables ---------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define RELOAD_VALUE   254
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
extern void IWDG_Configuration(void);
extern void TickIndependentWatchdog(void);

#endif
/*******************************************************************************
*   Copyrights (C) Asiatelco Technologies Co., 2003-2017. All rights reserved
*                                 End Of The File
*******************************************************************************/