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
		// 不初始化DMA默认配置
		DMA_DeInit(DMA1_Channel1);
	
		// DMA源地址
		DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;
	
		// 内存地址
	  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADC_ConvertedValue;
	
	  // 数据方向 : 外设到内存 
		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	
		// 数据传输大小
	  DMA_InitStructure.DMA_BufferSize = AdcChannelNum * AdcDataLength;
	
	  // 外设地址是否自增 ： 否
		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
		
		// 内存地址是否自增 ： 否
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
		
		// 外设数据单元大小 : 半字
		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
		
		// 内存数据单元大小 ：半字
		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
		
		// 模式 ：循环模式
		DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
		
		// 优先级 ： 高
		DMA_InitStructure.DMA_Priority = DMA_Priority_High;
		
		// 是否内存到内存传输 ： 否
		DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
		
		DMA_Init(DMA1_Channel1, &DMA_InitStructure);
		DMA_Cmd(DMA1_Channel1, ENABLE);
		
		// ADC configuration
		// ADC 模式
		
		ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
		
		// 是否开启扫描模式 : 否 扫描模式用于多通道采集
		ADC_InitStructure.ADC_ScanConvMode = ENABLE;
		
		// 是否开启连续转换模式 ：是
		ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
		
		// 是否使用外部触发转换
		ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
		
		// 数据对齐方式 ： 右对齐
		ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
		
		// 数据转换的通道数
		ADC_InitStructure.ADC_NbrOfChannel = AdcChannelNum;
		
		ADC_Init(ADC1, &ADC_InitStructure);
		
		//ADC_TempSensorVrefintCmd(ENABLE);
		
		// 配置ADC时钟
		RCC_ADCCLKConfig(RCC_PCLK2_Div8);
		
		// 配置采样周期
		ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 1, ADC_SampleTime_55Cycles5);
		ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 2, ADC_SampleTime_55Cycles5);
		
		// 使能ADC1 DMA
		ADC_DMACmd(ADC1, ENABLE);
		
		// 使能 ADC1
		ADC_Cmd(ADC1, ENABLE);
	
		
		// 复位校准寄存器
		ADC_ResetCalibration(ADC1);
		
		// 等待校准寄存器复位完成
		while(ADC_GetResetCalibrationStatus(ADC1));
		
		// ADC校准
		ADC_StartCalibration(ADC1);
		
		// 等待校准完成
		while(ADC_GetCalibrationStatus(ADC1));
		
		// 软件触发ADC转换
		ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}



void ADC1_Init(void)
{
		ADC1_GPIO_Config();
		ADC1_Mode_Config();	
}





