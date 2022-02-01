#include "timer.h"
#include "Kalman.h"

TIM_HandleTypeDef TIM2_Handler; //定时器5句柄

Kalman kalman;
//定时器5通道1输入捕获配置
// arr：自动重装值(TIM2,TIM2是32位的!!)
// psc：时钟预分频数
void TIM2_CH2_Cap_Init(u32 arr, u16 psc)
{
    KalmanInit(&kalman);

    TIM_IC_InitTypeDef TIM2_CH2Config;

    TIM2_Handler.Instance = TIM2;                             //通用定时器5
    TIM2_Handler.Init.Prescaler = psc;                        //分频系数
    TIM2_Handler.Init.CounterMode = TIM_COUNTERMODE_UP;       //向上计数器
    TIM2_Handler.Init.Period = arr;                           //自动装载值
    TIM2_Handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1; //时钟分频银子
    HAL_TIM_IC_Init(&TIM2_Handler);                           //初始化输入捕获时基参数

    TIM2_CH2Config.ICPolarity = TIM_ICPOLARITY_RISING;                       //上升沿捕获
    TIM2_CH2Config.ICSelection = TIM_ICSELECTION_DIRECTTI;                   //映射到TI1上
    TIM2_CH2Config.ICPrescaler = TIM_ICPSC_DIV1;                             //配置输入分频，不分频
    TIM2_CH2Config.ICFilter = 0;                                             //配置输入滤波器，不滤波
    HAL_TIM_IC_ConfigChannel(&TIM2_Handler, &TIM2_CH2Config, TIM_CHANNEL_2); //配置TIM2通道1

    HAL_TIM_IC_Start_IT(&TIM2_Handler, TIM_CHANNEL_2); //开启TIM2的捕获通道1，并且开启捕获中断
    __HAL_TIM_ENABLE_IT(&TIM2_Handler, TIM_IT_UPDATE); //使能更新中断
}

//定时器5底层驱动，时钟使能，引脚配置
//此函数会被HAL_TIM_IC_Init()调用
// htim:定时器5句柄
void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_TIM2_CLK_ENABLE();  //使能TIM2时钟
    __HAL_RCC_GPIOA_CLK_ENABLE(); //开启GPIOA时钟

    GPIO_Initure.Pin = GPIO_PIN_1;          // PA0
    GPIO_Initure.Mode = GPIO_MODE_AF_PP;    //复用推挽输出
    GPIO_Initure.Pull = GPIO_PULLDOWN;      //下拉
    GPIO_Initure.Speed = GPIO_SPEED_HIGH;   //高速
    GPIO_Initure.Alternate = GPIO_AF1_TIM2; // PA0复用为TIM2通道1
    HAL_GPIO_Init(GPIOA, &GPIO_Initure);

    HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0); //设置中断优先级，抢占优先级2，子优先级0
    HAL_NVIC_EnableIRQ(TIM2_IRQn);         //开启ITM5中断通道
}

//捕获状态
//[7]:0,没有成功的捕获;1,成功捕获到一次.
//[6]:0,还没捕获到低电平;1,已经捕获到低电平了.
//[5:0]:捕获低电平后溢出的次数(对于32位定时器来说,1us计数器加1,溢出时间:4294秒)
u8 TIM2CH2_CAPTURE_STA = 0; //输入捕获状态
u32 TIM2CH2_CAPTURE_VAL;    //输入捕获值(TIM2/TIM2是32位)
u8 TIM_ICOF_MAX = 0x05;
u8 TIM_ICOF_COUNT = 0;
u32 FbFreq = 0;

u32 IC_Value1 = 0;
u32 IC_Value2 = 0;
u8 First_Captured = 0;
u32 difference = 0;
//定时器5中断服务函数
void TIM2_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TIM2_Handler); //定时器共用处理函数
}

//定时器更新中断（计数溢出）中断处理回调函数， 该函数在HAL_TIM_IRQHandler中会被调用
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) //更新中断（溢出）发生时执行
{
    if (TIM_ICOF_COUNT < TIM_ICOF_MAX)
    {
        TIM_ICOF_COUNT++;
    }
    else
    {
        FbFreq = 0;
        TIM_ICOF_COUNT = 0;
    }

    // if ((TIM2CH2_CAPTURE_STA & 0X80) == 0) //还未成功捕获
    // {
    //     if (TIM2CH2_CAPTURE_STA & 0X40) //已经捕获到高电平了
    //     {
    //         if ((TIM2CH2_CAPTURE_STA & 0X3F) == 0X3F) //高电平太长了
    //         {
    //             TIM2CH2_CAPTURE_STA |= 0X80; //标记成功捕获了一次
    //             TIM2CH2_CAPTURE_VAL = 0XFFFF;
    //         }
    //         else
    //             TIM2CH2_CAPTURE_STA++;
    //     }
    // }
}
#define N 5

char count;

u32 value_buf[N];

// uint32_t tmp1 = 0, tmp2 = 0;
//定时器输入捕获中断处理回调函数，该函数在HAL_TIM_IRQHandler中会被调用
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) //捕获中断发生时执行
{

    if (First_Captured == 0)
    {
        TIM_ICOF_COUNT = 0;
        IC_Value1 = HAL_TIM_ReadCapturedValue(&TIM2_Handler, TIM_CHANNEL_2);
        First_Captured = 1;
    }
    else if (First_Captured == 1)
    {

        IC_Value2 = HAL_TIM_ReadCapturedValue(&TIM2_Handler, TIM_CHANNEL_2);
        if (TIM_ICOF_COUNT == 0)
        {
            difference = IC_Value2 - IC_Value1;
        }
        else if (TIM_ICOF_COUNT == 1)
        { //溢出一个计数周期
            difference = (0xFFFF - IC_Value1) + IC_Value2;
        }
        else
        { //溢出N个计数周期
            difference = (0xFFFF - IC_Value1) + 0xFFFF * (TIM_ICOF_COUNT - 1) + IC_Value2;
        }
        // ProcessIcValue(TIM1_IC1, cap_sum);
        u32 now_freq = 1000000 / difference;

        if (count < N)
        {
            value_buf[count++] = now_freq;
        }
        else
        {

            u32 temp = 0;
            int i = 0, j = 0;
            for (j = 0; j < N - 1; j++)
            {
                for (i = 0; i < N - j; i++)
                {
                    if (value_buf[i] > value_buf[i + 1])
                    {
                        temp = value_buf[i];
                        value_buf[i] = value_buf[i + 1];
                        value_buf[i + 1] = temp;
                    }
                }
            }

            FbFreq = KalmanFilter(&kalman, value_buf[N / 2], FbFreq);
            count = 0;
        }

        First_Captured = 0;

        // if ((TIM2CH2_CAPTURE_STA & 0X80) == 0) //还未成功捕获
        // {
        //     if (TIM2CH2_CAPTURE_STA & 0X40) //捕获到一个下降沿
        //     {
        //         TIM2CH2_CAPTURE_STA |= 0X80;                                                   //标记成功捕获到一次高电平脉宽
        //         TIM2CH2_CAPTURE_VAL = HAL_TIM_ReadCapturedValue(&TIM2_Handler, TIM_CHANNEL_2); //获取当前的捕获值.
        //         TIM_RESET_CAPTUREPOLARITY(&TIM2_Handler, TIM_CHANNEL_2);                       //一定要先清除原来的设置！！
        //         TIM_SET_CAPTUREPOLARITY(&TIM2_Handler, TIM_CHANNEL_2, TIM_ICPOLARITY_RISING);  //配置TIM2通道1上升沿捕获
        //     }
        //     else //还未开始,第一次捕获上升沿
        //     {
        //         TIM2CH2_CAPTURE_STA = 0; //清空
        //         TIM2CH2_CAPTURE_VAL = 0;
        //         TIM2CH2_CAPTURE_STA |= 0X40;      //标记捕获到了上升沿
        //         __HAL_TIM_DISABLE(&TIM2_Handler); //关闭定时器5
        //         __HAL_TIM_SET_COUNTER(&TIM2_Handler, 0);
        //         TIM_RESET_CAPTUREPOLARITY(&TIM2_Handler, TIM_CHANNEL_2);                       //一定要先清除原来的设置！！
        //         TIM_SET_CAPTUREPOLARITY(&TIM2_Handler, TIM_CHANNEL_2, TIM_ICPOLARITY_FALLING); //定时器5通道1设置为下降沿捕获
        //         __HAL_TIM_ENABLE(&TIM2_Handler);                                               //使能定时器5
        //     }
        // }
    }
}