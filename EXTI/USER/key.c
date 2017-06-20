#include "key.h"
#include "led.h"

/* key 配置 */
void Key_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	// 配置PC3时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	// 选择引脚
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	
	// 配置引脚模式
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/* 检测是否有按键按下函数 */
u8 Key_Scan(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	//
	if(GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == KEY_ON)
	{
		Delay(11000);
		if(GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == KEY_ON)
		{
			while(GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == KEY_ON);
				return KEY_ON;
		}
		else
			return KEY_OFF;
		
	}
	else
		return KEY_OFF;
}
