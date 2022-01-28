#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"


// extern TIM_HandleTypeDef TIM2_Handler;      //定时器句柄 

// void TIM2_Init(u16 arr,u16 psc);
void TIM2_PWM_Init(u16 arr,u16 psc);
void TIM_SetTIM2Compare2(u32 compare);
#endif

