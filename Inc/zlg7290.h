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



enum
{
    ZLG7290_WRITE_ADDR = 0x70,
    ZLG7290_READ_ADDR  = 0x71,
};

enum
{
    ZLG7290_ADDR_SYSREG     = 0x00,
    ZLG7290_ADDR_KEY        = 0x01,
    ZLG7920_ADDR_REPCNT     = 0x02,
    ZLG7290_ADDR_FUNCKEY    = 0x03,
    ZLG7290_ADDR_CMDBUF0    = 0x07,
    ZLG7290_ADDR_CMDBUF1    = 0x08,
    ZLG7290_ADDR_FLASH      = 0x0C,
    ZLG7290_ADDR_SCANNUM    = 0x0D,
    ZLG7290_ADDR_DPRAM0     = 0x10,
    ZLG7290_ADDR_DPRAM1     = 0x11,
    ZLG7290_ADDR_DPRAM2     = 0x12,
    ZLG7290_ADDR_DPRAM3     = 0x13,
    ZLG7290_ADDR_DPRAM4     = 0x14,
    ZLG7290_ADDR_DPRAM5     = 0x15,
    ZLG7290_ADDR_DPRAM6     = 0x16,
    ZLG7290_ADDR_DPRAM7     = 0x17,
};

enum
{
    ZLG7290_KEY_0       = 0x03,
    ZLG7290_KEY_1       = 0x1C,
    ZLG7290_KEY_2       = 0x1B,
    ZLG7290_KEY_3       = 0x1A,
    ZLG7290_KEY_4       = 0x14,
    ZLG7290_KEY_5       = 0x13,
    ZLG7290_KEY_6       = 0x12,
    ZLG7290_KEY_7       = 0x0C,
    ZLG7290_KEY_8       = 0x0B,
    ZLG7290_KEY_9       = 0x0A,
    ZLG7290_KEY_A       = 0x19,
    ZLG7290_KEY_B       = 0x11,
    ZLG7290_KEY_C       = 0x09,
    ZLG7290_KEY_D       = 0x01,
    ZLG7290_KEY_STAR    = 0x04,
    ZLG7290_KEY_POUND   = 0x02,
};

enum
{
    ZLG7290_DISPLAY_DOT         = 1 << 0,
    ZLG7290_DISPLAY_MIDDLE      = 1 << 1,
    ZLG7290_DISPLAY_LEFTTOP     = 1 << 2,
    ZLG7290_DISPLAY_LEFTBOTTOM  = 1 << 3,
    ZLG7290_DISPLAY_BOTTOM      = 1 << 4,
    ZLG7290_DISPLAY_RIGHTBOTTOM = 1 << 5,
    ZLG7290_DISPLAY_RIGHTTOP    = 1 << 6,
    ZLG7290_DISPLAY_TOP         = 1 << 7,
    ZLG7290_DISPLAY_ALL         = 0xFF,

    ZLG7290_DISPLAY_NUM0    = ZLG7290_DISPLAY_ALL & ~ZLG7290_DISPLAY_DOT & ~ZLG7290_DISPLAY_MIDDLE,
    ZLG7290_DISPLAY_NUM1    = ZLG7290_DISPLAY_LEFTTOP | ZLG7290_DISPLAY_LEFTBOTTOM,
    ZLG7290_DISPLAY_NUM2    = ZLG7290_DISPLAY_ALL & ~ZLG7290_DISPLAY_DOT & ~ZLG7290_DISPLAY_LEFTTOP & ~ZLG7290_DISPLAY_RIGHTBOTTOM,
    ZLG7290_DISPLAY_NUM3    = ZLG7290_DISPLAY_ALL & ~ZLG7290_DISPLAY_DOT & ~ZLG7290_DISPLAY_LEFTTOP & ~ZLG7290_DISPLAY_LEFTBOTTOM,
    ZLG7290_DISPLAY_NUM4    = ZLG7290_DISPLAY_LEFTTOP | ZLG7290_DISPLAY_MIDDLE | ZLG7290_DISPLAY_RIGHTTOP | ZLG7290_DISPLAY_RIGHTBOTTOM,
    ZLG7290_DISPLAY_NUM5    = ZLG7290_DISPLAY_ALL & ~ZLG7290_DISPLAY_DOT & ~ZLG7290_DISPLAY_LEFTBOTTOM & ~ZLG7290_DISPLAY_RIGHTTOP,
    ZLG7290_DISPLAY_NUM6    = ZLG7290_DISPLAY_ALL & ~ZLG7290_DISPLAY_DOT & ~ZLG7290_DISPLAY_RIGHTTOP,
    ZLG7290_DISPLAY_NUM7    = ZLG7290_DISPLAY_TOP | ZLG7290_DISPLAY_RIGHTTOP | ZLG7290_DISPLAY_RIGHTBOTTOM,
    ZLG7290_DISPLAY_NUM8    = ZLG7290_DISPLAY_ALL & ~ZLG7290_DISPLAY_DOT,
    ZLG7290_DISPLAY_NUM9    = ZLG7290_DISPLAY_ALL & ~ZLG7290_DISPLAY_DOT & ~ZLG7290_DISPLAY_LEFTBOTTOM,
};



/*
 * Function Arena
 * */
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
