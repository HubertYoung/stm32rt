#include "pwm.h"
#include "pwm.h"
#include "w25qxx.h"

TIM_HandleTypeDef TIM1_Handler;     //定时器句柄
TIM_OC_InitTypeDef TIM1_CH1Handler; //定时器2通道2句柄

//TIM1 PWM部分初始化
//arr：自动重装值。
//psc：时钟预分频数
//定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=定时器工作频率,单位:Mhz
void TIM1_PWM_Init(u16 arr, u16 psc)
{
    TIM1_Handler.Instance = TIM1;                       //定时器14
    TIM1_Handler.Init.Prescaler = psc;                  //定时器分频
    TIM1_Handler.Init.CounterMode = TIM_COUNTERMODE_UP; //向上计数模式
    TIM1_Handler.Init.Period = arr;                     //自动重装载值
    TIM1_Handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&TIM1_Handler); //初始化PWM

    TIM1_CH1Handler.OCMode = TIM_OCMODE_PWM1;                                  //模式选择PWM1
    TIM1_CH1Handler.Pulse = arr / 2 + 1;                                       //设置比较值,此值用来确定占空比，默认比较值为自动重装载值的一半,即占空比为50%
    TIM1_CH1Handler.OCPolarity = TIM_OCPOLARITY_LOW;                           //输出比较极性为低
    TIM1_CH1Handler.OCIdleState = TIM_OCIDLESTATE_SET;                         //输出比较极性为低
    HAL_TIM_PWM_ConfigChannel(&TIM1_Handler, &TIM1_CH1Handler, TIM_CHANNEL_1); //配置TIM1通道1

    HAL_TIM_PWM_Start(&TIM1_Handler, TIM_CHANNEL_1); //开启PWM通道1
}

//定时器底层驱动，时钟使能，引脚配置
//此函数会被HAL_TIM_PWM_Init()调用
//htim:定时器句柄
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_TIM1_CLK_ENABLE();  //使能定时器2
    __HAL_RCC_GPIOA_CLK_ENABLE(); //开启GPIOA时钟

    GPIO_Initure.Pin = GPIO_PIN_8;          //PA1
    GPIO_Initure.Mode = GPIO_MODE_AF_PP;    //复用推挽输出
    GPIO_Initure.Pull = GPIO_PULLDOWN;      //上拉
    GPIO_Initure.Speed = GPIO_SPEED_HIGH;   //高速
    GPIO_Initure.Alternate = GPIO_AF1_TIM1; //PA1复用为TIM1_CH2
    HAL_GPIO_Init(GPIOA, &GPIO_Initure);
}

//设置TIM通道2的占空比
//compare:比较值
void TIM_SetTIM1Compare2(u32 compare)
{
    __HAL_TIM_SetCompare(&TIM1_Handler, TIM_CHANNEL_1, compare);
    // U32ToU8Array(compare);
    u8 e[4];
    U32ToU8Array(e, compare);
    W25QXX_Write(e, PWM_CCR, 4);
}
void TIM_SetTIM1AutoReload(u32 arr, u32 ccr)
{
    __HAL_TIM_SET_AUTORELOAD(&TIM1_Handler, arr);
    TIM_SetTIM1Compare2(ccr);
    u8 e[4];
    U32ToU8Array(e, arr);
    W25QXX_Write(e, PWM_ARR, 4);
}
//定时器2中断服务函数
void TIM1_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TIM1_Handler);
}

//回调函数，定时器中断服务函数调用
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim == (&TIM1_Handler))
    {
        //        LED1=!LED1;        //LED1反转
    }
}
