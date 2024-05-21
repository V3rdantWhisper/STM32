/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ZLG7290_H

#define __ZLG7290_H

#include "stm32f4xx_hal.h"

#define ADDR_ZLG     0x70
#define ZLG_READ_ADDRESS1         0x01
#define ZLG_READ_ADDRESS2         0x10
#define ZLG_WRITE_ADDRESS1        0x10
#define ZLG_WRITE_ADDRESS2        0x11
#define BUFFER_SIZE1              (countof(Tx1_Buffer))
#define BUFFER_SIZE2              (countof(Rx2_Buffer))
#define countof(a) (sizeof(a) / sizeof(*(a)))
#define I2C_PAGESIZE    8

void I2C_ZLG7290_Read(I2C_HandleTypeDef *I2Cx, uint8_t I2C_Addr, uint8_t addr, uint8_t *buf, uint8_t num);

void I2C_ZLG7290_Write(I2C_HandleTypeDef *I2Cx, uint8_t I2C_Addr, uint8_t addr, uint8_t *buf, uint8_t num);


#endif /* __24C64_OPT_H */

/**
* @}
*/

/**
* @}
*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
