#ifndef __LED_DISPLAY_H
#define __LED_DISPLAY_H

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>



#define     DISPLAY_THREAD_STACK_SIZE   1024
#define     DISPLAY_THREAD_PRIORITY     10
#define     DISPLAY_THREAD_TIMESLICE    10


#define SM16106_PIN_OE      GET_PIN(B, 6)
#define SM16106_PIN_CK      GET_PIN(B, 8)
#define SM16106_PIN_DI      GET_PIN(B, 7)
#define SM16106_PIN_LE      GET_PIN(B, 9)




#endif
