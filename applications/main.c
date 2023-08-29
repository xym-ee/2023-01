#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>


#include "key.h"
#include "orangepi.h"

#define CHARGE_PIN      GET_PIN(B, 0)
#define FIRE_PIN        GET_PIN(B, 1)



/* 680K 10K    read*33/4096*69 */

#include "adc.h"

int main(void)
{
    rt_pin_mode(CHARGE_PIN, PIN_MODE_OUTPUT_OD);
    rt_pin_mode(FIRE_PIN, PIN_MODE_OUTPUT_OD);
    
    rt_pin_write(CHARGE_PIN, PIN_HIGH);
    rt_pin_write(FIRE_PIN, PIN_HIGH);
    
 
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





