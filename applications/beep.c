#include "beep.h"


rt_uint32_t time = 0;
rt_uint8_t  time_enable = 0;

/*--------------------------  数据处理线程  ---------------------------*/

static void beep_thread_entry(void *parameter)
{

    while (1)
    {
        if(time_enable==1)
        {
            time--;
            if(time==0)
            {
                rt_kprintf("111");
                rt_thread_mdelay(1000);
                time_enable=0;
            }
            else
            {
                rt_thread_mdelay(1000);
            }
        }
        

    }
}

int beep_init(void)
{
    rt_err_t ret = RT_EOK;

    /* 创建 serial 线程 */
    rt_thread_t thread = rt_thread_create("beep", 
                                        beep_thread_entry, 
                                        RT_NULL, 
                                        BEEP_THREAD_STACK_SIZE, 
                                        BEEP_THREAD_PRIORITY, 
										BEEP_THREAD_TIMESLICE);
    
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
INIT_APP_EXPORT(beep_init);





