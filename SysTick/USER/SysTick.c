#include "SysTick.h"

static __IO u32 TimingDelay;

void SysTick_Init(void)
{
//		SystemFrequency / 1000    1ms  中断一次
//		SystemFrequency / 10000   10us 中断一次
//	  SystemFrequency / 100000  1us 中断一次
	
		if(SysTick_Config(72))
		{
			while(1);
		}
		// close the systick
		SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
}

// 延时函数
void Delay(__IO u32 nTime)
{ 
		TimingDelay = nTime;	

		// 使能滴答定时器  
		SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;

		while(TimingDelay != 0);
}

// 获取节拍函数
void TimingDelay_Decrement(void)
{
		if (TimingDelay != 0x00)
		{ 
			TimingDelay--;
		}
}
