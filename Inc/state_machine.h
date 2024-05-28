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
/* STATE_IDLE:
 *   --> STATE_SET_TIME
 * STATE_SET_TIME
 *   --> STATE_IDLE
 * STA
 *
 *
 *
 *
 *
 *
 * */



typedef enum {
    EVENT_NONE,
    EVENT_SET_TIME,
    EVENT_SET_ALARM,
    EVENT_SET_PAUSE,
    EVENT_CONFIG_TIME,
    EVENT_SET_IDLE
} AlarmEvent;


void handleStateMachine();
AlarmEvent DequeueEvent();
void EnqueueEvent(AlarmEvent event);

#endif //STM32V3_STATE_MACHINE_H