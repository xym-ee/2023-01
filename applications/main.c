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
        if (voltage > CHATGE_LIMIT)
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
        
        
        
        
//        /* 充电启动 */
//        if ( key.red ==0 )
//        {
//            rt_pin_write(CHARGE_PIN, PIN_LOW);
//            rt_kprintf("start_charge\n");
//        }
//        
//        /* 充电停止 */
//        if ( key.green == 0)
//        {
//            rt_pin_write(CHARGE_PIN, PIN_HIGH);
//            rt_kprintf("stop_charge\n");
//        }
//        
//        /* 发射触发 */
//        if ( key.yellow2 == 0 )
//        {
//            rt_pin_write(FIRE_PIN, PIN_LOW);
//            
//            rt_kprintf("fire\n");
//            
//            rt_thread_mdelay(500);
//        
//            rt_pin_write(FIRE_PIN, PIN_HIGH);
//        }


        
        rt_thread_mdelay(1000);    
    }
}


