#include "key.h"

#include "button.h"

Button_t button1;


/* 按键1处理 */
uint8_t Read_Button1_Level(void)
{
    return rt_pin_read(KEY_GREEN_PIN);
}


void Btn1_Dowm_CallBack(void *btn)
{
    rt_kprintf("Button1 once press\n");
}

void Btn1_Double_CallBack(void *btn)
{
    rt_kprintf("Button1 double press\n");
}


/*--------------------------  数据处理线程  ---------------------------*/

static void key_thread_entry(void *parameter)
{
    rt_pin_mode(KEY_OUTPUT_PIN, PIN_MODE_OUTPUT_OD);
    
    rt_pin_mode(KEY_GREEN_PIN, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(KEY_YELLOW1_PIN, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(KEY_YELLOW2_PIN, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(KEY_RED_PIN, PIN_MODE_INPUT_PULLUP);
    
    rt_pin_write(KEY_OUTPUT_PIN, PIN_LOW);
    
    
    Button_Create("button1", &button1, Read_Button1_Level, PIN_LOW);
    
    Button_Attach(&button1, BUTTON_DOWM, Btn1_Dowm_CallBack);
    Button_Attach(&button1, BUTTON_DOUBLE, Btn1_Double_CallBack);

    
    Get_Button_Event(&button1);

    while (1)
    {
//        key.green = rt_pin_read(KEY_GREEN_PIN);
//        key.yellow1 = rt_pin_read(KEY_YELLOW1_PIN);
//        key.yellow2 = rt_pin_read(KEY_YELLOW2_PIN);
//        key.red = rt_pin_read(KEY_RED_PIN);
        
        Button_Process();
        
        rt_thread_mdelay(25);
    }
}

int key_init(void)
{
    rt_err_t ret = RT_EOK;

    /* 创建 serial 线程 */
    rt_thread_t thread = rt_thread_create("key", 
                                        key_thread_entry, 
                                        RT_NULL, 
                                        KEY_THREAD_STACK_SIZE, 
                                        KEY_THREAD_PRIORITY, 
										KEY_THREAD_TIMESLICE);
    
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
INIT_APP_EXPORT(key_init);





