#ifndef __KEY_H
#define __KEY_H

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>


#define     KEY_THREAD_STACK_SIZE   256
#define     KEY_THREAD_PRIORITY     3
#define     KEY_THREAD_TIMESLICE    10


#define     KEY_OUTPUT_PIN          GET_PIN(B, 3)
#define     KEY_GREEN_PIN           GET_PIN(D, 6)
#define     KEY_YELLOW1_PIN         GET_PIN(D, 4)
#define     KEY_YELLOW2_PIN         GET_PIN(D, 2)
#define     KEY_RED_PIN             GET_PIN(D, 0)



#define     SERVO_OUTPUT_PIN        GET_PIN(B, 5)
#define     SERVO_L_PIN             GET_PIN(D, 7)
#define     SERVO_R_PIN             GET_PIN(D, 5)
#define     SERVO_U_PIN             GET_PIN(D, 3)
#define     SERVO_D_PIN             GET_PIN(D, 1)

extern rt_uint8_t key;
extern rt_uint8_t servo_key;

#endif
