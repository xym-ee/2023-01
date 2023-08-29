#ifndef __OPENMV_H
#define __OPENMV_H

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>


#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>


#define OPENMV_UART       "uart2"


#define OPENMV_THREAD_PRIORITY         2
#define OPENMV_THREAD_STACK_SIZE       1024
#define OPENMV_THREAD_TIMESLICE        10



typedef struct 
{
	rt_uint8_t u;	
	rt_uint8_t v;
} 
pix_t;

extern pix_t pix;



#endif
