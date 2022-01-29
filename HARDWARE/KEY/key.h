#ifndef _KEY_H
#define _KEY_H
#include "sys.h"
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

//下面的方式是通过位带操作方式读取IO
//#define KEY_LEFT        PHin(3) //KEY_LEFT按键PH3
//#define KEY_UP        PHin(2) //KEY_UP按键PH2
//#define KEY_RIGHT        PCin(13)//KEY_RIGHT按键PC13
//#define KEY_DOWN       PAin(0) //WKUP按键PA0


#define KEY_LEFT_Pin GPIO_PIN_12
#define KEY_LEFT_GPIO_Port GPIOB
#define KEY_UP_Pin GPIO_PIN_13
#define KEY_UP_GPIO_Port GPIOB
#define KEY_RIGHT_Pin GPIO_PIN_14
#define KEY_RIGHT_GPIO_Port GPIOB
#define KEY_DOWN_Pin GPIO_PIN_15
#define KEY_DOWN_GPIO_Port GPIOB

//下面的方式是通过直接操作HAL库函数方式读取IO
#define KEY_LEFT        HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_14)  //KEY0按键PE4
#define KEY_UP        HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_12)  //KEY1按键PE3
#define KEY_RIGHT        HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_15) 	//KEY2按键PE2
#define KEY_DOWN       HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_13)  //WKUP按键PA0

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
