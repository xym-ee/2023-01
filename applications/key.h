#ifndef __KEY_H
#define __KEY_H

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>


#define     KEY_THREAD_STACK_SIZE   256
#define     KEY_THREAD_PRIORITY     3
#define     KEY_THREAD_TIMESLICE    10


//上拉输入，
#define     KEY_GREEN_PIN           GET_PIN(E, 3)
#define     KEY_YELLOW1_PIN         GET_PIN(E, 5)
#define     KEY_YELLOW2_PIN         GET_PIN(C, 13)
#define     KEY_RED_PIN             GET_PIN(C, 1)

//PE2 蜂鸣器
#define     SERVO_L_PIN             GET_PIN(E, 0)
#define     SERVO_R_PIN             GET_PIN(B, 8)
#define     SERVO_U_PIN             GET_PIN(B, 6)
#define     SERVO_D_PIN             GET_PIN(B, 3)

extern rt_uint8_t key;
extern rt_uint8_t servo_key;

#endif
