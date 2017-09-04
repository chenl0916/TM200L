/**
  ******************************************************************************
  * @file    Project/STM8L15x_StdPeriph_Template/stm8l15x_it.c
  * @author  MCD Application Team
  * @version V1.6.1
  * @date    30-September-2014
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm8l15x_it.h"
#include "iic.h"
#include "adc.h"
#include "main.h"
#include "rtc.h"
#include "atcmd.h"
#include "uartdrv.h"

/** @addtogroup STM8L15x_StdPeriph_Template
  * @{
  */
  
/* Extern variables ---------------------------------------------------------*/
extern TimeTableT wakeuptimetable;

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define UART1_END_CHAR_OD 		0x0D
#define UART1_END_CHAR_OA 		0x0A

#define I2C_OUTPUT0_CONTROL_REG     0xC0
#define I2C_BUCK_CONTROL_REG        0xC1
#define I2C_LOAD_SWITCH_CONTROL_REG 0xC2
#define I2C_CONTROL_NUM             0x01
#define I2C_CONTROL_0               RESET
#define I2C_CONTROL_1               SET

#define I2C_INPUT0_REG              0xD0
#define I2C_INPUT0_NUM              0x01
#define I2C_VIN_ADC_REGH            0xD1
#define I2C_VIN_ADC_REGL            0xD2
#define I2C_VIN_ADC_NUM             0x02
#define I2C_VBAT_ADC_REGH           0xD3
#define I2C_VBAT_ADC_REGL           0xD4
#define I2C_VBAT_ADC_NUM            0x02

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

#ifdef _COSMIC_
/**
  * @brief Dummy interrupt routine
  * @par Parameters:
  * None
  * @retval 
  * None
*/
INTERRUPT_HANDLER(NonHandledInterrupt,0)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
#endif

/**
  * @brief TRAP interrupt routine
  * @par Parameters:
  * None
  * @retval 
  * None
*/
INTERRUPT_HANDLER_TRAP(TRAP_IRQHandler)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
/**
  * @brief FLASH Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(FLASH_IRQHandler,1)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
/**
  * @brief DMA1 channel0 and channel1 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(DMA1_CHANNEL0_1_IRQHandler,2)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
	#ifndef ADC_SINGLE_CHANNEL_SUPPORT
	//if (DMA_GetITStatus (DMA1_IT_TC0) != RESET)
	{
		/* Clear IT Pending Bit */
		DMA_ClearITPendingBit(DMA1_IT_TC0);
		// Get adc result
		SetADCConversionValue(AdcDmaBuffer[0], AdcDmaBuffer[1]);
		// Set flag
		SetADCConversionStatus(TRUE);
	}
	#endif
}
/**
  * @brief DMA1 channel2 and channel3 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(DMA1_CHANNEL2_3_IRQHandler,3)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
/**
  * @brief RTC / CSS_LSE Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(RTC_CSSLSE_IRQHandler,4)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    // if (RTC->ISR2 & (RTC_IT_ALRA >> 4))
    // {
    //   RTC_ClearITPendingBit(RTC_IT_ALRA);
    //   SetRTCAlarmStatus(TRUE);
    // }

    if (RTC->ISR2 & (RTC_IT_WUT >> 4))
    {
      SetRTCWakeStatus(TRUE);
      RTC_ClearITPendingBit(RTC_IT_WUT);
      wakeuptimetable = GetRTCDatetime();
    }
}
/**
  * @brief External IT PORTE/F and PVD Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTIE_F_PVD_IRQHandler,5)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief External IT PORTB / PORTG Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTIB_G_IRQHandler,6)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
/*	if(EXTI_GetITStatus(EXTI_IT_PortB) !=RESET)
	{
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3) == RESET)
		{
			gInterruptTestFlag = TRUE;
		}
		EXTI_ClearITPendingBit(EXTI_IT_PortB);
	}
	if(EXTI_GetITStatus(EXTI_IT_PortG) !=RESET)
	{

		EXTI_ClearITPendingBit(EXTI_IT_PortG);
	}*/
}

/**
  * @brief External IT PORTD /PORTH Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTID_H_IRQHandler,7)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief External IT PIN0 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI0_IRQHandler,8)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
	if(EXTI_GetITStatus(EXTI_IT_Pin0)!= RESET)
	{
		//if(GPIO_ReadInputDataBit(PB0_MEMS_IT_PORT, PB0_MEMS_IT_PIN) == RESET)
		{
			gInterruptMemsIntFlag = TRUE;
		}
		//if(GPIO_ReadInputDataBit(PD0_WAKEUP_MCU_PORT, PD0_WAKEUP_MCU_PIN) == RESET)
		{
			gInterruptWakeupMcuFlag = TRUE;
		}
		EXTI_ClearITPendingBit(EXTI_IT_Pin0);
	}
}

/**
  * @brief External IT PIN1 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI1_IRQHandler,9)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief External IT PIN2 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI2_IRQHandler,10)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief External IT PIN3 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI3_IRQHandler,11)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief External IT PIN4 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI4_IRQHandler,12)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief External IT PIN5 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI5_IRQHandler,13)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
	if(EXTI_GetITStatus(EXTI_IT_Pin5)!= RESET)
	{
		//if(GPIO_ReadInputDataBit(PB5_EXT_INPUT_PORT, PB5_EXT_INPUT_PIN) == RESET)
		{
			gInterruptExtInputFlag = TRUE;
		}
		EXTI_ClearITPendingBit(EXTI_IT_Pin5);
	}
}

/**
  * @brief External IT PIN6 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI6_IRQHandler,14)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief External IT PIN7 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI7_IRQHandler,15)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
/**
  * @brief LCD /AES Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(LCD_AES_IRQHandler,16)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
/**
  * @brief CLK switch/CSS/TIM1 break Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(SWITCH_CSS_BREAK_DAC_IRQHandler,17)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief ADC1/Comparator Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(ADC1_COMP_IRQHandler,18)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
  /* Get ADC convertion value */
  //ADCdata = ADC_GetConversionValue(ADC1);
  //PotVoltage = ((ADCdata * 3300)/4096)*11;
}

/**
  * @brief TIM2 Update/Overflow/Trigger/Break /USART2 TX Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM2_UPD_OVF_TRG_BRK_USART2_TX_IRQHandler,19)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief Timer2 Capture/Compare / USART2 RX Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM2_CC_USART2_RX_IRQHandler,20)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}


/**
  * @brief Timer3 Update/Overflow/Trigger/Break Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM3_UPD_OVF_TRG_BRK_USART3_TX_IRQHandler,21)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
/**
  * @brief Timer3 Capture/Compare /USART3 RX Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM3_CC_USART3_RX_IRQHandler,22)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
/**
  * @brief TIM1 Update/Overflow/Trigger/Commutation Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM1_UPD_OVF_TRG_COM_IRQHandler,23)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
/**
  * @brief TIM1 Capture/Compare Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM1_CC_IRQHandler,24)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief TIM4 Update/Overflow/Trigger Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM4_UPD_OVF_TRG_IRQHandler,25)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
/**
  * @brief SPI1 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(SPI1_IRQHandler,26)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */		
}

/**
  * @brief USART1 TX / TIM5 Update/Overflow/Trigger/Break Interrupt  routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(USART1_TX_TIM5_UPD_OVF_TRG_BRK_IRQHandler,27)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief USART1 RX / Timer5 Capture/Compare Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(USART1_RX_TIM5_CC_IRQHandler,28)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
	u8 Res;

	/* Read one byte from the receive data register and send it back */
	//UART1_SendData8((UART1_ReceiveData8() & 0x7F));
	
	if(USART_GetITStatus(USART1,USART_IT_RXNE) != RESET)
	{
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		Res = USART_ReceiveData8(USART1); //(USART1->DR)
		if((UART_RX_NUM & UART_FINISHED_RECV) == 0)	// Not Finished
		{
			if(UART_RX_NUM & UART_FIRST_END_CHAR)		// Get 0x0D
			{
				if(Res != UART1_END_CHAR_OA)
					UART_RX_NUM = 0;		// Restart
				else
					UART_RX_NUM |=UART_FINISHED_RECV;	// Finished
			}
			else
			{
				if(Res == UART1_END_CHAR_OD)
					UART_RX_NUM |= UART_FIRST_END_CHAR;
				else
				{
					UartRxBuffer[UART_RX_NUM & UART_BUF_MAX_LENGTH] = Res;
					UART_RX_NUM++;
					if(UART_RX_NUM > UART_BUF_MAX_LENGTH)
						UART_RX_NUM = 0; // Error
				}
			}
		}
	} 
}

/**
  * @brief I2C1 / SPI2 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(I2C1_SPI2_IRQHandler,29)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */

  /* Read SR2 register to get I2C error */
  if (I2C1->SR2 != 0/*I2C_ReadRegister(I2C1, I2C_Register_SR2)*/)
  {
    /* Clears SR2 register */
    I2C1->SR2 = 0;
  }
  /* Check event */
  switch (I2C_GetLastEvent(I2C1))
  {
      /******* Slave transmitter ******/
      /* check on EV1 */
    case I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED:
      rw_flag = 3;
      break;

      /* check on EV3 */
    case I2C_EVENT_SLAVE_BYTE_TRANSMITTING:
      /* Transmit data */
      if(rw_flag == 3)
      {
        /* Transmit data */
        if(reg_no == '0')
	  I2C_SendData(I2C1, 0x00);
        else if(reg_no == '1')
	  I2C_SendData(I2C1, 0x11);
        /*else if(reg_no >= '2')
	  I2C_SendData(I2C1, 0x22);
        else if(reg_no >= '3')
	  I2C_SendData(I2C1, 0x33);
        else if(reg_no >= '4')
	  I2C_SendData(I2C1, 0x44);
        else if(reg_no >= '5')
	  I2C_SendData(I2C1, 0x55);
        else if(reg_no >= '6')
	  I2C_SendData(I2C1, 0x66);
        else if(reg_no >= '7')
	  I2C_SendData(I2C1, 0x77);
        else if(reg_no >= '8')
	  I2C_SendData(I2C1, 0x88);
        else if(reg_no >= '9')
    I2C_SendData(I2C1, 0x99);*/
    else if(reg_no == I2C_INPUT0_REG)
      I2C_SendData(I2C1, GPIO_ReadInputDataBit(PB5_EXT_INPUT_PORT, PB5_EXT_INPUT_PIN));
    else if(reg_no == I2C_VIN_ADC_REGH)
    {
      I2C_SendData(I2C1, ((GetADCConversionVinValue() >> 8) & 0xff));
    }
    else if(reg_no == I2C_VIN_ADC_REGL)
    {
      I2C_SendData(I2C1, ((GetADCConversionVinValue()) & 0xff));
    }
    else if(reg_no == I2C_VBAT_ADC_REGH)
    {
      I2C_SendData(I2C1, ((GetADCConversionBattValue() >> 8) & 0xff));
    }
    else if(reg_no == I2C_VBAT_ADC_REGL)
    {
      I2C_SendData(I2C1, ((GetADCConversionBattValue()) & 0xff));
    }
        else
	  I2C_SendData(I2C1, 0xAA);
      }
      else //fault
      {
        I2C_SendData(I2C1, 0xCC);
      }
      break;
      /******* Slave receiver **********/
      /* check on EV1*/
    case I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED:
      rw_flag = 1;
      reg_no = 0;
      rw_data = 0;
      break;

      /* Check on EV2*/
    case I2C_EVENT_SLAVE_BYTE_RECEIVED:
      if(rw_flag == 1)
      {
        rw_flag = 2;
        reg_no = I2C_ReceiveData(I2C1);
      }
      else if(rw_flag == 2)
      {
        rw_data = I2C_ReceiveData(I2C1);
        if((reg_no & 0xf0) == 0xC0)
        {
          if(reg_no == I2C_OUTPUT0_CONTROL_REG)
          {
            GPIO_WriteBit(PB4_EXT_OUTPUT_PORT, PB4_EXT_OUTPUT_PIN, (BitStatus)rw_data);
          }
          else if(reg_no == I2C_BUCK_CONTROL_REG)
          {
            GPIO_WriteBit(PB6_BUCK_EN_PORT, PB6_BUCK_EN_PIN, (BitStatus)rw_data);
          }
          else if(reg_no == I2C_LOAD_SWITCH_CONTROL_REG)
          {
            //GPIO_WriteBit(, , (BitStatus)rw_data);
          }
          else
          {

          }
        }
      }
      else //fault
      {
        rw_data = I2C_ReceiveData(I2C1);
      }
      break;

      /* Check on EV4 */
    case (I2C_EVENT_SLAVE_STOP_DETECTED):
      /* write to CR2 to clear STOPF flag */
      I2C1->CR2 |= I2C_CR2_ACK;
      break;

    default:
            /* write to CR2 to clear STOPF flag */
            I2C1->CR2 |= I2C_CR2_ACK;
      break;
  }
}
/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
