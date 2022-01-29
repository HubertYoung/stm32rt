#ifndef _KEY_H
#define _KEY_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//KEY��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2017/4/6
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////

//����ķ�ʽ��ͨ��λ��������ʽ��ȡIO
//#define KEY_LEFT        PHin(3) //KEY_LEFT����PH3
//#define KEY_UP        PHin(2) //KEY_UP����PH2
//#define KEY_RIGHT        PCin(13)//KEY_RIGHT����PC13
//#define KEY_DOWN       PAin(0) //WKUP����PA0


#define KEY_LEFT_Pin GPIO_PIN_12
#define KEY_LEFT_GPIO_Port GPIOB
#define KEY_UP_Pin GPIO_PIN_13
#define KEY_UP_GPIO_Port GPIOB
#define KEY_RIGHT_Pin GPIO_PIN_14
#define KEY_RIGHT_GPIO_Port GPIOB
#define KEY_DOWN_Pin GPIO_PIN_15
#define KEY_DOWN_GPIO_Port GPIOB

//����ķ�ʽ��ͨ��ֱ�Ӳ���HAL�⺯����ʽ��ȡIO
#define KEY_LEFT        HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_14)  //KEY0����PE4
#define KEY_UP        HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_12)  //KEY1����PE3
#define KEY_RIGHT        HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_15) 	//KEY2����PE2
#define KEY_DOWN       HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_13)  //WKUP����PA0

#define KEY_OK       HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_6)  //okPA0
#define KEY_BACK       HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)  //UKEYPA0

#define KEY_LEFT_PRES 	0x30
#define KEY_UP_PRES	0x50
#define KEY_RIGHT_PRES	0x10
#define KEY_DOWN_PRES   0x20

#define KEY_OK_PRES   0x40
#define KEY_BACK_PRES   0x60

void KEY_Init(void);
u8 KEY_Scan(u8 mode);
#endif
