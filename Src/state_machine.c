//
// Created by nemo on 5/27/24.
//
#include "state_machine.h"
#include "button.h"


AlarmEvent event_queue[8] = {0};
uint8_t event_queue_head = 0;
uint8_t event_queue_tail = 0;
AlarmState now_state = STATE_IDLE;

void enqueue_event(AlarmEvent event) {
    event_queue[event_queue_tail] = event;
    event_queue_tail = (event_queue_tail + 1) % 8;
}

AlarmEvent dequeue_event() {
    AlarmEvent event = event_queue[event_queue_head];
    event_queue_head = (event_queue_head + 1) % 8;
    return event;
}

void handleStateMachine() {
    switch (now_state) {
        case STATE_IDLE:
            // TODO
            break;
        case STATE_SET_TIME:
            // TODO
            break;
        case STATE_ALARM_ON:
            // TODO
            break;
        case STATE_PAUSE:
            // TODO
            break;
        case STATE_ALARM_PAUSE:
            // TODO
            break;
        default:
            break;
    }
}


