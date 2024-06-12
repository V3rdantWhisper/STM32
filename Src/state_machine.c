//
// Created by nemo on 5/27/24.
//
#include "stm32f4xx_hal.h"
#include "state_machine.h"
#include "button.h"
#include "zlg7290.h"
#include "beep.h"
#include "i2c.h"
#include "data.h"

#define STATE_CHECKSUM_INIT        0x1
#define STATE_CHECKSUM_IDLE        0x10
#define STATE_CHECKSUM_CONFIG_TIME 0x100
#define STATE_CHECKSUM_ALARM_ON    0x1000
#define STATE_CHECKSUM_TIME        0x10000
#define STATE_CHECKSUM_PAUSE       0x100000

#define PRE_STATE_IDLE          (STATE_CHECKSUM_PAUSE | STATE_CHECKSUM_CONFIG_TIME)
#define PRE_STATE_PAUSE         (STATE_CHECKSUM_PAUSE | STATE_CHECKSUM_IDLE | STATE_CHECKSUM_TIME)
#define PRE_STATE_TIME          (STATE_CHECKSUM_PAUSE | STATE_CHECKSUM_CONFIG_TIME | STATE_CHECKSUM_TIME)
#define PRE_STATE_CONFIG_TIME   (STATE_CHECKSUM_INIT  | STATE_CHECKSUM_CONFIG_TIME | STATE_CHECKSUM_ALARM_ON | STATE_CHECKSUM_IDLE | STATE_CHECKSUM_PAUSE)
#define PRE_STATE_ALARM_ON      (STATE_CHECKSUM_TIME)

#define CHECKSUM_VALID(CHK_SUM) {                \
uint32_t chk;                           \
GET_NUM_DATE(controlFlowChecksum, chk); \
if( ( chk & CHK_SUM ) == 0){      \
        Reset_Handler();                \
    }                                   \
}


AlarmEvent __attribute__((section(".sodata"))) event_queue[8] = {0};
uint8_t __attribute__((section(".sodata"))) event_queue_head = 0;
uint8_t __attribute__((section(".sodata"))) event_queue_tail = 0;
uint8_t __attribute__((section(".sodata"))) event_queue_size = 0;
AlarmState __attribute__((section(".sodata"))) now_state = STATE_CONFIG_TIME;
AlarmState __attribute__((section(".sodata"))) saved_state = STATE_CONFIG_TIME;
uint32_t __attribute__((section(".sodata"))) cold_start;
uint32_t __attribute__((section(".sodata"))) controlFlowChecksum = STATE_CHECKSUM_INIT;


void EnqueueEvent(AlarmEvent event) {
//    __disable_irq();
    event_queue[event_queue_tail] = event;
    event_queue_tail = (event_queue_tail + 1) % 8;
    if (event_queue_size != 8) {
        event_queue_size++;
    } else {
        event_queue_head = (event_queue_head + 1) % 8;
    }
//    __enable_irq();
}

AlarmEvent DequeueEvent() {
    if (event_queue_size == 0) {
        return EVENT_NONE;
    }
//    __disable_irq();
    AlarmEvent event = event_queue[event_queue_head];
    event_queue_head = (event_queue_head + 1) % 8;
    event_queue_size--;
//    __enable_irq();
    return event;
}

void RUNSTateIDLE(AlarmEvent Event) {
    HAL_SuspendTick();
    HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
    HAL_ResumeTick();
    UPDATE_NUM_BAK( now_state, saved_state ); // back to the saved state
}

// complete
void RUNStateCONFIGTIME(uint8_t Event) {
    switch (Event) {
        case EVENT_KEYBOARD:
            for (int i = 0; i < 3; i++) {
                ZLG7290_Read(&hi2c1, ZLG7290_ADDR_KEY, read_buffer+i, 1);
            }
            if ( read_buffer[0] == read_buffer[1] && read_buffer[0] == read_buffer[2] ) {
                bottom_num = read_buffer[0];
                for (int i = 0; i < 3; i++) {
                    read_buffer[i] = 0;
                }
            } else {
                return;
            }
            ClockKeyboadProcess();
            break;
        case EVENT_SET_TIME:
            UPDATE_NUM_BAK( now_state, STATE_TIME );
            break;
        case EVENT_SET_IDLE:
            UPDATE_NUM_BAK( saved_state, STATE_CONFIG_TIME);
            UPDATE_NUM_BAK( now_state, STATE_IDLE);
            break;
        default:
            break;
    }
}


// complete
void RUNStateALARM(AlarmEvent Event) {
    for (int i = 0; i < 100; i++) {
        open_beep(2);
        close_beep(2);
    }
    UPDATE_NUM_BAK(now_state, STATE_CONFIG_TIME);

}

// complete
void RUNStateTIME(AlarmEvent Event) {
    switch (Event) {
        case EVENT_SET_PAUSE:
            UPDATE_NUM_BAK( now_state, STATE_PAUSE );
            break;
        case EVENT_KEYBOARD:
            for (int i = 0; i < 3; i++) {
                ZLG7290_Read(&hi2c1, ZLG7290_ADDR_KEY, &read_buffer[i], 1);
            }
            if ( read_buffer[0] == read_buffer[1] && read_buffer[0] == read_buffer[2] ) {
                bottom_num = read_buffer[0];
            } else {
                return;
            }
            if (bottom_num == ZLG7290_KEY_POUND) {
                UPDATE_NUM_BAK( now_state, STATE_PAUSE );
            }
        default:
            FlashTime();
            uint64_t now;
            GET_NUM_DATE(now_time, now);
            if ( now != 0) {
                HAL_Delay(50);
            } else {
                UPDATE_NUM_BAK( now_state, STATE_ALARM_ON );
            }
            break;
    }
}

// complete
void RUNStatePAUSE(AlarmEvent Event) {
    switch (Event) {
        case EVENT_KEYBOARD:
            for (int i = 0; i < 3; i++) {
                ZLG7290_Read(&hi2c1, ZLG7290_ADDR_KEY, &read_buffer[i], 1);
            }
            if ( read_buffer[0] == read_buffer[1] && read_buffer[0] == read_buffer[2] ) {
                bottom_num = read_buffer[0];
            } else {
                return;
            }
            if (bottom_num == ZLG7290_KEY_POUND) {
                UPDATE_NUM_BAK( now_state, STATE_TIME );
            } else if (bottom_num == ZLG7290_KEY_STAR) {
                UPDATE_NUM_BAK( now_state, STATE_CONFIG_TIME);
                UPDATE_NUM_BAK( now_time, 0);
                FlashTime();
            }
            break;
        case EVENT_SET_IDLE:
            UPDATE_NUM_BAK( saved_state, STATE_PAUSE);
            UPDATE_NUM_BAK( now_state, STATE_IDLE);
            break;
        default:
            break;
    }
}


void handleStateMachine() {
    AlarmEvent event = DequeueEvent();
    uint32_t cks;
    switch (now_state) {
        case STATE_IDLE:
            CHECKSUM_VALID(PRE_STATE_IDLE);
            RUNSTateIDLE(event);
            UPDATE_NUM_BAK( controlFlowChecksum, STATE_CHECKSUM_IDLE );
            break;
        case STATE_CONFIG_TIME:
            CHECKSUM_VALID(PRE_STATE_CONFIG_TIME);
            RUNStateCONFIGTIME(event);
            UPDATE_NUM_BAK( controlFlowChecksum, STATE_CHECKSUM_CONFIG_TIME );
            break;
        case STATE_TIME:
            CHECKSUM_VALID(PRE_STATE_TIME);
            RUNStateTIME(event);
            UPDATE_NUM_BAK( controlFlowChecksum, STATE_CHECKSUM_TIME );
            break;
        case STATE_ALARM_ON:
            CHECKSUM_VALID(PRE_STATE_ALARM_ON);
            RUNStateALARM(event);
            UPDATE_NUM_BAK( controlFlowChecksum, STATE_CHECKSUM_ALARM_ON );
            break;
        case STATE_PAUSE:
            CHECKSUM_VALID(PRE_STATE_PAUSE);
            RUNStatePAUSE(event);
            UPDATE_NUM_BAK( controlFlowChecksum, STATE_CHECKSUM_PAUSE );
            break;
        default:
            now_state = STATE_CONFIG_TIME;
            break;
    }
}


