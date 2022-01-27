#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "FreeRTOS.h"
#include "task.h"
#include "usmart.h"
#include "test.h"


//任务优先级
#define START_TASK_PRIO 1
//任务堆栈大小
#define START_STK_SIZE 128
//任务句柄
TaskHandle_t StartTask_Handler;
//任务函数
void start_task(void *pvParameters);

//任务优先级
#define SYS_TASK_PRIO 2
//任务堆栈大小
#define SYS_STK_SIZE 50
//任务句柄
TaskHandle_t SYSTask_Handler;
//任务函数
void sys_task(void *pvParameters);

//任务优先级
#define KEY_TASK_PRIO 3
//任务堆栈大小
#define KEY_STK_SIZE 50
//任务句柄
TaskHandle_t KEYTask_Handler;
//任务函数
void key_task(void *pvParameters);

//任务优先级
#define GUI_TASK_PRIO 4
//任务堆栈大小
#define GUI_STK_SIZE 128
//任务句柄
TaskHandle_t GUITask_Handler;
//任务函数
void gui_task(void *pvParameters);
uint8_t res;
int main(void)
{
    HAL_Init();                      //初始化HAL库
    Stm32_Clock_Init(168, 25, 2, 4); //设置时钟,84
    delay_init(84);                  //初始化延时函数
    LED_Init();                      //初始化LED
    KEY_Init();                      //初始化LED
    uart_init(115200);              //初始化串口
    usmart_dev.init(84); 		    //初始化USMART	
    // shell_init();
    // shell_register("ssd1306", ssd1306);
    res = ssd1306_basic_init(SSD1306_INTERFACE_IIC, SSD1306_ADDR_SA0_0);
    if (res)
    {
        ssd1306_basic_deinit();

        return 1;
    }
    res = ssd1306_basic_string(0, 0, "123", 3, 1, SSD1306_FONT_16);
    if (res)
    {
        ssd1306_interface_debug_print("ssd1306: show string failed.\n");
        ssd1306_basic_deinit();

        return 1;
    }

    res = ssd1306_basic_rect(0, 31, 31, 31, 1);
    if (res)
    {
        ssd1306_basic_deinit();

        return 1;
    }

    //创建开始任务
    xTaskCreate((TaskFunction_t)start_task,          //任务函数
                (const char *)"start_task",          //任务名称
                (uint16_t)START_STK_SIZE,            //任务堆栈大小
                (void *)NULL,                        //传递给任务函数的参数
                (UBaseType_t)START_TASK_PRIO,        //任务优先级
                (TaskHandle_t *)&StartTask_Handler); //任务句柄
    vTaskStartScheduler();                           //开启任务调度
}

//开始任务任务函数
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL(); //进入临界区
    //创建SYS任务
    xTaskCreate((TaskFunction_t)sys_task,
                (const char *)"sys_task",
                (uint16_t)SYS_STK_SIZE,
                (void *)NULL,
                (UBaseType_t)SYS_TASK_PRIO,
                (TaskHandle_t *)&SYSTask_Handler);
    //创建KEY任务
    xTaskCreate((TaskFunction_t)key_task,
                (const char *)"key_task",
                (uint16_t)KEY_STK_SIZE,
                (void *)NULL,
                (UBaseType_t)KEY_TASK_PRIO,
                (TaskHandle_t *)&KEYTask_Handler);
    //浮点测试任务
    xTaskCreate((TaskFunction_t)gui_task,
                (const char *)"gui_task",
                (uint16_t)GUI_STK_SIZE,
                (void *)NULL,
                (UBaseType_t)GUI_TASK_PRIO,
                (TaskHandle_t *)&GUITask_Handler);
    printf("start_task is finished, other tasks start\n");
    vTaskDelete(StartTask_Handler); //删除开始任务
    taskEXIT_CRITICAL();            //退出临界区
}

// SYS任务函数
void sys_task(void *pvParameters)
{
    while (1)
    {
        SYS_LED = 1;
        vTaskDelay(300);
        SYS_LED = 0;
        vTaskDelay(600);
    }
}

// KEY任务函数
void key_task(void *pvParameters)
{
    u8 key;
    while (1)
    {
        key = KEY_Scan(0); //按键扫描
        switch (key)
        {
        case KEY_LEFT_PRES:
            TEST_LED = !TEST_LED;
            break;
        case KEY_RIGHT_PRES:
            TEST_LED = !TEST_LED;
            break;
        }
        vTaskDelay(50);
    }
}

//浮点测试任务
void gui_task(void *pvParameters)
{

    while (1)
    {
       
        vTaskDelay(1000);
    }
}
