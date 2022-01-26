#include "key.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//KEY驱动代码
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2017/4/6
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////

//按键初始化函数
void KEY_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;

    __HAL_RCC_GPIOB_CLK_ENABLE(); //开启GPIOB时钟

    GPIO_Initure.Pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15; //PA0
    GPIO_Initure.Mode = GPIO_MODE_INPUT;                                      //输入
    GPIO_Initure.Pull = GPIO_PULLDOWN;                                        //下拉
    GPIO_Initure.Speed = GPIO_SPEED_HIGH;                                     //高速
    HAL_GPIO_Init(GPIOB, &GPIO_Initure);
}

//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//1，WKUP按下 KEY_DOWN
//注意此函数有响应优先级,KEY_LEFT>KEKEY_LEFTEY2>KEY_DOWN!!
u8 KEY_Scan(u8 mode)
{
    static u8 key_up = 1; //按键松开标志
    if (mode == 1)
        key_up = 1; //支持连按
    if (key_up && (KEY_LEFT == 1 || KEY_UP == 1 || KEY_RIGHT == 1 || KEY_DOWN == 1))
    {
        delay_ms(10);
        key_up = 0;
        if (KEY_LEFT == 1)
            return KEY_LEFT_PRES;
        else if (KEY_UP == 1)
            return KEY_UP_PRES;
        else if (KEY_RIGHT == 1)
            return KEY_RIGHT_PRES;
        else if (KEY_DOWN == 1)
            return KEY_DOWN_PRES;
    }
    else if (KEY_LEFT == 0 && KEY_UP == 0 && KEY_RIGHT == 0 && KEY_DOWN == 0)
        key_up = 1;
    return 0; //无按键按下
}
