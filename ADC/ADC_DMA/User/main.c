
#include "main.h"

#define ADC1_DR_Address    0x40012440

static volatile uint32_t TimingDelay; 
__IO uint16_t RegularConvData_Tab[5]={0};
	float AD1=0,AD2=0,AD3=0,AD4=0,AD5=0;

void Delay(uint32_t nTime);

int main(void)
{ 

	RCC_ClocksTypeDef RCC_Clocks;
	/* Configure SysTick IRQ and SysTick Timer to generate interrupts every 500µs */
	RCC_GetClocksFreq(&RCC_Clocks);
	SysTick_Config(RCC_Clocks.HCLK_Frequency / 100);
	
	USART_Configuration();
	ADC1_Config();
	DMA_Config();

	
	while(1)
	{
    /* Test DMA1 TC flag */
    while((DMA_GetFlagStatus(DMA1_FLAG_TC1)) == RESET ); 
    
    /* Clear DMA TC flag */
    DMA_ClearFlag(DMA1_FLAG_TC1);
		
//		printf("RegularConvData_Tab0=%x, \r\n",RegularConvData_Tab[0]);
		printf("The VBAT is=%x, \r\n",RegularConvData_Tab[1]);
//		printf("RegularConvData_Tab2=%x, \r\n",RegularConvData_Tab[2]);
//		printf("RegularConvData_Tab3=%x, \r\n",RegularConvData_Tab[3]);
//   printf("RegularConvData_Tab4=%x, \r\n",RegularConvData_Tab[4]);		
//	  printf("waveshare\r\n");
	//	printf("Receive:%d\r\n",USARTFLAG);
		AD1=(float)RegularConvData_Tab[0];
		AD2=(float)RegularConvData_Tab[1];
		AD3=(float)RegularConvData_Tab[2];
		AD4=(float)RegularConvData_Tab[3];
		AD5=(float)RegularConvData_Tab[4];
//		AD2=(float)RegularConvData_Tab[1];
//		printf("AD1=%f, \r\n",AD1);
		printf("AD2=%f, \r\n",AD2*6.6/0xfff);
//		printf("AD3=%f, \r\n",AD3);
//		printf("AD4=%f, \r\n",AD4);
//		printf("AD5=%f, \r\n",AD5);
//		printf("AD2=%f, \r\n",AD2);
	Delay(100);
	}
}		
void ADC1_Config(void)
{
	ADC_InitTypeDef     ADC_InitStructure;
  GPIO_InitTypeDef    GPIO_InitStructure;	
  /* ADC1 DeInit */  
  ADC_DeInit(ADC1);
	 /* GPIOC Periph clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
  
   /* ADC1 Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	/* Configure ADC Channel11 as analog input */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	  /* ADC DMA request in circular mode */
  ADC_DMARequestModeConfig(ADC1, ADC_DMAMode_Circular);
  
  /* Enable ADC_DMA */
  ADC_DMACmd(ADC1, ENABLE);  
  
  /* Initialize ADC structure */
  ADC_StructInit(&ADC_InitStructure);
  
  /* Configure the ADC1 in continous mode withe a resolutuion equal to 12 bits  */
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; 
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Backward;
  ADC_Init(ADC1, &ADC_InitStructure); 

  /* Convert the ADC1 Channel 1 with 55.5 Cycles as sampling time */ 
  ADC_ChannelConfig(ADC1, ADC_Channel_0 , ADC_SampleTime_55_5Cycles);   
	ADC_ChannelConfig(ADC1, ADC_Channel_1 , ADC_SampleTime_55_5Cycles);   
  
 
  
  /* Convert the ADC1 temperature sensor  with 55.5 Cycles as sampling time */ 
  ADC_ChannelConfig(ADC1, ADC_Channel_TempSensor , ADC_SampleTime_55_5Cycles);  
  ADC_TempSensorCmd(ENABLE);
  
  /* Convert the ADC1 Vref  with 55.5 Cycles as sampling time */ 
  ADC_ChannelConfig(ADC1, ADC_Channel_Vrefint , ADC_SampleTime_55_5Cycles); 
  ADC_VrefintCmd(ENABLE);
  
  /* Convert the ADC1 Vbat with 55.5 Cycles as sampling time */ 
  ADC_ChannelConfig(ADC1, ADC_Channel_Vbat , ADC_SampleTime_55_5Cycles);  
  ADC_VbatCmd(ENABLE);
  
  /* ADC Calibration */
  ADC_GetCalibrationFactor(ADC1);
  
  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);     
  
  /* Wait the ADCEN falg */
  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADEN)); 
  
  /* ADC1 regular Software Start Conv */ 
  ADC_StartOfConversion(ADC1);
 
}
void DMA_Config()
{
	DMA_InitTypeDef   DMA_InitStructure;
	  /* DMA1 clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1 , ENABLE);
  
	  /* DMA1 Channel1 Config */
  DMA_DeInit(DMA1_Channel1);
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC1_DR_Address;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)RegularConvData_Tab;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = 5;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel1, &DMA_InitStructure);
  /* DMA1 Channel1 enable */
  DMA_Cmd(DMA1_Channel1, ENABLE);


}
void Delay(uint32_t nTime)
{
TimingDelay = nTime;

while(TimingDelay != 0);

}

/**
* @brief  Decrements the TimingDelay variable.
* @param  None
* @retval None
*/
void TimingDelay_Decrement(void)
{

if (TimingDelay != 0x00)
{ 
TimingDelay--;
}

}


