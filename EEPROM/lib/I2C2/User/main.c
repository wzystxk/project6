

#include "main.h"



/* Private variables ---------------------------------------------------------*/
uint8_t Tx1Buffer[256];

uint8_t Tx2Buffer[256];

uint8_t Rx1Buffer[256];

uint8_t Rx2Buffer[256];

static volatile uint32_t TimingDelay; 

volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = FAILED;
volatile uint16_t NumDataRead = 0;


void Delay(uint32_t nTime);
int main(void)
{ 
	uint16_t i;
// 	RCC_ClocksTypeDef RCC_Clocks;
// 	/* Configure SysTick IRQ and SysTick Timer to generate interrupts every 500µs */
// 	RCC_GetClocksFreq(&RCC_Clocks);
// 	SysTick_Config(RCC_Clocks.HCLK_Frequency / 100);
	
	  	for(i=0; i<256; i++)
		Tx1Buffer[i]=i;	 /* Ìî³äWriteBuffer */
	  	for(i=0; i<256;i++)
		Tx2Buffer[i]=i;	 /* Ìî³äWriteBuffer */
	
	
	USART_Configuration();
	printf("waveshare\r\n");
  NVIC_USART_Config();
	I2C_Config();
	printf(" Transfer 1 FAILED  ");    
	  /* Write on I2C EEPROM from sEE_WRITE_ADDRESS1 */
  sEE_WriteBuffer(I2C2,Tx1Buffer, sEE_WRITE_ADDRESS1, BUFFER_SIZE1); 

  /* Wait for EEPROM standby state */
  sEE_WaitEepromStandbyState(I2C2);  
  
  /* Set the Number of data to be read */
  NumDataRead = BUFFER_SIZE1;
  
  /* Read from I2C EEPROM from sEE_READ_ADDRESS1 */
  sEE_ReadBuffer(I2C2,Rx1Buffer, sEE_READ_ADDRESS1, (uint16_t *)(&NumDataRead)); 
 

  
  /* Check if the data written to the memory is read correctly */
  TransferStatus1 = Buffercmp(Tx1Buffer, Rx1Buffer, BUFFER_SIZE1);
  /* TransferStatus1 = PASSED, if the transmitted and received data 
     to/from the EEPROM are the same */
  /* TransferStatus1 = FAILED, if the transmitted and received data 
     to/from the EEPROM are different */
 
  if (TransferStatus1 == PASSED)
  {
    printf(" Transfer 1 PASSED  ");   

  }
  else
  {
    printf(" Transfer 1 FAILED  ");    

  }  

 	printf("I2c I2Cx_ISR: 0x%x\r\n",I2C1->ISR);
  /* Second write in the memory followed by a read of the written data -------*/
  /* Write on I2C EEPROM from sEE_WRITE_ADDRESS2 */
  sEE_WriteBuffer(I2C2,Tx2Buffer, sEE_WRITE_ADDRESS2, BUFFER_SIZE2); 

  /* Wait for EEPROM standby state */
  sEE_WaitEepromStandbyState(I2C2);  
  
  /* Set the Number of data to be read */
  NumDataRead = BUFFER_SIZE2;  
  
  /* Read from I2C EEPROM from sEE_READ_ADDRESS2 */
  sEE_ReadBuffer(I2C2,Rx2Buffer, sEE_READ_ADDRESS2, (uint16_t *)(&NumDataRead));

  
  /* Check if the data written to the memory is read correctly */
  TransferStatus2 = Buffercmp(Tx2Buffer, Rx2Buffer, BUFFER_SIZE2);
  /* TransferStatus2 = PASSED, if the transmitted and received data 
     to/from the EEPROM are the same */
  /* TransferStatus2 = FAILED, if the transmitted and received data 
     to/from the EEPROM are different */
 
  if (TransferStatus2 == PASSED)
  {
    printf(" Transfer 2 PASSED  ");
  }
  else
  {
    printf(" Transfer 2 FAILED  ");
  }  

  
  /* Free all used resources */
  
	
	while(1)
	{
	printf("waveshare\r\n");
	//	printf("Receive:%d\r\n",USARTFLAG);
	Delay(100);
	}
}		
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
  while(BufferLength--)
  {
    if(*pBuffer1 != *pBuffer2)
    {
      return FAILED;
    }
    
    pBuffer1++;
    pBuffer2++;
  }

  return PASSED;  
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


