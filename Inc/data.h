//
// Created by nemo on 5/28/24.
//

#ifndef STM32V3_DATA_H
#define STM32V3_DATA_H

#include "stdint.h"
#include "button.h"
#include "state_machine.h"


#define CREATE_BACKUP_BUF(var) \
    typeof(var) __attribute__((section(".bak1"))) __##var##_bak1 = 0; \
    typeof(var) __attribute__((section(".bak2"))) __##var##_bak2 = 0; \
    uint32_t __attribute__((section(".crc1"))) __##var##_crc1 = 0;    \
    uint32_t __attribute__((section(".crc2"))) __##var##_crc2 = 0;    \
    uint32_t __attribute__((section(".crc3"))) __##var##_crc3 = 0;

#define CREATE_BACKUP_NUM(var) \
    typeof(var) __attribute__((section(".bak1"))) __##var##_bak1 = 0; \
    typeof(var) __attribute__((section(".bak2"))) __##var##_bak2 = 0; \

#define CREATE_BACKUP_BUF_EXTERN(var)                        \
    extern typeof(var) __##var##_bak1;                       \
    extern typeof(var) __##var##_bak2;                       \
    extern uint32_t __##var##_crc1;                          \
    extern uint32_t __##var##_crc2;                          \
    extern uint32_t __##var##_crc3;

#define CREATE_BACKUP_NUM_EXTERN(var)                        \
    extern typeof(var) __##var##_bak1;                       \
    extern typeof(var) __##var##_bak2;


#define UPDATE_NUM_BAK(var, val) { \
   __##var##_bak1 = __##var##_bak2 = var = val;                     \
}

#define GET_NUM_DATE(var, num) { \
    if ( __##var##_bak1 == __##var##_bak2 && __##var##_bak2  == var ) {      \
        num = var;                                                          \
    } else if ( __##var##_bak1 == __##var##_bak2  ) {                       \
        var =  __##var##_bak1;                                              \
        num = var;                                                           \
    } else if ( __##var##_bak2 == var ) {                                   \
        __##var##_bak1 =  __##var##_bak2;                               \
        num = __##var##_bak2;                                            \
    } else  {                                                           \
        __##var##_bak2 =  __##var##_bak1;                               \
        num = __##var##_bak1;                                           \
    }                                                                   \
}


//// check the crc
//// 多路表决
#define CHECK_THE_CRC(var) \
    if ( __##var##_crc1 && __##var##_crc2 ) {               \
        __##var##_crc3 = __##var##_crc1;                    \
    } else if (  __##var##_crc1 && __##var##_crc3 ) {       \
        __##var##_crc2 = __##var##_crc1;                    \
    } else if (  __##var##_crc2 && __##var##_crc3 ) {       \
        __##var##_crc1 = __##var##_crc3;                    \
    } else {                                                \
        __##var##_crc1 = __##var##_crc3;                    \
                                                            \
    }



CREATE_BACKUP_NUM_EXTERN(now_time);
CREATE_BACKUP_NUM_EXTERN(now_state);
CREATE_BACKUP_NUM_EXTERN(saved_state);
CREATE_BACKUP_NUM_EXTERN(cold_start);
CREATE_BACKUP_NUM_EXTERN(controlFlowChecksum);



#endif //STM32V3_DATA_H
