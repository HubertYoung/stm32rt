#ifndef _LED_H
#define _LED_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/9/7
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

#define SYS_LED        PCout(13)   	//LED0
#define TEST_LED        PCout(14)   	//LED0
#define SYS_LED_Pin                 GPIO_PIN_13
#define SYS_LED_GPIO_Port           GPIOC
// #define LED1 PFout(10)   	//LED1
// #define TEST_Pin GPIO_PIN_14
// #define TEST_GPIO_Port GPIOC

void LED_Init(void);
#endif
