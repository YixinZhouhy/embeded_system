#include "adc.h"

__IO uint16_t ADC_ConvertedValue[AdcDataLength][AdcChannelNum];

static void ADC1_GPIO_Config(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		
		// set the clock of DMA
		RCC_AHBPeriphClockCmd( RCC_AHBPeriph_DMA1, ENABLE);
		
    // set the clock of ADC1
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_ADC1 | 
													  RCC_APB2Periph_GPIOC,
														ENABLE);
    // configure the PC_1 and PC_2 (ADC1_IN11 and ADC1_IN12)
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
	
}

static void ADC1_Mode_Config(void)
{
		DMA_InitTypeDef DMA_InitStructure;
		ADC_InitTypeDef ADC_InitStructure;
		
		// DMA channel1 configuration
		// ����ʼ��DMAĬ������
		DMA_DeInit(DMA1_Channel1);
	
		// DMAԴ��ַ
		DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;
	
		// �ڴ��ַ
	  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADC_ConvertedValue;
	
	  // ���ݷ��� : ���赽�ڴ� 
		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	
		// ���ݴ����С
	  DMA_InitStructure.DMA_BufferSize = AdcChannelNum * AdcDataLength;
	
	  // �����ַ�Ƿ����� �� ��
		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
		
		// �ڴ��ַ�Ƿ����� �� ��
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
		
		// �������ݵ�Ԫ��С : ����
		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
		
		// �ڴ����ݵ�Ԫ��С ������
		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
		
		// ģʽ ��ѭ��ģʽ
		DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
		
		// ���ȼ� �� ��
		DMA_InitStructure.DMA_Priority = DMA_Priority_High;
		
		// �Ƿ��ڴ浽�ڴ洫�� �� ��
		DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
		
		DMA_Init(DMA1_Channel1, &DMA_InitStructure);
		DMA_Cmd(DMA1_Channel1, ENABLE);
		
		// ADC configuration
		// ADC ģʽ
		
		ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
		
		// �Ƿ���ɨ��ģʽ : �� ɨ��ģʽ���ڶ�ͨ���ɼ�
		ADC_InitStructure.ADC_ScanConvMode = ENABLE;
		
		// �Ƿ�������ת��ģʽ ����
		ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
		
		// �Ƿ�ʹ���ⲿ����ת��
		ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
		
		// ���ݶ��뷽ʽ �� �Ҷ���
		ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
		
		// ����ת����ͨ����
		ADC_InitStructure.ADC_NbrOfChannel = AdcChannelNum;
		
		ADC_Init(ADC1, &ADC_InitStructure);
		
		//ADC_TempSensorVrefintCmd(ENABLE);
		
		// ����ADCʱ��
		RCC_ADCCLKConfig(RCC_PCLK2_Div8);
		
		// ���ò�������
		ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 1, ADC_SampleTime_55Cycles5);
		ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 2, ADC_SampleTime_55Cycles5);
		
		// ʹ��ADC1 DMA
		ADC_DMACmd(ADC1, ENABLE);
		
		// ʹ�� ADC1
		ADC_Cmd(ADC1, ENABLE);
	
		
		// ��λУ׼�Ĵ���
		ADC_ResetCalibration(ADC1);
		
		// �ȴ�У׼�Ĵ�����λ���
		while(ADC_GetResetCalibrationStatus(ADC1));
		
		// ADCУ׼
		ADC_StartCalibration(ADC1);
		
		// �ȴ�У׼���
		while(ADC_GetCalibrationStatus(ADC1));
		
		// �������ADCת��
		ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}



void ADC1_Init(void)
{
		ADC1_GPIO_Config();
		ADC1_Mode_Config();	
}





