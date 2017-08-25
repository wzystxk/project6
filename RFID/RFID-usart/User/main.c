

#include "main.h"
#include "IIC.h"
#include "P8563.h"
#include "data.h"
#include "FM1702.h"
uint8_t temp1[8];
uint8_t temp2[7];
volatile uint16_t NumDataRead = 0;
	
//uint8_t add[]={0x2b,0x2c,0x2d,0x02e,};

static volatile uint32_t TimingDelay; 

volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = FAILED;
//volatile uint16_t NumDataRead = 0;


void Delay(uint32_t nTime);
void GPIO_ini()
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  /* Enable the GPIO Clock */
  RCC_AHBPeriphClockCmd(MF522_RST_CLK, ENABLE);

  /* Configure the GPIO pin */
  GPIO_InitStructure.GPIO_Pin = MF522_RST_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

  GPIO_Init(MF522_RST_PORT, &GPIO_InitStructure);
	
  /* Enable the GPIO Clock */
  RCC_AHBPeriphClockCmd(MF522_MISO_CLK, ENABLE);

  /* Configure the GPIO pin */
  GPIO_InitStructure.GPIO_Pin = MF522_MISO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

  GPIO_Init(MF522_MISO_PORT, &GPIO_InitStructure);
	
  /* Enable the GPIO Clock */
  RCC_AHBPeriphClockCmd(MF522_MOSI_CLK, ENABLE);

  /* Configure the GPIO pin */
  GPIO_InitStructure.GPIO_Pin = MF522_MOSI_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

  GPIO_Init(MF522_MOSI_PORT, &GPIO_InitStructure);
	
  /* Enable the GPIO Clock */
  RCC_AHBPeriphClockCmd(MF522_SCK_CLK, ENABLE);

  /* Configure the GPIO pin */
  GPIO_InitStructure.GPIO_Pin = MF522_SCK_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

  GPIO_Init(MF522_SCK_PORT, &GPIO_InitStructure);
	
  /* Enable the GPIO Clock */
  RCC_AHBPeriphClockCmd(MF522_NSS_CLK, ENABLE);

  /* Configure the GPIO pin */
  GPIO_InitStructure.GPIO_Pin = MF522_NSS_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

  GPIO_Init(MF522_NSS_PORT, &GPIO_InitStructure);
	
  /* Enable the GPIO Clock */
  RCC_AHBPeriphClockCmd(LED_CLK, ENABLE);

  /* Configure the GPIO pin */
  GPIO_InitStructure.GPIO_Pin = LED_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

  GPIO_Init(LED_PORT, &GPIO_InitStructure);
}

void InitializeSystem()
{
	LED_OFF;
	delay(10000);
	Init_FM1702();
	LED_ON;
	delay(50000);	
	LED_OFF;
}
void balance(uint8_t i)
{
	temp1[0]=(temp2[i]/10)+'0';
	temp1[1]=(temp2[i]%10)+'0';
}

int main(void)
{ 
	
	unsigned char status, try;
	unsigned char buf[16];// DefaultKey[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; 

//uint8_t tmpp;
	uint8_t cnt;
	
	SystemInit();
	USART_Configuration();
	
	NVIC_USART_Config();
//	p8563_init();
//	p8563_settime();
//	I2C_EE_Init();
//	mpr121_init();


	GPIO_ini();  
	InitializeSystem( );
	
	
	for(cnt=0;cnt<16;cnt++)
	buf[cnt]=cnt;
	printf(" Init system OK  \n");
	printf(" Printf OK  \n");	
	

	while(1)
	{
		try = 10;
		while(--try)
		{		
	    status = Request(RF_CMD_REQUEST_ALL);		    //Ñ°¿¨
			if(status != FM1702_OK)    continue;
	 
			status = AntiColl();                        //³åÍ»¼ì²â                       
			if(status != FM1702_OK)    continue;

			status=Select_Card();                       //Ñ¡¿¨
			if(status != FM1702_OK)    continue;
	  }
	}
}


void Delay(uint32_t nTime)
{
TimingDelay = nTime;

while(TimingDelay != 0)
{
	TimingDelay--;
};

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


