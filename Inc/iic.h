/*******************************************************************************
* File Name          : iic.h
* Author               : Jevon
* Description        : This file provides all the initialization functions.

* History:
*  03/29/2017 : iic V1.00
*******************************************************************************/
#ifndef __IIC_H
#define __IIC_H
/* Includes ------------------------------------------------------------------*/
#include "stm8l15x_conf.h"
/* Extern variables ---------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
#define I2C_SPEED              		100000/*200000*/
#define I2C_SLAVE_ADDRESS7     0xA0

// Variable Declared 
extern uint8 rw_flag;
extern uint8 reg_no;
extern uint8 rw_data;
//Function Declare
extern void I2C1_Configuration(void);
#endif
/*******************************************************************************
*   Copyrights (C) Asiatelco Technologies Co., 2003-2017. All rights reserved
*                                 End Of The File
*******************************************************************************/

