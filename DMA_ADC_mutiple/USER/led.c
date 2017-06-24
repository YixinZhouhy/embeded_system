#include "led.h"

void LED_GPIO_Config(void)
{
	  // 定义一个GPIO_InitTypeDef 类型的结构体
    GPIO_InitTypeDef GPIO_InitStructure;
    
	  // enable the clock of the GPIOC
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	 
	  // select the pin
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	
	  // configure the mode of the pin
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	 
	  // configure the speed of the pin
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	  // initialize the GPIOC
		GPIO_Init(GPIOC, &GPIO_InitStructure);
	 
	  // 
	  GPIO_SetBits(GPIOC, GPIO_Pin_1 | GPIO_Pin_0);
}

// 延时函数
void delay(__IO uint32_t nCount)  
{
	  for(; nCount != 0; nCount--);
}
