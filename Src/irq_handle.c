//
// Created by nemo on 5/28/24.
//
#include "stdint.h"
#include "stm32f4xx_hal.h"
#include "i2c.h"
#include "zlg7290.h"
#include "button.h"
#include "state_machine.h"

static __IO uint32_t uwTick;


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == GPIO_PIN_13) {
        for (int i = 0; i < 5; i++) {
            I2C_ZLG7290_Read(&hi2c1, ZLG7290_READ_ADDR, ZLG7290_ADDR_KEY, &read_buffer[i], 1);
        }
        bottom_num = read_buffer[0];
        uwTick = 0;
    }
}

void HAL_IncTick() {
    uwTick++;
    switch (now_state) {
        case STATE_TIME :
        case STATE_ALARM_ON:
        case STATE_IDLE:
            uwTick = 0;
            break;
        default:
            uwTick++;
            if (uwTick >= 10000) {
                uwTick = 0;
                EnqueueEvent(EVENT_SET_IDLE);
            }
            break;

    }

}