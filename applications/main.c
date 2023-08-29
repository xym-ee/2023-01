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



#define CHARGE_PIN      GET_PIN(B, 0)
#define FIRE_PIN        GET_PIN(B, 1)


int main(void)
{
    while(1)
    {
        
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

        
        //rt_kprintf("%d\n", voltage);
        
        rt_thread_mdelay(1000);    
    }
}


