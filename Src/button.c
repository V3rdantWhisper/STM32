//
// Created by nemo on 5/21/24.
//
/* USER CODE BEGIN 4 */
#include "zlg7290.h"
#include "i2c.h"
#include "usart.h"
#include "state_machine.h"

#define TIME_MAX 99999999

uint8_t time_buffer[8] = {0};
uint64_t now_time = 0;
uint8_t bottom_num;

void ClockKeyboadProcess() {
    switch (bottom_num) {
        case ZLG7290_KEY_A:
            if (now_time < TIME_MAX) {
                now_time++;
            }
            break;
        case ZLG7290_KEY_B:
            if (now_time > 0) {
                now_time--;
            }
            break;
        case ZLG7290_KEY_C:
            now_time = 0;
            break;
        case ZLG7290_KEY_D:
            now_time = 99999999;
            break;
        case ZLG7290_KEY_STAR:
            enqueue_event(EVENT_SET_ALARM);
            break;
        case ZLG7290_KEY_POUND:
            enqueue_event(EVENT_SET_PAUSE);
            break;
        default:

            // process number
            break;
    }


}




