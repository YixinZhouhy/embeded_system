#include "usart1.h"

uint8_t SendBuff[SENDBUFF_SIZE];

static void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure; 
	
	/* Configure the NVIC Preemption Priority Bits */  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	/* Enable the USARTy Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;	 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

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

/// 配置DMA中断

void DMA_Config(void)
{
		DMA_InitTypeDef  DMA_InitStructure;
		
	  // enable the clock of dma
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
		
		NVIC_Configuration();  // set the exti
		
	  // 保持外设数据寄存器的基地址
		DMA_InitStructure.DMA_PeripheralBaseAddr  = USART1_DR_Base;
		
		//  保持内存地址
		DMA_InitStructure.DMA_MemoryBaseAddr = (u32)SendBuff;
		
	  // 数据传输方向 : 从内存到外设 
		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	
		// 数据传输大小
		DMA_InitStructure.DMA_BufferSize = SENDBUFF_SIZE;
		
		//  外设地址不增
		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
		
		// 内存地址自增
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
		
		// 外设数据单位	
		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
		
		// 内存数据单位
		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
		
		// DMA模式 ： 一次传输， 循环
		DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;	 
		
		// 优先级  : 中
		DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
		
		// 禁止内存到内存的传输
		DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
		
		// configure the channel of dma
		DMA_Init(DMA1_Channel4, &DMA_InitStructure);
		
		// configure the exti 
		DMA_ITConfig(DMA1_Channel4, DMA_IT_TC, ENABLE);
		
		// enable DMA
		DMA_Cmd(DMA1_Channel4, ENABLE);
		

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

