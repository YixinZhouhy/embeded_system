#include "stm32f10x.h"
#include "led.h"

void Delay(__IO u32 nCount);

int main(void)
{	
	/* LED �˿ڳ�ʼ�� */
	LED_GPIO_Config();	 
 
	while (1)
	{
		LED1( OFF );  // ��
		Delay(8000000);
		LED1( ON );  // ��
		Delay(8000000);
	}

}

// ��ʱ����
void Delay(__IO uint32_t nCount)  
{
	for(; nCount != 0; nCount--);
}
