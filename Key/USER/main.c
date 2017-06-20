#include "stm32f10x.h"
#include "led.h"
#include  "key.h"

int main(void)
{	
	/* LED �˿ڳ�ʼ�� */
	LED_GPIO_Config();	
	/* Key �˿ڳ�ʼ�� */
  Key_GPIO_Config();	
 
	while (1)
	{
		if(Key_Scan(GPIOC, GPIO_Pin_3) == KEY_ON)
		{	
		GPIO_WriteBit(GPIOC, GPIO_Pin_1,\
			(BitAction)(1 - GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_1)));
		}
	}

}
