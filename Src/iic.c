/*******************************************************************************
* File Name          : iic.c
* Author               : Jevon
* Description        : This file provides all the version functions.

* History:
*  03/21/2017 : iic V1.00
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "stm8l15x.h"
#include "iic.h"
#include "adc.h"
#include "uartdrv.h"
/* Extern variables ---------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
uint8 rw_flag = 0;
uint8 reg_no = 0;//read/write register
uint8 rw_data = 0;

void I2C1_Configuration(void)
{
  // I2C_Cmd(I2C1, ENABLE);
  I2C1->CR1 |= I2C_CR1_PE;
  
  /* I2C configuration after enabling it */
  I2C_Init(I2C1, I2C_SPEED, I2C_SLAVE_ADDRESS7, I2C_Mode_I2C, I2C_DutyCycle_2,
           I2C_Ack_Enable, I2C_AcknowledgedAddress_7bit);

  /* Enable Error Interrupt*/
  // I2C_ITConfig(I2C1, (I2C_IT_TypeDef)(I2C_IT_ERR | I2C_IT_EVT | I2C_IT_BUF), ENABLE);
  I2C1->ITR |= (uint8_t)((I2C_IT_ERR | I2C_IT_EVT | I2C_IT_BUF));
}

/*******************************************************************************
*   Copyrights (C) Asiatelco Technologies Co., 2003-2017. All rights reserved
*                                 End Of The File
*******************************************************************************/

