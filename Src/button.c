//
// Created by nemo on 5/21/24.
//
/* USER CODE BEGIN 4 */
#include "zlg7290.h"
#include "i2c.h"
#include "usart.h"

#define countof(a) (sizeof(a) / sizeof(*(a)))

uint8_t flag;//不同的按键有不同的标志位值
uint8_t flag1 = 0;//中断标志位，每次按键产生一次中断，并开始读取8个数码管的值
uint8_t Rx2_Buffer[8] = {0};
uint8_t Tx1_Buffer[8] = {0};
uint8_t Rx1_Buffer[1] = {0};

void swtich_key(void) {
    switch (Rx1_Buffer[0]) {
        case 0x1C:
            flag = 1;
            break;
        case 0x1B:
            flag = 2;
            break;
        case 0x1A:
            flag = 3;
            break;
        case 0x14:
            flag = 4;
            break;
        case 0x13:
            flag = 5;
            break;
        case 0x12:
            flag = 6;
            break;
        case 0x0C:
            flag = 7;
            break;
        case 0x0B:
            flag = 8;
            break;
        case 0x0A:
            flag = 9;
            break;
        case 0x03:
            flag = 15;
            break;
        case 0x19:
            flag = 10;
            break;
        case 0x11:
            flag = 11;
            break;
        case 0x09:
            flag = 12;
            break;
        case 0x01:
            flag = 13;
            break;
        case 0x02:
            flag = 14;
            break;
        default:
            break;
    }
}

void switch_flag(void) {
    switch (flag) {
        case 1:
            Tx1_Buffer[0] = 0x0c;
            if (Rx2_Buffer[0] == 0) {
                I2C_ZLG7290_Write(&hi2c1, 0x70, ZLG_WRITE_ADDRESS1, Tx1_Buffer, 1);
            } else {
                I2C_ZLG7290_Write(&hi2c1, 0x70, ZLG_WRITE_ADDRESS2, Rx2_Buffer, BUFFER_SIZE2);
                I2C_ZLG7290_Write(&hi2c1, 0x70, ZLG_WRITE_ADDRESS1, Tx1_Buffer, 1);
            }
            break;
        case 2:
            Tx1_Buffer[0] = 0xDA;
            if (Rx2_Buffer[0] == 0) {
                I2C_ZLG7290_Write(&hi2c1, 0x70, ZLG_WRITE_ADDRESS1, Tx1_Buffer, 1);
            } else {
                I2C_ZLG7290_Write(&hi2c1, 0x70, ZLG_WRITE_ADDRESS2, Rx2_Buffer, BUFFER_SIZE2);
                I2C_ZLG7290_Write(&hi2c1, 0x70, ZLG_WRITE_ADDRESS1, Tx1_Buffer, 1);
            }
            break;
        case 3:
            Tx1_Buffer[0] = 0xF2;
            if (Rx2_Buffer[0] == 0) {
                I2C_ZLG7290_Write(&hi2c1, 0x70, ZLG_WRITE_ADDRESS1, Tx1_Buffer, 1);
            } else {
                I2C_ZLG7290_Write(&hi2c1, 0x70, ZLG_WRITE_ADDRESS2, Rx2_Buffer, BUFFER_SIZE2);
                I2C_ZLG7290_Write(&hi2c1, 0x70, ZLG_WRITE_ADDRESS1, Tx1_Buffer, 1);
            }
            break;
        case 4:
            Tx1_Buffer[0] = 0x66;
            if (Rx2_Buffer[0] == 0) {
                I2C_ZLG7290_Write(&hi2c1, 0x70, ZLG_WRITE_ADDRESS1, Tx1_Buffer, 1);
            } else {
                I2C_ZLG7290_Write(&hi2c1, 0x70, ZLG_WRITE_ADDRESS2, Rx2_Buffer, BUFFER_SIZE2);
                I2C_ZLG7290_Write(&hi2c1, 0x70, ZLG_WRITE_ADDRESS1, Tx1_Buffer, 1);
            }
            break;
        case 5:
            Tx1_Buffer[0] = 0xB6;
            if (Rx2_Buffer[0] == 0) {
                I2C_ZLG7290_Write(&hi2c1, 0x70, ZLG_WRITE_ADDRESS1, Tx1_Buffer, 1);
            } else {
                I2C_ZLG7290_Write(&hi2c1, 0x70, ZLG_WRITE_ADDRESS2, Rx2_Buffer, BUFFER_SIZE2);
                I2C_ZLG7290_Write(&hi2c1, 0x70, ZLG_WRITE_ADDRESS1, Tx1_Buffer, 1);
            }
            break;
        case 6:
            Tx1_Buffer[0] = 0xBE;
            if (Rx2_Buffer[0] == 0) {
                I2C_ZLG7290_Write(&hi2c1, 0x70, ZLG_WRITE_ADDRESS1, Tx1_Buffer, 1);
            } else {
                I2C_ZLG7290_Write(&hi2c1, 0x70, ZLG_WRITE_ADDRESS2, Rx2_Buffer, BUFFER_SIZE2);
                I2C_ZLG7290_Write(&hi2c1, 0x70, ZLG_WRITE_ADDRESS1, Tx1_Buffer, 1);
            }
            break;
        case 7:
            Tx1_Buffer[0] = 0xE0;
            if (Rx2_Buffer[0] == 0) {
                I2C_ZLG7290_Write(&hi2c1, 0x70, ZLG_WRITE_ADDRESS1, Tx1_Buffer, 1);
            } else {
                I2C_ZLG7290_Write(&hi2c1, 0x70, ZLG_WRITE_ADDRESS2, Rx2_Buffer, BUFFER_SIZE2);
                I2C_ZLG7290_Write(&hi2c1, 0x70, ZLG_WRITE_ADDRESS1, Tx1_Buffer, 1);
            }
            break;
        case 8:
            Tx1_Buffer[0] = 0xFE;
            if (Rx2_Buffer[0] == 0) {
                I2C_ZLG7290_Write(&hi2c1, 0x70, ZLG_WRITE_ADDRESS1, Tx1_Buffer, 1);
            } else {
                I2C_ZLG7290_Write(&hi2c1, 0x70, ZLG_WRITE_ADDRESS2, Rx2_Buffer, BUFFER_SIZE2);
                I2C_ZLG7290_Write(&hi2c1, 0x70, ZLG_WRITE_ADDRESS1, Tx1_Buffer, 1);
            }
            break;
        case 9:
            Tx1_Buffer[0] = 0xE6;
            if (Rx2_Buffer[0] == 0) {
                I2C_ZLG7290_Write(&hi2c1, 0x70, ZLG_WRITE_ADDRESS1, Tx1_Buffer, 1);
            } else {
                I2C_ZLG7290_Write(&hi2c1, 0x70, ZLG_WRITE_ADDRESS2, Rx2_Buffer, BUFFER_SIZE2);
                I2C_ZLG7290_Write(&hi2c1, 0x70, ZLG_WRITE_ADDRESS1, Tx1_Buffer, 1);
            }
            break;
        case 10:
            Tx1_Buffer[0] = 0xEE;
            if (Rx2_Buffer[0] == 0) {
                I2C_ZLG7290_Write(&hi2c1, 0x70, ZLG_WRITE_ADDRESS1, Tx1_Buffer, 1);
            } else {
                I2C_ZLG7290_Write(&hi2c1, 0x70, ZLG_WRITE_ADDRESS2, Rx2_Buffer, BUFFER_SIZE2);
                I2C_ZLG7290_Write(&hi2c1, 0x70, ZLG_WRITE_ADDRESS1, Tx1_Buffer, 1);
            }
            break;
        case 11:
            Tx1_Buffer[0] = 0x3E;
            if (Rx2_Buffer[0] == 0) {
                I2C_ZLG7290_Write(&hi2c1, 0x70, ZLG_WRITE_ADDRESS1, Tx1_Buffer, 1);
            } else {
                I2C_ZLG7290_Write(&hi2c1, 0x70, ZLG_WRITE_ADDRESS2, Rx2_Buffer, BUFFER_SIZE2);
                I2C_ZLG7290_Write(&hi2c1, 0x70, ZLG_WRITE_ADDRESS1, Tx1_Buffer, 1);
            }
            break;
        case 12:
            Tx1_Buffer[0] = 0x9C;
            if (Rx2_Buffer[0] == 0) {
                I2C_ZLG7290_Write(&hi2c1, 0x70, ZLG_WRITE_ADDRESS1, Tx1_Buffer, 1);
            } else {
                I2C_ZLG7290_Write(&hi2c1, 0x70, ZLG_WRITE_ADDRESS2, Rx2_Buffer, BUFFER_SIZE2);
                I2C_ZLG7290_Write(&hi2c1, 0x70, ZLG_WRITE_ADDRESS1, Tx1_Buffer, 1);
            }
            break;
        case 13:
            Tx1_Buffer[0] = 0x7A;
            if (Rx2_Buffer[0] == 0) {
                I2C_ZLG7290_Write(&hi2c1, 0x70, ZLG_WRITE_ADDRESS1, Tx1_Buffer, 1);
            } else {
                I2C_ZLG7290_Write(&hi2c1, 0x70, ZLG_WRITE_ADDRESS2, Rx2_Buffer, BUFFER_SIZE2);
                I2C_ZLG7290_Write(&hi2c1, 0x70, ZLG_WRITE_ADDRESS1, Tx1_Buffer, 1);
            }
            break;
        case 14:
            Tx1_Buffer[0] = 0x00;
            I2C_ZLG7290_Write(&hi2c1, 0x70, ZLG_WRITE_ADDRESS1, Tx1_Buffer, 8);
            break;
        case 15:
            Tx1_Buffer[0] = 0xFC;
            if (Rx2_Buffer[0] == 0) {
                I2C_ZLG7290_Write(&hi2c1, 0x70, ZLG_WRITE_ADDRESS1, Tx1_Buffer, 1);
            } else {
                I2C_ZLG7290_Write(&hi2c1, 0x70, ZLG_WRITE_ADDRESS2, Rx2_Buffer, BUFFER_SIZE2);
                I2C_ZLG7290_Write(&hi2c1, 0x70, ZLG_WRITE_ADDRESS1, Tx1_Buffer, 1);
            }
            break;
        default:
            break;
    }
}

