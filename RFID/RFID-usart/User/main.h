#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"
#include <stdio.h>
#include "usart.h"
//#include "IIC.h"
//#include "P8563.h"
//#include "I2C.h"
//#include "i2c_eeprom.h"

//#include "usart.h"


#define MF522_RST_PIN                    GPIO_Pin_2
#define MF522_RST_PORT                   GPIOB
#define MF522_RST_CLK                    RCC_AHBPeriph_GPIOB  
  
#define MF522_MISO_PIN                   GPIO_Pin_13
#define MF522_MISO_PORT                  GPIOB
#define MF522_MISO_CLK                   RCC_AHBPeriph_GPIOB  

#define MF522_MOSI_PIN                   GPIO_Pin_12  
#define MF522_MOSI_PORT                  GPIOB
#define MF522_MOSI_CLK                   RCC_AHBPeriph_GPIOB  

#define MF522_SCK_PIN                    GPIO_Pin_4  
#define MF522_SCK_PORT                   GPIOB
#define MF522_SCK_CLK                    RCC_AHBPeriph_GPIOB 

#define MF522_NSS_PIN                    GPIO_Pin_5  
#define MF522_NSS_PORT                   GPIOB
#define MF522_NSS_CLK                    RCC_AHBPeriph_GPIOB 

//指示灯
#define LED_PIN                          GPIO_Pin_8  
#define LED_PORT                         GPIOB
#define LED_CLK                          RCC_AHBPeriph_GPIOB   

#define RST_H                            GPIO_SetBits(MF522_RST_PORT, MF522_RST_PIN)
#define RST_L                            GPIO_ResetBits(MF522_RST_PORT, MF522_RST_PIN)
#define MOSI_H                           GPIO_SetBits(MF522_MOSI_PORT, MF522_MOSI_PIN)
#define MOSI_L                           GPIO_ResetBits(MF522_MOSI_PORT, MF522_MOSI_PIN)
#define SCK_H                            GPIO_SetBits(MF522_SCK_PORT, MF522_SCK_PIN)
#define SCK_L                            GPIO_ResetBits(MF522_SCK_PORT, MF522_SCK_PIN)
#define NSS_H                            GPIO_SetBits(MF522_NSS_PORT, MF522_NSS_PIN)
#define NSS_L                            GPIO_ResetBits(MF522_NSS_PORT, MF522_NSS_PIN)
#define READ_MISO                        GPIO_ReadInputDataBit(MF522_MISO_PORT, MF522_MISO_PIN)
#define LED_ON                           GPIO_SetBits(LED_PORT, LED_PIN)
#define LED_OFF                          GPIO_ResetBits(LED_PORT, LED_PIN)
/////////////////////////////////////////////////////////////////////
//函数原型
/////////////////////////////////////////////////////////////////////
 

#define TRUE 1
#define FALSE 0

extern void delay(unsigned int dlength);



























#define sEE_WRITE_ADDRESS1        0x00
#define sEE_READ_ADDRESS1         0x00
#define BUFFER_SIZE1             256
#define BUFFER_SIZE2             256
#define sEE_WRITE_ADDRESS2       (sEE_WRITE_ADDRESS1 + BUFFER_SIZE1)
#define sEE_READ_ADDRESS2        (sEE_READ_ADDRESS1 + BUFFER_SIZE1)


//extern uint8_t a8563_Store[7];


//#define touch_shield 0xB4  //Addr接地,mpr121地址的前7位为0x5b,最后一位为零时(写),8位的16进制为0xB4

/* Private macro -------------------------------------------------------------*/
#define countof(a) (sizeof(a) / sizeof(*(a)))
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
