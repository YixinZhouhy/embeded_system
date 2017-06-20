#include "stm32f10x.h"
#include "led.h"

void Delay(__IO u32 nCount);

int main(void)
{	
	/* LED 端口初始化 */
	LED_GPIO_Config();	 
 
	while (1)
	{
		LED1( OFF );  // 亮
		Delay(8000000);
		LED1( ON );  // 灭
		Delay(8000000);
	}

}

// 延时函数
void Delay(__IO uint32_t nCount)  
{
	for(; nCount != 0; nCount--);
}
