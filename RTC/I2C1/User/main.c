

#include "main.h"
//#include "IIC.h"
#include "P8563.h"
#include "data.h"
//#include "mpr121.h"



/* Private variables ---------------------------------------------------------*/
//uint8_t Tx1Buffer[]={1,1,0,0,1,1,0xff,2};

//uint8_t Tx2Buffer[]={0x0f,0x0a,0x0f,0x0a,0x0f,0x0a,0x0f,0x0a,0x0f,0x0a,0x0f,0x0a,0x0f,0x0a,0x0f,0x0a,0x0f,0x0a,0x0f,0x0a,0x0f,0x0a,0x0f,0x0a};
//uint8_t Tx3Buffer[]={0x04,0x0c};



//uint8_t Tx1Buffer[256];

//uint8_t Tx2Buffer[256];

//uint8_t Rx1Buffer[256];

//uint8_t Rx2Buffer[256];

uint8_t temp1[8];
uint8_t temp2[7];
volatile uint16_t NumDataRead = 0;
	
//uint8_t add[]={0x2b,0x2c,0x2d,0x02e,};

static volatile uint32_t TimingDelay; 

volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = FAILED;
//volatile uint16_t NumDataRead = 0;


void Delay(uint32_t nTime);



void balance(uint8_t i)
{
	temp1[0]=(temp2[i]/10)+'0';
	temp1[1]=(temp2[i]%10)+'0';
}

int main(void)
{ 
	
//	uint8_t key;
//	uint16_t us;
	uint8_t i;
	
	SystemInit();
	USART_Configuration();
	
	NVIC_USART_Config();
	p8563_init();
	p8563_settime();
	printf(" Init system OK  \n");
	printf(" Printf OK  \n");
	while(1)
	{
		p8563_gettime();
		printf("The Time Is");
		for(i=0;i<7;i++)
		temp2[i]=transmit(i);
		for(i=0;i<7;i++)
		{
			balance(i);
			printf("%3s ", temp1);
		}
		printf("now\r\n");
		Delay(900000);
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


