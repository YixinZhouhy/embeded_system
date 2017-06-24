#include "usart1.h"

uint8_t SendBuff[SENDBUFF_SIZE];

void USART1_Config(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
	
	  // configure the clock of usart1
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | \
													 RCC_APB2Periph_GPIOA,
													 ENABLE);
	
		// usart gpio configuration
	  // configure usart1_tx
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  // 复用推挽输出
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	
		// configure usart1_rx
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; // 浮空输入
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	
		// configure the mode of usart1
		USART_InitStructure.USART_BaudRate = 115200; // 波特率
		USART_InitStructure.USART_WordLength = USART_WordLength_8b; // 数据位
		USART_InitStructure.USART_StopBits = USART_StopBits_1; // 停止位
		USART_InitStructure.USART_Parity = USART_Parity_No;  // 奇偶校验位
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 硬件流控制
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; // 配置串口模式
		USART_Init(USART1, &USART_InitStructure); // 向寄存器写入配置参数
		USART_Cmd(USART1, ENABLE); // 使能usart1外设
}


// 重定向c库函数printf到USART1
int fputc(int ch, FILE *f)
{
		// 发送一个字节数据到USART1 
		USART_SendData(USART1, (uint8_t) ch);
		
		// 等待发送完毕 
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);		
			
		return (ch);
}

// 重定向c库函数scanf到USART1
int fgetc(FILE *f)
{
		// 等待串口1输入数据 
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USART1);
}

