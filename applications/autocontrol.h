#ifndef __AUTOCONTROL_H
#define __AUTOCONTROL_H


#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>



#define     AUTO_THREAD_STACK_SIZE   512
#define     AUTO_THREAD_PRIORITY     2
#define     AUTO_THREAD_TIMESLICE    10


extern rt_int32_t yaw_auto_control;
extern rt_int32_t pit_auto_control;


#endif

