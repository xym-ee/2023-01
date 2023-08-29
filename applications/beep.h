#ifndef __BEEP_H
#define __BEEP_H

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>




#define     BEEP_THREAD_STACK_SIZE   256
#define     BEEP_THREAD_PRIORITY     16
#define     BEEP_THREAD_TIMESLICE    10


/* defined the LED0 pin: PC13 */
#define BEEP_PIN    GET_PIN(B, 0)


extern rt_uint32_t time;


#endif
