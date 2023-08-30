#ifndef __RAILGUN_H
#define __RAILGUN_H

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>


#define CHARGE_PIN      GET_PIN(C, 4)
#define FIRE_PIN        GET_PIN(C, 5)


#define     GUN_THREAD_STACK_SIZE   256
#define     GUN_THREAD_PRIORITY     5
#define     GUN_THREAD_TIMESLICE    10


#endif

