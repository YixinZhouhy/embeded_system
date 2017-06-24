#include "stm32f10x.h"
#include "led.h"

void Delay(__IO u32 nCount);

int main(void)
{	
	SystemInit();
	
	/* LED �˿ڳ�ʼ�� */
	LED_GPIO_Config();	 
 
	while (1)
	{
		LED1( OFF );  // ��
		Delay(72000000);
		LED1( ON );  // ��
		Delay(72000000);
	}

}

// ��ʱ����
void Delay(__IO uint32_t nCount)  
{
	for(; nCount != 0; nCount--);
}
