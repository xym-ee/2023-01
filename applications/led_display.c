#include "led_display.h"
#include "key.h"
#include "orangepi.h"


static void display_number(rt_int16_t num);
static void display_clear(void);
void display_wait(void);

/*--------------------------  数据处理线程  ---------------------------*/

static void display_thread_entry(void *parameter)
{
    rt_uint32_t i = 0;
    
    rt_uint8_t read_flag = 0;
    
    rt_pin_mode(SM16106_PIN_OE, PIN_MODE_OUTPUT);
    rt_pin_mode(SM16106_PIN_CK, PIN_MODE_OUTPUT);
    rt_pin_mode(SM16106_PIN_DI, PIN_MODE_OUTPUT);
    rt_pin_mode(SM16106_PIN_LE, PIN_MODE_OUTPUT);
    
        
    
    while (1)
    {
        /* 视觉计数逻辑 */
        switch (counter)
        {
            case '1': i++; counter = '0'; display_number(i); break;                     //计数触发
            case 's': display_wait(); display_clear(); break;       //初始状态，等待上位机启动
            case 'r': display_number(0); break;
            default:;
        }
        
        /* 按键清理逻辑 */
        if (key.green == 0)
        {
            i=0;
            display_number(i);
        }
        
        
        /* 计时设置逻辑 */
        

        
        rt_thread_mdelay(50);
    }
}

int display_init(void)
{
    rt_err_t ret = RT_EOK;

    /* 创建 serial 线程 */
    rt_thread_t thread = rt_thread_create("display", 
                                        display_thread_entry, 
                                        RT_NULL, 
                                        DISPLAY_THREAD_STACK_SIZE, 
                                        DISPLAY_THREAD_PRIORITY, 
										DISPLAY_THREAD_TIMESLICE);
    
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
INIT_APP_EXPORT(display_init);



/*---------------------------- sm16016 驱动 ---------------------------------------*/

static void _sm16106_write_byte(rt_uint8_t data)
{
    for (int i=0; i<8; i++)
    {
        rt_pin_write(SM16106_PIN_CK, PIN_LOW);
        
        if (data&0x80)
            rt_pin_write(SM16106_PIN_DI, PIN_HIGH);
        else
            rt_pin_write(SM16106_PIN_DI, PIN_LOW);
        
        data <<= 1;
        
        rt_pin_write(SM16106_PIN_CK, PIN_HIGH);
    }
}

static void _sm16106_output_enable(void)
{
    rt_pin_write(SM16106_PIN_OE, PIN_LOW);     
}

static void _sm16106_output_disable(void)
{
    rt_pin_write(SM16106_PIN_OE, PIN_HIGH);
}

static void _sm16106_data_lock(void)
{
    rt_pin_write(SM16106_PIN_LE, PIN_LOW);
    rt_pin_write(SM16106_PIN_LE, PIN_HIGH);
    rt_pin_write(SM16106_PIN_LE, PIN_LOW);
}

static void display_clear(void)
{
    _sm16106_output_disable();
    
    _sm16106_write_byte(0x00);
    _sm16106_write_byte(0x00);
    _sm16106_write_byte(0x00);
    _sm16106_write_byte(0x00);
    
    _sm16106_data_lock();
    
    _sm16106_output_enable();
    
}

static void display_all(void)
{
    _sm16106_output_disable();
    
    _sm16106_write_byte(0xff);
    _sm16106_write_byte(0xff);
    _sm16106_write_byte(0xff);
    _sm16106_write_byte(0xff);
    
    _sm16106_data_lock();
    
    _sm16106_output_enable();
}


const rt_uint8_t seg_code[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};


// 0 ~ 9999
static void display_number(rt_int16_t num)
{
    rt_uint8_t seg_code_output[4] = {0x00, 0x00, 0x00, 0x00};
    
    if (num>999)
    {
        seg_code_output[3] = seg_code[num%10];
        seg_code_output[2] = seg_code[(num/10)%10];
        seg_code_output[1] = seg_code[(num/100)%10];
        seg_code_output[0] = seg_code[(num/1000)%10];
    }
    else if(num>99)
    {
        seg_code_output[3] = seg_code[num%10];
        seg_code_output[2] = seg_code[(num/10)%10];
        seg_code_output[1] = seg_code[(num/100)%10];
        seg_code_output[0] = 0x00;    
    }
    else if(num>9)
    {
        seg_code_output[3] = seg_code[num%10];
        seg_code_output[2] = seg_code[(num/10)%10];
        seg_code_output[1] = 0x00;
        seg_code_output[0] = 0x00;
    }
    else
    {
        seg_code_output[3] = seg_code[num%10];
        seg_code_output[2] = 0x00;
        seg_code_output[1] = 0x00;
        seg_code_output[0] = 0x00;    
    }
    
    _sm16106_output_disable();
    _sm16106_write_byte(seg_code_output[0]); //千位
    _sm16106_write_byte(seg_code_output[1]); //百位
    _sm16106_write_byte(seg_code_output[2]); //十位
    _sm16106_write_byte(seg_code_output[3]); //个位
    _sm16106_data_lock();
    _sm16106_output_enable();    
}


void display_wait(void)
{
    _sm16106_output_disable();
    _sm16106_write_byte(0x40);
    _sm16106_data_lock();
    _sm16106_output_enable(); 

    rt_thread_mdelay(250);
    
    _sm16106_output_disable();
    _sm16106_write_byte(0x40);
    _sm16106_data_lock();
    _sm16106_output_enable(); 
    
    rt_thread_mdelay(250);
    
    _sm16106_output_disable();
    _sm16106_write_byte(0x40);
    _sm16106_data_lock();
    _sm16106_output_enable();  
    
    rt_thread_mdelay(250);
    
    _sm16106_output_disable();
    _sm16106_write_byte(0x40);
    _sm16106_data_lock();
    _sm16106_output_enable(); 

    rt_thread_mdelay(250);
}



