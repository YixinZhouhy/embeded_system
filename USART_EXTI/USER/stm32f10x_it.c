/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTI
  
  AL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include <stdio.h>
#include "led.h"
/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

// usart1中断函数
#define r_length  5

int i = 0;

uint8_t ch[r_length] = {'*', '*', '*', '*', '*'};
void USART1_IRQHandler(void)
{
  

	int j;
	
	// 读取状态寄存器中RXNE是否置一 ，置一则进入usart中断
	while(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{ 	 
		ch[i] = USART_ReceiveData(USART1);
		i++;
	}
}


/* usart接收一个字符进入一次中断
   每次接收hex 或者 ascii (char类型)
*/

// int i = 0;  // 用于进入中断计数实验
/*
void USART1_IRQHandler(void)
{
	uint8_t ch;

	// 读取状态寄存器中RXNE是否置一 ，置一则进入usart中断
	if(USART_GetITStatus(USART1, USART_IT_RXNE))
	{ 	 
			i++;		
			ch = USART_ReceiveData(USART1);
	}
	if((i ==  5) && (USART_GetITStatus(USART1, USART_IT_RXNE)))
    LED1(ON);
}
*/

// 接收hex
/*
void USART1_IRQHandler(void)
{
	uint8_t ch;
	
	// 读取状态寄存器中RXNE是否置一 ，置一则进入usart中断
	if(USART_GetITStatus(USART1, USART_IT_RXNE))  
	{ 	 
			ch = USART_ReceiveData(USART1);
			if(ch == 0x01)  // 判断是否接收到0x01
				LED1(ON);
			else
				LED1(OFF);
	}
}
*/

// 接收ascii
/*
void USART1_IRQHandler(void)
{
	uint8_t ch;
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE))
	{ 	 
			ch = USART_ReceiveData(USART1);
			if(ch == 'c')  // 判断是否接收到0x01
				LED1(ON);
			else
				LED1(OFF);
	}
}
*/

//  使用while()检查寄存器状态
/*
void USART1_IRQHandler(void)
{
	uint8_t ch;
	
	// 读取状态寄存器中RXNE是否置一 ，置一则进入usart中断
	while(USART_GetITStatus(USART1, USART_IT_RXNE))
	{ 	
			ch = USART_ReceiveData(USART1);
			printf("%c" , ch);
	}
	printf("**");
}
*/

// if()检查寄存器状态
/*
void USART1_IRQHandler(void)
{
	uint8_t ch;
	
  // 读取状态寄存器中RXNE是否置一 ，置一则进入usart中断 
	if(USART_GetITStatus(USART1, USART_IT_RXNE))
	{ 	
			ch = USART_ReceiveData(USART1);
			printf("%c" , ch);
	}
	printf("**");
}
*/

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
