#include  "dma.h"
#include  "usart1.h"

extern uint8_t SendBuff[SENDBUFF_SIZE];

// �ж����ú���
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

// DMA���ú���
void DMA_Config(void)
{
		DMA_InitTypeDef  DMA_InitStructure;
		
	  // enable the clock of dma
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
		
		NVIC_Configuration();  // set the exti
		
	  // �����������ݼĴ����Ļ���ַ
		DMA_InitStructure.DMA_PeripheralBaseAddr  = USART1_DR_Base;
		
		//  �����ڴ��ַ
		DMA_InitStructure.DMA_MemoryBaseAddr = (u32)SendBuff;
		
	  // ���ݴ��䷽�� : ���ڴ浽���� 
		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	
		// ���ݴ����С
		DMA_InitStructure.DMA_BufferSize = SENDBUFF_SIZE;
		
		//  �����ַ����
		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
		
		// �ڴ��ַ����
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
		
		// �������ݵ�λ	
		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
		
		// �ڴ����ݵ�λ
		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
		
		// DMAģʽ �� һ�δ��䣬 ѭ��
		DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;	 
		
		// ���ȼ�  : ��
		DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
		
		// ��ֹ�ڴ浽�ڴ�Ĵ���
		DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
		
		// configure the channel of dma
		DMA_Init(DMA1_Channel4, &DMA_InitStructure);
		
		// configure the exti 
		DMA_ITConfig(DMA1_Channel4, DMA_IT_TC, ENABLE);
		
		// enable DMA
		DMA_Cmd(DMA1_Channel4, ENABLE);
}

