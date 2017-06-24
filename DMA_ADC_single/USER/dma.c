#include  "dma.h"
#include  "usart1.h"

extern uint8_t SendBuff[SENDBUFF_SIZE];

// 中断配置函数
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

// DMA配置函数
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

