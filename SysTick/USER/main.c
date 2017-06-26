#include "stm32f10x.h"
#include "led.h"
#include "SysTick.h"


int main(void)
{	
		// LED 端口初始化 
		LED_GPIO_Config();
	  // SysTick初始化
		SysTick_Init();
 
		while (1)
		{
			LED1( OFF );  
			Delay(1000000);
			LED1( ON );  
			Delay(1000000);
		}

}

