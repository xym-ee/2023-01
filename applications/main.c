/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-06     misonyo   first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#include "adc.h"

#define BEEP_PIN    GET_PIN(E, 2)


/* 电压过高，蜂鸣器报警 */
int main(void)
{
    rt_pin_mode(BEEP_PIN, PIN_MODE_OUTPUT);
    rt_pin_write(BEEP_PIN, PIN_HIGH);
    
    while(1)
    {
        if (voltage > CHATGE_LIMIT - 200)
        {
            rt_pin_write(BEEP_PIN, PIN_LOW);
            rt_thread_mdelay(300);
            rt_pin_write(BEEP_PIN, PIN_HIGH);
            rt_thread_mdelay(300);
            
            rt_pin_write(BEEP_PIN, PIN_LOW);
            rt_thread_mdelay(300);
            rt_pin_write(BEEP_PIN, PIN_HIGH);
            rt_thread_mdelay(300);
            
            rt_pin_write(BEEP_PIN, PIN_LOW);
            rt_thread_mdelay(300);
            rt_pin_write(BEEP_PIN, PIN_HIGH);
            rt_thread_mdelay(300);
        }
        
        rt_thread_mdelay(1000);    
    }
}


