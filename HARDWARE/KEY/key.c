#include "key.h"
#include "delay.h"
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

//������ʼ������
void KEY_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;

    __HAL_RCC_GPIOB_CLK_ENABLE(); //����GPIOBʱ��

    GPIO_Initure.Pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15; //PA0
    GPIO_Initure.Mode = GPIO_MODE_INPUT;                                      //����
    GPIO_Initure.Pull = GPIO_PULLDOWN;                                        //����
    GPIO_Initure.Speed = GPIO_SPEED_HIGH;                                     //����
    HAL_GPIO_Init(GPIOB, &GPIO_Initure);
}

//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//0��û���κΰ�������
//1��WKUP���� KEY_DOWN
//ע��˺�������Ӧ���ȼ�,KEY_LEFT>KEKEY_LEFTEY2>KEY_DOWN!!
u8 KEY_Scan(u8 mode)
{
    static u8 key_up = 1; //�����ɿ���־
    if (mode == 1)
        key_up = 1; //֧������
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
    return 0; //�ް�������
}
