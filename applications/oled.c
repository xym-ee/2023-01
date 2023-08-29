#include "oled.h"
#include "status.h"

#include "adc.h"

/*--------------------------  数据处理线程  ---------------------------*/

static void oled_thread_entry(void *parameter)
{
    ssd1306_Init();
    ssd1306_Fill(Black);
    ssd1306_SetCursor(2, 0);
    ssd1306_WriteString("V:   . ", Font_16x26, White);
    ssd1306_SetCursor(2, 26);
    ssd1306_WriteString("MODE:MANUAL", Font_11x18, White);
    ssd1306_UpdateScreen();
    
    char txt[20];

    rt_uint32_t vol = 0;
    
    while (1)
    {
        /* 充电电压显示 */
        vol = voltage;
        
        rt_sprintf(txt, "%d", vol%10);
        ssd1306_SetCursor(2 + 6*16, 0);
        ssd1306_WriteString(txt, Font_16x26, White);
        
        rt_sprintf(txt, "%3d", vol/10);
        ssd1306_SetCursor(2 + 2*16, 0);
        ssd1306_WriteString(txt, Font_16x26, White);
        
        
        if (status.control_mode == MANUAL)
        {
            rt_sprintf(txt, "MANUAL");
        }
        else
        {
            rt_sprintf(txt, "  AUTO");
        }
        ssd1306_SetCursor(2 + 5*11, 26);
        ssd1306_WriteString(txt, Font_11x18, White);
        
        ssd1306_UpdateScreen();

        rt_thread_mdelay(700);

    }
}

int oled_init(void)
{
    rt_err_t ret = RT_EOK;

    /* 创建 serial 线程 */
    rt_thread_t thread = rt_thread_create("oled", 
                                        oled_thread_entry, 
                                        RT_NULL, 
                                        OLED_THREAD_STACK_SIZE, 
                                        OLED_THREAD_PRIORITY, 
										OLED_THREAD_TIMESLICE);
    
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
INIT_APP_EXPORT(oled_init);





