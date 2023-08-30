#include "railgun.h"
#include "key.h"


static void railgun_thread_entry(void *parameter)
{
    while (1)
    {
        /* 发射按键检测 */
        if (key == 4)
        {
            key = 0;
            
            rt_pin_write(FIRE_PIN, PIN_LOW);
            
            rt_thread_mdelay(500);
            
            rt_pin_write(FIRE_PIN, PIN_HIGH);
        }
        
        rt_thread_mdelay(100);
    }
}

int railgun_init(void)
{
    rt_pin_mode(CHARGE_PIN, PIN_MODE_OUTPUT_OD);
    rt_pin_mode(FIRE_PIN, PIN_MODE_OUTPUT_OD);
    
    rt_pin_write(CHARGE_PIN, PIN_HIGH);
    rt_pin_write(FIRE_PIN, PIN_HIGH);
    
    
    rt_err_t ret = RT_EOK;

    /* 创建 serial 线程 */
    rt_thread_t thread = rt_thread_create("railgun", 
                                        railgun_thread_entry, 
                                        RT_NULL, 
                                        GUN_THREAD_STACK_SIZE, 
                                        GUN_THREAD_PRIORITY, 
										GUN_THREAD_TIMESLICE);
    
    /* 创建成功则启动线程 */
    if (thread != RT_NULL)
    {
        rt_thread_startup(thread);
    }
    else
    {
        ret = RT_ERROR;
    }

    return ret;
}

/* 导出命令 or 自动初始化 */
INIT_APP_EXPORT(railgun_init);


