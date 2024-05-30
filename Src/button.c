//
// Created by nemo on 5/21/24.
//

#include "zlg7290.h"
#include "i2c.h"
#include "state_machine.h"
#define TIME_MAX 99999999

uint8_t  __attribute__((section(".sodata"))) read_buffer[8] = {0};
uint8_t  __attribute__((section(".sodata"))) time_buffer[8] = {0};
uint64_t __attribute__((section(".sodata"))) now_time = 0;
uint8_t  __attribute__((section(".sodata"))) bottom_num;


uint8_t ZLG7290KeyToNum(uint8_t key);
uint8_t num_to_ZLG7290Key(uint8_t num);

void FlashTime() {
    time_buffer[0] = num_to_ZLG7290Key(now_time / 10000000 );
    time_buffer[1] = num_to_ZLG7290Key( now_time / 1000000 % 10 );
    time_buffer[2] = num_to_ZLG7290Key( now_time / 100000 % 10 );
    time_buffer[3] = num_to_ZLG7290Key( now_time / 10000 % 10 );
    time_buffer[4] = num_to_ZLG7290Key( now_time / 1000 % 10 );
    time_buffer[5] = num_to_ZLG7290Key( now_time / 100 % 10 );
    time_buffer[6] = num_to_ZLG7290Key( now_time / 10 % 10 );
    time_buffer[7] = num_to_ZLG7290Key( now_time % 10 );

    ZLG7290_Write(&hi2c1, ZLG7290_ADDR_DPRAM0, time_buffer, 8);
}

uint8_t ZLG7290KeyToNum(uint8_t key) {
    switch (key) {
        case ZLG7290_KEY_0:
            return 0;
            break;
        case ZLG7290_KEY_1:
            return 1;
            break;
        case ZLG7290_KEY_2:
            return 2;
            break;
        case ZLG7290_KEY_3:
            return 3;
            break;
        case ZLG7290_KEY_4:
            return 4;
            break;
        case ZLG7290_KEY_5:
            return 5;
            break;
        case ZLG7290_KEY_6:
            return 6;
            break;
        case ZLG7290_KEY_7:
            return 7;
            break;
        case ZLG7290_KEY_8:
            return 8;
            break;
        case ZLG7290_KEY_9:
            return 9;
            break;
        default:
            return ZLG7290_INVALID_NUM;
            break;
    }
}

uint8_t num_to_ZLG7290Key(uint8_t num) {
    switch (num) {
        case 1:
            return ZLG7290_DISPLAY_1;
            break;
        case 2:
            return ZLG7290_DISPLAY_2;
            break;
        case 3:
            return ZLG7290_DISPLAY_3;
            break;
        case 4:
            return ZLG7290_DISPLAY_4;
            break;
        case 5:
            return ZLG7290_DISPLAY_5;
            break;
        case 6:
            return ZLG7290_DISPLAY_6;
            break;
        case 7:
            return ZLG7290_DISPLAY_7;
            break;
        case 8:
            return ZLG7290_DISPLAY_8;
            break;
        case 9:
            return ZLG7290_DISPLAY_9;
            break;
        case 0:
            return ZLG7290_DISPLAY_0;
            break;
        default:
            return ZLG7290_INVALID_NUM;
            break;
    }
}


void ClockKeyboadProcess() {
    uint8_t num;
    switch (bottom_num) {
        case ZLG7290_KEY_A:
            if (now_time < TIME_MAX) {
                now_time++;
            }
            FlashTime();
            break;
        case ZLG7290_KEY_B:
            if (now_time > 0) {
                now_time--;
            }
            break;
        case ZLG7290_KEY_C:
            now_time = 0;
            FlashTime();
            break;
        case ZLG7290_KEY_D:
            now_time = 99999999;
            FlashTime();
            break;
        case ZLG7290_KEY_STAR:
            EnqueueEvent(EVENT_SET_TIME);
            break;
        case ZLG7290_KEY_POUND:
            EnqueueEvent(EVENT_SET_PAUSE);
            break;
        default:
            num = ZLG7290KeyToNum(bottom_num);
            if (num == ZLG7290_INVALID_NUM)
                break;
            now_time = now_time * 10 + num;
            if (now_time > TIME_MAX) {
                now_time = TIME_MAX;
            }
            FlashTime();
    }
}




