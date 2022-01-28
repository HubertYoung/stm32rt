

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "FreeRTOS.h"
#include "task.h"
#include "usmart.h"
// #include "driver_ssd1306_basic.h"
// #include "driver_ssd1306_091.h"

#include "oled.h"
#include "iic.h"
#include "SOLGUI_Include.h"

#include "pwm.h"

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
#define SYS_STK_SIZE 128
//任务句柄
TaskHandle_t SYSTask_Handler;
//任务函数
void sys_task(void *pvParameters);

//任务优先级
#define KEY_TASK_PRIO 3
//任务堆栈大小
#define KEY_STK_SIZE 128
//任务句柄
TaskHandle_t KEYTask_Handler;
//任务函数
void key_task(void *pvParameters);

//任务优先级
#define GUI_TASK_PRIO 4
//任务堆栈大小
#define GUI_STK_SIZE 50
//任务句柄
TaskHandle_t GUITask_Handler;
//任务函数
void gui_task(void *pvParameters);
uint8_t res;
u32 switch_reg = 0;
MENU_PAGE wifi_list, wifi_init, wifi_conn, tcp_conn, senddata;

__M_PAGE(wifi_list, "wifi_list", PAGE_NULL,
         {
             SOLGUI_Cursor(6, 0, 4);
             SOLGUI_Widget_GotoPage(0, &wifi_init);
             SOLGUI_Widget_GotoPage(1, &wifi_conn);
             SOLGUI_Widget_GotoPage(2, &tcp_conn);
             SOLGUI_Widget_GotoPage(3, &senddata);
         });
__M_PAGE(wifi_init, "wifi_init", &wifi_list,
         {
             SOLGUI_Cursor(0, 0, 1);
             SOLGUI_Widget_Switch(0, "WIFI init ON/OFF", &switch_reg, 0);
         });
__M_PAGE(wifi_conn, "wifi_conn", &wifi_list,
         {
             SOLGUI_Cursor(0, 0, 1);
             SOLGUI_Widget_Switch(0, "WIFI connection ON/OFF", &switch_reg, 1);
         });
__M_PAGE(tcp_conn, "tcp_conn", &wifi_list,
         {
             SOLGUI_Cursor(0, 0, 1);
             SOLGUI_Widget_Switch(0, "TCP connection ON/OFF", &switch_reg, 2);
         });
__M_PAGE(senddata, "senddata", &wifi_list,
         {
             SOLGUI_Cursor(0, 0, 1);
             SOLGUI_Widget_Switch(0, "send mode ON/OFF", &switch_reg, 3);
         });
int main(void)
{
    HAL_Init();                      //初始化HAL库
    Stm32_Clock_Init(168, 25, 2, 4); //设置时钟,84
    delay_init(84);                  //初始化延时函数
    LED_Init();                      //初始化LED
    KEY_Init();                      //初始化LED
    uart_init(115200);               //初始化串口
    usmart_dev.init(84);             //初始化USMART

    SOLGUI_Init(&wifi_list);
    // SOLGUI_Cursor(6,0,4);
    // SOLGUI_printf(SCREEN_X_WIDTH-6,56,F6X8,"%c",0x84);			//操作指示（根据键值解析部分来编写）
    //目的达到24khz 设置2分频 84M/(pcs * aar) = 24kHz
    // 2000    -> 1K
    // 20      -> 100k,如果进度值为0.5k, 每次减少10
    // 默认24k 应该是 1770
    TIM2_PWM_Init(500 - 1, 42 - 1); //84M/84=1M的计数频率1us，自动重装载为500，那么PWM频率为1M/500=2kHZ
    // OLED_Init();                    //初始化OLED
    // OLED_Clear();
    // OLED_ShowString(0, 0, "FOSTEX", 24);
    // OLED_ShowString(0, 24, "MODEL 20", 24);

    // shell_init();
    // shell_register("ssd1306", ssd1306);
    // res = ssd1306_basic_init(SSD1306_INTERFACE_IIC, SSD1306_ADDR_SA0_0);
    // if (res)
    // {
    //     ssd1306_basic_deinit();

    //     return 1;
    // }

    // ssd1306_basic_string(0, 0, "FOSTEX", sizeof("FOSTEX"), 1, SSD1306_FONT_24);
    // ssd1306_basic_string(0, 24, "MODEL 20", sizeof("MODEL 20"), 1, SSD1306_FONT_24);

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
    // xTaskCreate((TaskFunction_t)key_task,
    //             (const char *)"key_task",
    //             (uint16_t)KEY_STK_SIZE,
    //             (void *)NULL,
    //             (UBaseType_t)KEY_TASK_PRIO,
    //             (TaskHandle_t *)&KEYTask_Handler);
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
        // key = KEY_Scan(0); //按键扫描
        // switch (key)
        // {
        // case KEY_LEFT_PRES: {}
        //     TEST_LED = !TEST_LED;
        //     	 /* run reg test */
        //     // ssd1306_display_test(SSD1306_INTERFACE_IIC, SSD1306_ADDR_SA0_0);

        //     break;
        // case KEY_RIGHT_PRES:
        //     TEST_LED = !TEST_LED;
        //     break;
        // }
        vTaskDelay(1000);
    }
}

void gui_task(void *pvParameters)
{
    u8 key = 0;
    // ssd1306_basic_clear();
    while (1)
    {
        // GUI_Refresh();Not enough information to list image symbols.
        // test();
        key = KEY_Scan(0);
        SOLGUI_InputKey(key);
        SOLGUI_Menu_PageStage();
        SOLGUI_Refresh();
        TEST_LED = ~TEST_LED;
        vTaskDelay(100);
    }
}
