//
// Created by nemo on 5/28/24.
//
#include "stdint.h"
#include "stm32f4xx_hal.h"
#include "data.h"
#include "button.h"
#include "state_machine.h"

static __IO uint32_t uwTick;
uint64_t time_out;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == GPIO_PIN_13) {
        EnqueueEvent(EVENT_KEYBOARD);
        time_out = 0;
    }
}

void HAL_IncTick() {
    uwTick++;
    switch (now_state) {
        case STATE_TIME :
            if ( now_time > 0 && uwTick % 1 == 0 ) {
                UPDATE_NUM_BAK( now_time, now_time-1 );
            }
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