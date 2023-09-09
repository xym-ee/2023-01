#include "pwm.h"
#include "key.h"
#include "status.h"
#include "autocontrol.h"

/*----------------------   pwm舵机控制线程   --------------------------*/
static rt_thread_t servo_pwm_thread = RT_NULL;

/* 线程 1 的入口函数 */
static void servo_pwm_thread_entry(void *parameter)
{
    struct rt_device_pwm *pwm_dev;      /* PWM设备句柄 */
    
    pwm_dev = (struct rt_device_pwm *)rt_device_find(PWM_SERVO_DEV);
    
    rt_pwm_set(pwm_dev, PWM_SERVO_YAW, 20000000, 1500000);
    rt_pwm_set(pwm_dev, PWM_SERVO_PITCH, 20000000, 1500000);
    
    rt_pwm_enable(pwm_dev, PWM_SERVO_YAW);
    rt_pwm_enable(pwm_dev, PWM_SERVO_PITCH);
    
    rt_int32_t yaw_control = 0;
    rt_int32_t pit_control = 0;

    
    while (1)
    {
        switch (status.pts_control)
        {
            case LEFT   : status.pts_control = NONE; yaw_control += 10000; break;
            case RIGHT  : status.pts_control = NONE; yaw_control -= 10000; break;
            case UP     : status.pts_control = NONE; pit_control -= 10000; break;
            case DOWN   : status.pts_control = NONE; pit_control += 10000; break;
            default : ;           
        }
        
        if (status.control_mode == AUTO)
        {
            yaw_control = yaw_auto_control;
            pit_control = pit_auto_control;
        }
        
        

        /* PWM 信号输出 */
        rt_pwm_set(pwm_dev, PWM_SERVO_YAW,   20000000, 1500000 + yaw_control);   			
        rt_pwm_set(pwm_dev, PWM_SERVO_PITCH, 20000000, 1500000 + pit_control); 
        
        //rt_kprintf("%d %d\n",yaw_pwm, pitch_pwm);

        rt_thread_mdelay(20);
    }
}

int servo_thread_init(void)
{
    /* 创建线程 1，名称是 thread1，入口是 thread1_entry*/
    servo_pwm_thread = rt_thread_create("servo",
                            servo_pwm_thread_entry, 
                            RT_NULL,
                            SERVO_PWM_STACK_SIZE,
                            SERVO_PWM_PRIORITY, 
                            SERVO_PWM_TIMESLICE);

    /* 如果获得线程控制块，启动这个线程 */
    if (servo_pwm_thread != RT_NULL)
        rt_thread_startup(servo_pwm_thread);

    return 0;
}

/* 导出到 msh 命令列表中 */
//MSH_CMD_EXPORT(motor_thread_init, motor_thread_init);
INIT_APP_EXPORT(servo_thread_init);

