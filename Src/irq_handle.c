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
uint64_t time_out;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == GPIO_PIN_13) {
//        for (int i = 0; i < 3; i++) {
//            I2C_ZLG7290_Read(&hi2c1, ZLG7290_READ_ADDR, ZLG7290_ADDR_KEY, &read_buffer[i], 1);
//        }
        EnqueueEvent(EVENT_KEYBOARD);
//        if ( read_buffer[0] == read_buffer[1] && read_buffer[0] == read_buffer[2] ) {
//            EnqueueEvent(EVENT_KEYBOARD);
//        }
        time_out = 0;
    }
}

void HAL_IncTick() {
    uwTick++;
    switch (now_state) {
        case STATE_TIME :
        case STATE_ALARM_ON:
        case STATE_IDLE:
            time_out = 0;
            break;
        default:
            time_out++;
            if (uwTick >= 1000000000) {
                time_out = 0;
                EnqueueEvent(EVENT_SET_IDLE);
            }
            break;

    }

}

uint32_t HAL_GetTick(void)
{
    return uwTick;
}