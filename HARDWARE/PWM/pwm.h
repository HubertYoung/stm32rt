#ifndef _PWM_H
#define _PWM_H
#include "sys.h"

// extern TIM_HandleTypeDef TIM2_Handler;      //定时器句柄

// void TIM2_Init(u16 arr,u16 psc);
void TIM1_PWM_Init(u16 arr, u16 psc);
void TIM_SetTIM1Compare1(u32 compare);
void TIM_SetTIM1AutoReload(u32 arr, u32 ccr);
#endif
