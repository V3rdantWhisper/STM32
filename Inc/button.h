//
// Created by nemo on 5/21/24.
//

#ifndef STM32V3_BUTTON_C_H
#define STM32V3_BUTTON_C_H

#include "stdint.h"

#define TIME_MAX 99999999

extern uint8_t read_buffer[8];
extern uint8_t time_buffer[8];
extern uint64_t now_time;
extern uint8_t bottom_num;

void FlashTime();
void ClockKeyboadProcess();




#endif //STM32V3_BUTTON_C_H
