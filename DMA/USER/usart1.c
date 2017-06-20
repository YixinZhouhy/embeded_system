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
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  // �����������
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	
		// configure usart1_rx
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; // ��������
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	
		// configure the mode of usart1
		USART_InitStructure.USART_BaudRate = 115200; // ������
		USART_InitStructure.USART_WordLength = USART_WordLength_8b; // ����λ
		USART_InitStructure.USART_StopBits = USART_StopBits_1; // ֹͣλ
		USART_InitStructure.USART_Parity = USART_Parity_No;  // ��żУ��λ
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // Ӳ��������
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; // ���ô���ģʽ
		USART_Init(USART1, &USART_InitStructure); // ��Ĵ���д�����ò���
		USART_Cmd(USART1, ENABLE); // ʹ��usart1����
}

/// ����DMA�ж�

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

// �ض���c�⺯��printf��USART1
int fputc(int ch, FILE *f)
{
		// ����һ���ֽ����ݵ�USART1 
		USART_SendData(USART1, (uint8_t) ch);
		
		// �ȴ�������� 
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);		
			
		return (ch);
}

// �ض���c�⺯��scanf��USART1
int fgetc(FILE *f)
{
		// �ȴ�����1�������� 
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USART1);
}

