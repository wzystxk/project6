

#include "main.h"
#include "IIC.h"
#include "mpr121.h"



/* Private variables ---------------------------------------------------------*/
//uint8_t Tx1Buffer[]={1,1,0,0,1,1,0xff,2};

//uint8_t Tx2Buffer[]={0x0f,0x0a,0x0f,0x0a,0x0f,0x0a,0x0f,0x0a,0x0f,0x0a,0x0f,0x0a,0x0f,0x0a,0x0f,0x0a,0x0f,0x0a,0x0f,0x0a,0x0f,0x0a,0x0f,0x0a};
//uint8_t Tx3Buffer[]={0x04,0x0c};
uint8_t Tx1Buffer[256];

uint8_t Tx2Buffer[256];

uint8_t Rx1Buffer[256];

uint8_t Rx2Buffer[256];

uint8_t temp1[8];
uint8_t temp2[]="asdfghj";
volatile uint16_t NumDataRead = 0;
	
//uint8_t add[]={0x2b,0x2c,0x2d,0x02e,};

static volatile uint32_t TimingDelay; 

volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = FAILED;
//volatile uint16_t NumDataRead = 0;


void Delay(uint32_t nTime);

static uint8_t get_key()
{
	uint8_t count=0,i=0;
	uint16_t dat;
		dat=read_i2c(touch_shield,0x01)<<8;
		dat=dat| read_i2c(touch_shield,0x00);
	for (i=0; i<12; i++)  //¼ì²âÓÐ¶àÉÙ°´¼ü±»´¥Ãþ
	  {
	    if ((dat & (1<<i)))
	      count++;
	  }
	  i=0;
	  if(count==1){
	  	while((dat & (1<<i)) == 0)
			i++;
			return i;
	  }
	  return 199;
	
}

int main(void)
{ 
	uint8_t key;
	uint16_t us;
	SystemInit();
	USART_Configuration();
	
	NVIC_USART_Config();
//	I2C_EE_Init();
	mpr121_init();
	printf(" Init system OK  \n");
	printf(" Printf OK  \n");

	while(1)
	{
//		SET_DQ();
//		Delay(50);
//		CLR_DQ();
//		Delay(50);
//		SET_CLK();
//		Delay(50);
//		CLR_CLK();
//		mpr121_init();
		if(GET_RQ()==0)
		{
			us++;
//			if(us>1024)
			key=get_key();
			printf("\nKEY=%d\r\n",key);
		}
		printf("\nGET_RQ()=%d\n",GET_RQ());
		if(key!=199){
			temp1[0]=(key/100)+'0';
			temp1[1]=(key%100/10)+'0';
			temp1[2]=(key%10)+'0';
			printf("key=%3s\r\n", temp1);
		}
		key=199;
		Delay(5000);
//	sEE_WriteBuffer(temp1, 0x050, 8);
//		printf("temp1[]=%20s\n", temp1);
//			Delay(5000000);
//	NumDataRead=16;
//	sEE_ReadBuffer(temp2, 0x050,(uint16_t *)(&NumDataRead));
//		if(*temp1 != *temp2)
//		{printf(" Transfer 1 success  \n");	
//			printf("temp2[]=%20s\n", temp2);
//		}
//		else
//	printf(" Transfer 1 Failed  \n");
//			Delay(5000000);
	}
//	uint16_t i;
//// 	RCC_ClocksTypeDef RCC_Clocks;
//// 	/* Configure SysTick IRQ and SysTick Timer to generate interrupts every 500µs */
//// 	RCC_GetClocksFreq(&RCC_Clocks);
//// 	SysTick_Config(RCC_Clocks.HCLK_Frequency / 100);
//	
//	  	for(i=0; i<256; i++)
//		Tx1Buffer[i]=i;	 /* Ìî³äWriteBuffer */
//	  	for(i=0; i<256;i++)
//		Tx2Buffer[i]=i;	 /* Ìî³äWriteBuffer */
//	
//	
//	USART_Configuration();
//	printf("waveshare\r\n");
//  NVIC_USART_Config();
////	I2C_Config();
//	printf(" Transfer 1 FAILED  ");
//	
////for(i=0;i<8;i++)
////	{
////	sEE_WriteBuffer(I2C1,Tx1Buffer, 0x2b, 8);
////	sEE_WaitEepromStandbyState(I2C1);
////	sEE_WriteBuffer(I2C1,Tx2Buffer, 0x41, 24);
////	sEE_WaitEepromStandbyState(I2C1);
////	sEE_WriteBuffer(I2C1,Tx2Buffer, 0x5d, 2);	
////	sEE_WaitEepromStandbyState(I2C1);
//	  /* Write on I2C EEPROM from sEE_WRITE_ADDRESS1 */
////  sEE_WriteBuffer(I2C1,Tx1Buffer, sEE_WRITE_ADDRESS1, BUFFER_SIZE1); 

//  /* Wait for EEPROM standby state */
////  sEE_WaitEepromStandbyState(I2C1);  
//  
//  /* Set the Number of data to be read */
// // NumDataRead = BUFFER_SIZE1;
//  
//  /* Read from I2C EEPROM from sEE_READ_ADDRESS1 */
////  sEE_ReadBuffer(I2C1,Rx1Buffer, sEE_READ_ADDRESS1, (uint16_t *)(&NumDataRead)); 
// 

//  
//  /* Check if the data written to the memory is read correctly */
//// TransferStatus1 = Buffercmp(Tx1Buffer, Rx1Buffer, BUFFER_SIZE1);
//  /* TransferStatus1 = PASSED, if the transmitted and received data 
//     to/from the EEPROM are the same */
//  /* TransferStatus1 = FAILED, if the transmitted and received data 
//     to/from the EEPROM are different */
// 
//  if (TransferStatus1 == PASSED)
//  {
//    printf(" Transfer 1 PASSED  ");   

//  }
//  else
//  {
//    printf(" Transfer 1 FAILED  ");    

//  }  

// 	printf("I2c I2Cx_ISR: 0x%x\r\n",I2C1->ISR);
//  /* Second write in the memory followed by a read of the written data -------*/
//  /* Write on I2C EEPROM from sEE_WRITE_ADDRESS2 */
////  sEE_WriteBuffer(I2C1,Tx2Buffer, sEE_WRITE_ADDRESS2, BUFFER_SIZE2); 

//  /* Wait for EEPROM standby state */
////  sEE_WaitEepromStandbyState(I2C1);  
//  
//  /* Set the Number of data to be read */
////  NumDataRead = BUFFER_SIZE2;  
//  
//  /* Read from I2C EEPROM from sEE_READ_ADDRESS2 */
////  sEE_ReadBuffer(I2C1,Rx2Buffer, sEE_READ_ADDRESS2, (uint16_t *)(&NumDataRead));

//  
//  /* Check if the data written to the memory is read correctly */
//  TransferStatus2 = Buffercmp(Tx2Buffer, Rx2Buffer, BUFFER_SIZE2);
//  /* TransferStatus2 = PASSED, if the transmitted and received data 
//     to/from the EEPROM are the same */
//  /* TransferStatus2 = FAILED, if the transmitted and received data 
//     to/from the EEPROM are different */
// 
//  if (TransferStatus2 == PASSED)
//  {
//    printf(" Transfer 2 PASSED  ");
//  }
//  else
//  {
//    printf(" Transfer 2 FAILED  ");
//  }  

//  
//  /* Free all used resources */
//  
//	
//	while(1)
//	{
//	printf("waveshare\r\n");
//	//	printf("Receive:%d\r\n",USARTFLAG);
//	Delay(100);
//	}
//}		
//TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
//{
//  while(BufferLength--)
//  {
//    if(*pBuffer1 != *pBuffer2)
//    {
//      return FAILED;
//    }
//    
//    pBuffer1++;
//    pBuffer2++;
//  }

//  return PASSED;  
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


