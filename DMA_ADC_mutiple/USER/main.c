/*
 ��ͨ��DMA��ʽ�ɼ�50������
*/

#include "stm32f10x.h"
#include "usart1.h"
#include "adc.h"

extern __IO uint16_t ADC_ConvertedValue[AdcDataLength][AdcChannelNum];

float ADC_ConvertedValueLocal;

void delay(int i);

int main(void)
{	
		int ChannelNum, DataLength; // ��Ϊѭ������
	
		USART1_Config();	 
		ADC1_Init();
	
	  while(1)
		{
		  for(DataLength = 0; DataLength < AdcDataLength; DataLength++)
			{
			  for(ChannelNum = 0; ChannelNum < AdcChannelNum; ChannelNum++)
				{
					ADC_ConvertedValueLocal = (float) ADC_ConvertedValue[DataLength][ChannelNum] / 4096 * 3.3;
					printf("%.2f ", ADC_ConvertedValueLocal);
				}
				printf("\n");
			}
			//delay(7999999);
		}
}

// ��ʱ����
void delay(int i)
{
	for(; i >= 0; i--);
}
