//
// Created by nemo on 5/21/24.
//

#ifndef STM32V3_BUTTON_C_H
#define STM32V3_BUTTON_C_H

#include "stdint.h"

extern uint8_t flag;//不同的按键有不同的标志位值
extern uint8_t flag1;//中断标志位，每次按键产生一次中断，并开始读取8个数码管的值
extern uint8_t Rx2_Buffer[8];
extern uint8_t Tx1_Buffer[8];
extern uint8_t Rx1_Buffer[1];

void swtich_key(void);
void switch_flag(void);

#endif //STM32V3_BUTTON_C_H
