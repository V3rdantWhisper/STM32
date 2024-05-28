#include "zlg7290.h"

/* Maximum Timeout values for flags and events waiting loops. These timeouts are
not based on accurate values, they just guarantee that the application will 
not remain stuck if the I2C communication is corrupted.
You may modify these timeout values depending on CPU frequency and application
conditions (interrupts routines ...). */   
#define I2C_Open_FLAG_TIMEOUT         ((uint32_t)0x1000)

#define I2C_Open_LONG_TIMEOUT         ((uint32_t)0xffff)

__IO uint32_t  I2CTimeout = I2C_Open_LONG_TIMEOUT;


/*******************************************************************************
* Function Name  : I2C_24C64_Read
* Description    : 
* Input          : 
* Output         : 
* Return         : 
* Attention      : None
*******************************************************************************/

__IO  uint32_t ZLG7290_I2C_Timeout = I2C_Open_LONG_TIMEOUT;
__IO  uint32_t ZLG7290_I2C_Retries = 5;

void ZLG7290_Set_Timeout(uint32_t timeout)
{
    ZLG7290_I2C_Timeout = timeout;
}

void ZLG7290_Set_Retries(uint32_t retries)
{
    ZLG7290_I2C_Retries = retries;
}

HAL_StatusTypeDef ZLG7290_Read(I2C_HandleTypeDef* hi2c, uint16_t addr, uint8_t* buf, uint16_t bufsz)
{
    HAL_StatusTypeDef status = HAL_OK;
    for (uint32_t i = 0; i < ZLG7290_I2C_Retries; ++i)
    {
        status = HAL_I2C_Mem_Read(hi2c, ZLG7290_READ_ADDR, addr, I2C_MEMADD_SIZE_8BIT, buf, bufsz, ZLG7290_I2C_Timeout);
        if (status == HAL_OK)
            break;
    }
    return status;
}

static HAL_StatusTypeDef ZLG7290_WriteByte(I2C_HandleTypeDef* hi2c, uint16_t addr, uint8_t* buf)
{
    return HAL_I2C_Mem_Write(hi2c, ZLG7290_WRITE_ADDR, addr, I2C_MEMADD_SIZE_8BIT, buf, 1, ZLG7290_I2C_Timeout);
}

HAL_StatusTypeDef ZLG7290_Write(I2C_HandleTypeDef* hi2c, uint16_t addr, uint8_t* buf, uint16_t bufsz)
{
    HAL_StatusTypeDef status = HAL_OK;
    for (uint32_t i = 0; i < ZLG7290_I2C_Retries; ++i)
    {
        for (uint32_t j = 1; j <= bufsz; ++j)
        {
            status |= ZLG7290_WriteByte(hi2c, addr + bufsz - j, buf + bufsz - j);
            HAL_Delay(5);
        }
        if (status == HAL_OK)
            break;
    }
    return status;
}


/**
* @}
*/

/**
* @}
*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
