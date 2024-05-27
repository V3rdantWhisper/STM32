//
// Created by nemo on 5/27/24.
//

#ifndef STM32V3_STATE_MACHINE_H
#define STM32V3_STATE_MACHINE_H


typedef enum {
    STATE_IDLE,
    STATE_SET_TIME,
    STATE_ALARM_ON,
    STATE_PAUSE,
    STATE_ALARM_PAUSE,
} AlarmState;

typedef enum {
    EVENT_SET_TIME,
    EVENT_SET_ALARM,
    EVENT_ALARM_TRIGGERED,
    EVENT_ALARM_STOPPED,
    EVENT_SET_PAUSE,
    EVENT_TIMEOUT
} AlarmEvent;


void enqueue_event(AlarmEvent event);
AlarmEvent dequeue_event();

#endif //STM32V3_STATE_MACHINE_H
