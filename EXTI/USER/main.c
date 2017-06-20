#include "stm32f10x.h"
#include "led.h"
#include "key.h"
#include "EXTI_PC3_Config.h" 

int main(void)
{	
	
	LED_GPIO_Config();  // configure the LED 
  Key_GPIO_Config();	// configure the Key port
	LED1(ON);
	EXTI_PC3_Config();  // configure exti line 
	while (1)
	{
	}
}
