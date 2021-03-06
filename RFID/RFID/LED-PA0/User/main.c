//#include "ALL_Includes.h"//包含所需的头文件

//void ALL_Config(void);

//void EXTI_Config(void)
//{
//  EXTI_InitTypeDef   EXTI_InitStructure;
//  GPIO_InitTypeDef   GPIO_InitStructure;
//  NVIC_InitTypeDef   NVIC_InitStructure;
//  
//  /* Enable GPIOC clock */
//  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

//  /* Configure PC13 pin as input floating */
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//  GPIO_Init(GPIOC, &GPIO_InitStructure);

//  /* Enable SYSCFG clock */
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
//  
//  /* Connect EXTI13 Line to PC13 pin */
//  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource13);

//  /* Configure EXTI13 line */
//  EXTI_InitStructure.EXTI_Line = EXTI_Line13;
//  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//  EXTI_Init(&EXTI_InitStructure);

//  /* Enable and set EXTI 4-15 Interrupt */
//  NVIC_InitStructure.NVIC_IRQChannel = EXTI4_15_IRQn;
//  NVIC_InitStructure.NVIC_IRQChannelPriority = 0x00;
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStructure);
//}

//void EXTI4_15_IRQHandler(void)
//{
//		if(EXTI_GetITStatus(EXTI_Line13)!=RESET)//判断某个线上的中断是否发生 
//		{
//				EXTI_ClearITPendingBit(EXTI_Line13);
//		}
//}

//int main(void)
//{	
//	ALL_Config();
//	
//	while(1)
//	{
//			LED_ON();
//			delay_ms(80);
//			LED_OFF();
//			delay_ms(80);
//	}
//}

///************************
//函数功能：总初始化
//输入参数：无
//输出参数：无
//备    注：无
//************************/
//void ALL_Config(void)
//{
//    Delay_Init(48);
//		LED_Init();
//		EXTI_Config();
//}








/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/main.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */  

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"
#include <stdio.h>
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_rcc.h"
#include "main.h"
#include "FM1702.h"

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
 USART_InitTypeDef USART_InitStructure;

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

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

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f10x_xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f10x.c file
     */     

 
	unsigned char status, try;
	unsigned char buf[16], DefaultKey[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; 

	GPIO_ini();  
  InitializeSystem( );
	
  while (1)
  {
		try = 5;
		while(--try)
		{		
	    status = Request(RF_CMD_REQUEST_ALL);		    //寻卡
			if(status != FM1702_OK)    continue;
	 
			status = AntiColl();                        //冲突检测                       
			if(status != FM1702_OK)    continue;

			status=Select_Card();                       //选卡
			if(status != FM1702_OK)    continue;

			status = Load_keyE2_CPY(DefaultKey);          //加载密码
			if(status != TRUE)         continue;

			status = Authentication(UID, 1, RF_CMD_AUTH_LA);	  //验证1扇区keyA
      if(status != FM1702_OK)    continue;

			status=MIF_READ(buf,4);							       //读卡，读取1扇区0块数据到buffer[0]-buffer[15]
			//status=MIF_Write(buffer,4);              //写卡，将buffer[0]-buffer[15]写入1扇区0块
			if(status == FM1702_OK)
			{
				//读写成功，点亮LED
				LED_ON;
				delay(50000);
			}
	  }
		if(try == 0)	
			LED_OFF; 
	}
}

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
