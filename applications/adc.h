#ifndef __ADC_H
#define __ADC_H


#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>




#define     ADC_THREAD_STACK_SIZE   512
#define     ADC_THREAD_PRIORITY     2
#define     ADC_THREAD_TIMESLICE    10

/* 充电电压限制 */
#define CHATGE_LIMIT        1200


extern rt_uint32_t voltage;

#endif

