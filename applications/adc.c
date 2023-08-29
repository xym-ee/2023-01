#include "adc.h"
#include "railgun.h"

#define ADC_DEV_NAME        "adc1"      /* ADC 设备名称 */
#define ADC_DEV_CHANNEL     5                            /* ADC 通道 */
#define REFER_VOLTAGE       33          /* 参考电压 3.3V,数据精度乘以10保留1位小数*/
#define CONVERT_BITS        (1 << 12)   /* 转换位数为12位 */



rt_uint32_t voltage = 0;


void bubble_sort(rt_uint32_t *arr, int size)
{
    rt_uint32_t i, j, tmp;
    for (i = 0; i < size - 1; i++)
    {
        for (j = 0; j < size - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}


/*--------------------------  数据处理线程  ---------------------------*/

static void adc_thread_entry(void *parameter)
{
    rt_adc_device_t adc_dev;
    
    rt_uint32_t value[7];

    adc_dev = (rt_adc_device_t)rt_device_find(ADC_DEV_NAME);
    
    if (adc_dev == RT_NULL)
    {
        rt_kprintf("adc sample run failed! can't find %s device!\n", ADC_DEV_NAME);
    }
    
    rt_adc_enable(adc_dev, ADC_DEV_CHANNEL);
    
    while (1)
    {
        value[0] = rt_adc_read(adc_dev, ADC_DEV_CHANNEL);
        value[1] = rt_adc_read(adc_dev, ADC_DEV_CHANNEL);
        value[2] = rt_adc_read(adc_dev, ADC_DEV_CHANNEL);
        value[3] = rt_adc_read(adc_dev, ADC_DEV_CHANNEL);
        value[4] = rt_adc_read(adc_dev, ADC_DEV_CHANNEL);
        value[5] = rt_adc_read(adc_dev, ADC_DEV_CHANNEL);
        value[6] = rt_adc_read(adc_dev, ADC_DEV_CHANNEL);
        
        bubble_sort(value, 7);
        
        voltage = value[3] * REFER_VOLTAGE * 69 / CONVERT_BITS ;
        
        /* 电容电压过高，强制停止充电 */
        if (voltage > 1200)
        {
            rt_pin_write(CHARGE_PIN, PIN_HIGH);
        }

        rt_thread_mdelay(10);
    }
}

int adc_init(void)
{
    rt_err_t ret = RT_EOK;

    /* 创建 serial 线程 */
    rt_thread_t thread = rt_thread_create("adc", 
                                        adc_thread_entry, 
                                        RT_NULL, 
                                        ADC_THREAD_STACK_SIZE, 
                                        ADC_THREAD_PRIORITY, 
										ADC_THREAD_TIMESLICE);
    
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
INIT_APP_EXPORT(adc_init);




