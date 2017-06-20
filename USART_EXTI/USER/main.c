#include "stm32f10x.h"
#include "led.h"
#include "usart1.h"


int main(void)
{	
		LED_GPIO_Config();
		USART1_Config();
	
		while(1)
		{
			// printf("\r\nyixinzhou\r\n");
			delay(16000000);
		}
}

