//
// Created by nemo on 5/21/24.
//
#include "stm32f4xx_hal.h"
#include "gpio.h"


void open_beep(unsigned int delay) {
    HAL_GPIO_WritePin(GPIOG,GPIO_PIN_6,GPIO_PIN_SET);
    HAL_Delay(delay);
}

void close_beep(unsigned int delay) {
    HAL_GPIO_WritePin(GPIOG,GPIO_PIN_6,GPIO_PIN_RESET);
    HAL_Delay(delay);
}
