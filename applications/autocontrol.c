#include "autocontrol.h"

#include "status.h"

#include "openmv.h"



rt_int32_t yaw_auto_control = 0;
rt_int32_t pit_auto_control = 0;

/*--------------------------  数据处理线程  ---------------------------*/

static void auto_thread_entry(void *parameter)
{

    while (1)
    {
        /* 手动控制，不干预舵机 */
        if (status.control_mode == MANUAL)
        {
            yaw_auto_control = 0;
            pit_auto_control = 0;
            
            rt_thread_mdelay(1000);
        }
        else
        {
            /* 水平跟踪 */
            if (160 - pix.u > 10)
            {
                yaw_auto_control += 10000;
            }
            else if (160 - pix.u < -10)
            {
                yaw_auto_control += -10000;
            }
//            else
//            {
//                yaw_auto_control = 0;
//            }

            
            /* 垂直跟踪，openmv不会垂直动，不用做这个。 */
//            if (120 - pix.v > 10)
//            {
//                pit_auto_control = 10000;
//            }
//            else if (120 - pix.v < -10)
//            {
//                pit_auto_control = -10000;
//            }
//            else
//            {
//                pit_auto_control = 0;
//            }           
            
            
            
            rt_thread_mdelay(50);
        }
    }
}

int auto_init(void)
{
    rt_err_t ret = RT_EOK;

    /* 创建 serial 线程 */
    rt_thread_t thread = rt_thread_create("auto", 
                                        auto_thread_entry, 
                                        RT_NULL, 
                                        AUTO_THREAD_STACK_SIZE, 
                                        AUTO_THREAD_PRIORITY, 
										AUTO_THREAD_TIMESLICE);
    
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
INIT_APP_EXPORT(auto_init);




