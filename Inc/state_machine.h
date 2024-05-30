//
// Created by nemo on 5/27/24.
//

#ifndef STM32V3_STATE_MACHINE_H
#define STM32V3_STATE_MACHINE_H


typedef enum {
    STATE_IDLE,
    STATE_CONFIG_TIME,
    STATE_TIME,
    STATE_ALARM_ON,
    STATE_PAUSE,
} AlarmState;


typedef enum {
    EVENT_NONE,
    EVENT_SET_TIME,
    EVENT_SET_PAUSE,
    EVENT_KEYBOARD,
    EVENT_SET_IDLE
} AlarmEvent;


extern AlarmState now_state;
extern AlarmState saved_state;
extern uint32_t cold_start;
extern uint32_t controlFlowChecksum;

extern void Reset_Handler();
void handleStateMachine();
AlarmEvent DequeueEvent();
void EnqueueEvent(AlarmEvent event);

#endif //STM32V3_STATE_MACHINE_H
