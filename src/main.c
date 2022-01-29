

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
#include "SOLGUI_Hardware.h"

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
#define SYS_TASK_PRIO 4
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
#define GUI_TASK_PRIO 2
//任务堆栈大小
#define GUI_STK_SIZE 256
//任务句柄
TaskHandle_t GUITask_Handler;
//任务函数
void gui_task(void *pvParameters);
uint8_t res;
u32 switch_reg = 0;

char pic_choose = 1;
float CarAngle; //车模倾角
float CarSpeed; //加速度计角度
char* test_str = "123123"; //加速度计角度
MENU_PAGE main_page, pwm_init, wifi_conn, tcp_conn, senddata;

__M_PAGE(main_page, "MainPage", PAGE_NULL,
         {
             //  SOLGUI_Cursor(6, 5, 3);
             //  SOLGUI_Widget_Button(0, "1.f_mount", SD_f_mount_test); //按键
             // //  SOLGUI_Widget_Button(1, "2.f_write", SD_f_write_test); //按键
             // //  SOLGUI_Widget_Button(2, "3.f_open", SD_f_open_test);   //按键
             //  SOLGUI_Widget_Text(0, 32, ~F6X8, "S=%d,r=%d,C=%d", 1, 1, 1);
             //  SOLGUI_Widget_Text(0, 24, F6X8, "%s", "2");
             //  SOLGUI_Widget_Text(0, 16, F6X8, "%s", "2" + 21);
             //  SOLGUI_Widget_Text(0, 8, F6X8, "%s", "2" + 42);
             //  SOLGUI_Widget_Text(0, 0, F6X8, "%s", "2" + 63);
             SOLGUI_Cursor(6, 0, 7);
             SOLGUI_Widget_GotoPage(0, &pwm_init);
             SOLGUI_Widget_GotoPage(1, &wifi_conn);
             SOLGUI_Widget_GotoPage(2, &tcp_conn);
             SOLGUI_Widget_Edit(3,"edit",4,test_str);								//文本编辑器
             SOLGUI_Widget_OptionText(4, "angle:  %f", 12.2);
             SOLGUI_Widget_OptionText(5, "angle:  %f", 12.2);
             SOLGUI_Widget_OptionText(6, "speed:  %f", 12.2);
         });
__M_PAGE(pwm_init, "PWMPage", &main_page,
         {
             SOLGUI_Cursor(6, 0, 1);
             SOLGUI_Widget_Spin(0, "SP_SET", FLT32, -8000, 8000, &pic_choose);
         });
__M_PAGE(wifi_conn, "wifi_conn", &main_page,
         {
             SOLGUI_Cursor(0, 0, 1);

             //  SOLGUI_Widget_OptionText(4, "angle:  %f", CarAngle);
         });
__M_PAGE(tcp_conn, "tcp_conn", &main_page,
         {
             SOLGUI_Cursor(0, 0, 1);

             //  SOLGUI_Widget_OptionText(5, "speed:  %f", CarSpeed);
         });
__M_PAGE(senddata, "senddata", &main_page,
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

    //目的达到24khz 设置2分频 84M/(pcs * aar) = 24kHz
    // 2000    -> 1K
    // 20      -> 100k,如果进度值为0.5k, 每次减少10
    // 默认24k 应该是 1770
    TIM2_PWM_Init(500 - 1, 42 - 1); //84M/84=1M的计数频率1us，自动重装载为500，那么PWM频率为1M/500=2kHZ
    // EC11_Init();
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

        vTaskDelay(1000);
    }
}

void gui_task(void *pvParameters)
{
    u8 key = 0;

    SOLGUI_Hardware_Init();

    SOLGUI_printf(0, 24, F8X10, "FOSTEX");
    SOLGUI_printf(0, 48, F8X10, "MODLE 20");
    SOLGUI_Refresh();

    delay_ms(1000);
    SOLGUI_Menu_SetHomePage(&main_page);
    SOLGUI_Menu_PageStage();
    SOLGUI_Refresh();
    while (1)
    {
        u8 temp_key = KEY_Scan(0);
        if (key != temp_key)
        {
            key = temp_key;
            SOLGUI_InputKey(key);
            SOLGUI_Menu_PageStage();
            SOLGUI_Refresh();
        }

        TEST_LED = ~TEST_LED;
        vTaskDelay(10);
    }
}
