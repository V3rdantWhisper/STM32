//
// Created by nemo on 5/27/24.
//
#include "stm32f4xx_hal.h"
#include "state_machine.h"
#include "button.h"
#include "zlg7290.h"
#include "beep.h"

#define STATE_CHECKSUM_INIT        0x1
#define STATE_CHECKSUM_IDLE        0x10
#define STATE_CHECKSUM_CONFIG_TIME 0x100
#define STATE_CHECKSUM_ALARM_ON    0x1000
#define STATE_CHECKSUM_TIME        0x10000
#define STATE_CHECKSUM_PAUSE       0x100000

#define PRE_STATE_IDLE          STATE_CHECKSUM_PAUSE | STATE_CHECKSUM_CONFIG_TIME
#define PRE_STATE_PAUSE         STATE_CHECKSUM_PAUSE | STATE_CHECKSUM_IDLE       | STATE_CHECKSUM_TIME
#define PRE_STATE_TIME          STATE_CHECKSUM_PAUSE | STATE_CHECKSUM_CONFIG_TIME | STATE_CHECKSUM_TIME
#define PRE_STATE_CONFIG_TIME   STATE_CHECKSUM_INIT  | STATE_CHECKSUM_CONFIG_TIME | STATE_CHECKSUM_ALARM_ON | STATE_CHECKSUM_IDLE
#define PRE_STATE_ALARM_ON      STATE_CHECKSUM_TIME 

uint32_t controlFlowChecksum = STATE_CHECKSUM_INIT;

AlarmEvent event_queue[8] = {0};
uint8_t event_queue_head = 0;
uint8_t event_queue_tail = 0;
uint8_t event_queue_size = 0;
AlarmState now_state = STATE_CONFIG_TIME;
AlarmState saved_state = STATE_CONFIG_TIME;

void EnqueueEvent(AlarmEvent event) {
    __disable_irq();
    event_queue[event_queue_tail] = event;
    event_queue_tail = (event_queue_tail + 1) % 8;
    if (event_queue_size != 8) {
        event_queue_size++;
    } else {
        event_queue_head = (event_queue_head + 1) % 8;
    }
    __enable_irq();
}

AlarmEvent DequeueEvent() {
    if (event_queue_size == 0) {
        return EVENT_NONE;
    }
    __disable_irq();
    AlarmEvent event = event_queue[event_queue_head];
    event_queue_head = (event_queue_head + 1) % 8;
    event_queue_size--;
    __enable_irq();
    return event;
}

void RUNSTateIDLE(AlarmEvent Event) {
    HAL_SuspendTick();
    HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
    HAL_ResumeTick();
    now_state = saved_state; // back to the saved state
}

// complete
void RUNStateCONFIGTIME(AlarmEvent Event) {
    switch (Event) {
        case EVENT_KEYBOARD:
            ClockKeyboadProcess();
            break;
        case EVENT_SET_TIME:
            now_state = STATE_TIME;
            break;
        case EVENT_SET_IDLE:
            saved_state = STATE_CONFIG_TIME;
            now_state = STATE_IDLE;
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
    now_state = STATE_CONFIG_TIME;

}

// complete
void RUNStateTIME(AlarmEvent Event) {
    switch (Event) {
        case EVENT_SET_PAUSE:
            now_state = STATE_PAUSE;
            break;
        default:
            if (now_time != 0) {
                now_time--;
                FlashTime();
                HAL_Delay(50);
            } else {
                now_state = STATE_ALARM_ON;
            }
            break;
    }
}

// complete
void RUNStatePAUSE(AlarmEvent Event) {
    switch (Event) {
        case EVENT_KEYBOARD:
            if (bottom_num == ZLG7290_KEY_POUND)
                now_state = STATE_TIME;
            break;
        case EVENT_SET_IDLE:
            saved_state = STATE_PAUSE;
            now_state = STATE_IDLE;
            break;
        default:
            break;
    }
}


void handleStateMachine() {
    // TODO: check Event Queue
    AlarmEvent event = DequeueEvent();
    switch (now_state) {
        case STATE_IDLE:
            // TODO: cfi check
            if(controlFlowChecksum | PRE_STATE_IDLE == 0){
                ;//error
            }
            RUNSTateIDLE(event);
            controlFlowChecksum = STATE_CHECKSUM_IDLE;
            break;
        case STATE_CONFIG_TIME:
            if(controlFlowChecksum | PRE_STATE_CONFIG_TIME == 0){
                ;//error
            }
            RUNStateCONFIGTIME(event);
            controlFlowChecksum = STATE_CHECKSUM_CONFIG_TIME;
            break;
        case STATE_TIME:
            if(controlFlowChecksum | PRE_STATE_TIME == 0){
                ;//error
            }
            RUNStateTIME(event);
            controlFlowChecksum = STATE_CHECKSUM_TIME;
            break;
        case STATE_ALARM_ON:
            if(controlFlowChecksum | PRE_STATE_ALARM_ON == 0){
                ; //error      
            }
            RUNStateALARM(event);
            controlFlowChecksum = STATE_CHECKSUM_ALARM_ON;
            break;
        case STATE_PAUSE:
            if(controlFlowChecksum | PRE_STATE_PAUSE == 0){
                ; //error      
            }
            RUNStatePAUSE(event);
            controlFlowChecksum = STATE_CHECKSUM_PAUSE;
            break;
        default:
            break;
    }
}


