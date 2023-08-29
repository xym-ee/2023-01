#include "pwm.h"
#include "key.h"

rt_int32_t yaw_pwm = 1500000;
rt_int32_t pitch_pwm = 1500000;


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
    
    while (1)
    {
        switch(servo_key)
        {
            case 1: yaw_pwm+=100000; rt_kprintf("1\n"); servo_key = 0; break;
            case 2: yaw_pwm-=100000; rt_kprintf("2\n"); servo_key = 0; break;
            case 3: pitch_pwm+=100000; rt_kprintf("3\n"); servo_key = 0; break;
            case 4: pitch_pwm-=100000; rt_kprintf("4\n"); servo_key = 0; break;
            default:;   
        
        }
        
        /*  限位 */
        if (yaw_pwm > UP_LIMIT)
            yaw_pwm = UP_LIMIT;
        if (yaw_pwm < DOWN_LIMIT)
            yaw_pwm = DOWN_LIMIT;

        if (pitch_pwm > UP_LIMIT)
            pitch_pwm = UP_LIMIT;
        if (pitch_pwm < DOWN_LIMIT)
            pitch_pwm = DOWN_LIMIT;
        
        /* PWM 信号输出 */
        rt_pwm_set(pwm_dev, PWM_SERVO_YAW, 20000000, yaw_pwm);   			
        rt_pwm_set(pwm_dev, PWM_SERVO_PITCH, 20000000, pitch_pwm);
        
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

