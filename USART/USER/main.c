#include "stm32f10x.h"
#include "led.h"
#include "usart1.h"

void delay(__IO u32 nCount);
char * s_gets(char * st, int n);

int main(void)
{	
		USART1_Config();
		
		while(1)
		{
			printf("\r\nyixinzhou\r\n");
			delay(1000);
		}
}

// ÑÓÊ±º¯Êý
void delay(__IO uint32_t nCount)  
{
	  for(; nCount != 0; nCount--);
}
