/*
 单通道DMA方式采集50个数据
*/

#include "stm32f10x.h"
#include "usart1.h"
#include "adc.h"

extern __IO uint16_t ADC_ConvertedValue[AdcDataLength];

float ADC_ConvertedValueLocal;

void delay(int i);

int main(void)
{	
		int i;
	
		USART1_Config();	 
		ADC1_Init();
	
	  while(1)
		{
			for(i = 0; i < AdcDataLength; i++)
			{
				ADC_ConvertedValueLocal = (float) ADC_ConvertedValue[i] / 4096 * 3.3;
				printf("%f ", ADC_ConvertedValueLocal);
			}
			delay(7999999);
		}
}

// 延时函数
void delay(int i)
{
	for(; i >= 0; i--);
}
