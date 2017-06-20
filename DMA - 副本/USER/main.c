#include "stm32f10x.h"
#include "led.h"
#include "usart1.h"
#include "dma.h"

extern uint8_t SendBuff[SENDBUFF_SIZE];

int main(void)
{	
		int i;
	
		LED_GPIO_Config();
		USART1_Config();
		DMA_Config();
		 
		for(i = 0; i < SENDBUFF_SIZE; i++)
			SendBuff[i] = 'A';
	
	  //  串口向DMA发送请求
		USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
		
		LED1(ON);
		while(1);
}
