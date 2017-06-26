#include "SysTick.h"

static __IO u32 TimingDelay;

void SysTick_Init(void)
{
//		SystemFrequency / 1000    1ms  �ж�һ��
//		SystemFrequency / 10000   10us �ж�һ��
//	  SystemFrequency / 100000  1us �ж�һ��
	
		if(SysTick_Config(72))
		{
			while(1);
		}
		// close the systick
		SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
}

// ��ʱ����
void Delay(__IO u32 nTime)
{ 
		TimingDelay = nTime;	

		// ʹ�ܵδ�ʱ��  
		SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;

		while(TimingDelay != 0);
}

// ��ȡ���ĺ���
void TimingDelay_Decrement(void)
{
		if (TimingDelay != 0x00)
		{ 
			TimingDelay--;
		}
}
