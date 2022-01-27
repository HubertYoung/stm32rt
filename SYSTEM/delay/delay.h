#ifndef _DELAY_H
#define _DELAY_H
#include <sys.h>	  
//////////////////////////////////////////////////////////////////////////////////  
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F429开发板
//使用SysTick的普通计数模式对延迟进行管理(支持ucosii)
//包括delay_us,delay_ms
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2015/6/10
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved
//********************************************************************************
//修改说明
////////////////////////////////////////////////////////////////////////////////// 

void delay_init(u8 SYSCLK);
void delay_us(u32 nus);
void delay_ms(u32 nms);
// void delay_xms(u32 nms);

#endif

