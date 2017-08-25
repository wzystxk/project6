#ifndef __I2C_H
#define __I2C_H
#include "stm32f0xx.h"

#include <stdio.h>
#define sEE_I2C_TIMING          0x00210507
#define sEE_M24C08

#if defined (sEE_M24C08)
 #define sEE_PAGESIZE           16
#elif defined (sEE_M24C64_32)
 #define sEE_PAGESIZE           32
#elif defined (sEE_M24LR64)
 #define sEE_PAGESIZE           8
#endif

#define sEE_MAX_TRIALS_NUMBER     300

#define sEE_OK                    0
#define sEE_FAIL                  1   

#define sEE_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define sEE_LONG_TIMEOUT         ((uint32_t)(10 * sEE_FLAG_TIMEOUT))
#define sEE_HW_ADDRESS            0xA0   /* E2 = 0 */ 
 /*#define sEE_HW_ADDRESS     0xA2*/ /* E2 = 0 */  
 /*#define sEE_HW_ADDRESS     0xA4*/ /* E2 = 0 */
 /*#define sEE_HW_ADDRESS     0xA6*/ /* E2 = 0 */


void I2C_Config(void);
uint32_t sEE_ReadBuffer(I2C_TypeDef *I2Cx,uint8_t* pBuffer, uint16_t ReadAddr, uint16_t* NumByteToRead);
uint32_t sEE_WritePage(I2C_TypeDef  *I2Cx, uint8_t* pBuffer, uint16_t WriteAddr, uint8_t* NumByteToWrite);
void sEE_WriteBuffer(I2C_TypeDef  *I2Cx,uint8_t* pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite);
uint32_t sEE_WaitEepromStandbyState(I2C_TypeDef  *I2Cx);
uint32_t sEE_TIMEOUT_UserCallback(void);
//write_i2c(I2C_TypeDef  *I2Cx,uint8_t addr,uint8_t dat);


#endif /* __USART_H */

