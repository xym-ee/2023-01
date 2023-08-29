#ifndef __KEY_H
#define __KEY_H

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>


#define     KEY_THREAD_STACK_SIZE   256
#define     KEY_THREAD_PRIORITY     11
#define     KEY_THREAD_TIMESLICE    10


#define     KEY_OUTPUT_PIN          GET_PIN(A, 8)
#define     KEY_GREEN_PIN           GET_PIN(B, 15)
#define     KEY_YELLOW1_PIN         GET_PIN(B, 14)
#define     KEY_YELLOW2_PIN         GET_PIN(B, 13)
#define     KEY_RED_PIN             GET_PIN(B, 12)





#endif
