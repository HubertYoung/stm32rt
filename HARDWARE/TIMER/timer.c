#include "timer.h"
#include "Kalman.h"

TIM_HandleTypeDef TIM2_Handler; //��ʱ��5���

Kalman kalman;
//��ʱ��5ͨ��1���벶������
// arr���Զ���װֵ(TIM2,TIM2��32λ��!!)
// psc��ʱ��Ԥ��Ƶ��
void TIM2_CH2_Cap_Init(u32 arr, u16 psc)
{
    KalmanInit(&kalman);

    TIM_IC_InitTypeDef TIM2_CH2Config;

    TIM2_Handler.Instance = TIM2;                             //ͨ�ö�ʱ��5
    TIM2_Handler.Init.Prescaler = psc;                        //��Ƶϵ��
    TIM2_Handler.Init.CounterMode = TIM_COUNTERMODE_UP;       //���ϼ�����
    TIM2_Handler.Init.Period = arr;                           //�Զ�װ��ֵ
    TIM2_Handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1; //ʱ�ӷ�Ƶ����
    HAL_TIM_IC_Init(&TIM2_Handler);                           //��ʼ�����벶��ʱ������

    TIM2_CH2Config.ICPolarity = TIM_ICPOLARITY_RISING;                       //�����ز���
    TIM2_CH2Config.ICSelection = TIM_ICSELECTION_DIRECTTI;                   //ӳ�䵽TI1��
    TIM2_CH2Config.ICPrescaler = TIM_ICPSC_DIV1;                             //���������Ƶ������Ƶ
    TIM2_CH2Config.ICFilter = 0;                                             //���������˲��������˲�
    HAL_TIM_IC_ConfigChannel(&TIM2_Handler, &TIM2_CH2Config, TIM_CHANNEL_2); //����TIM2ͨ��1

    HAL_TIM_IC_Start_IT(&TIM2_Handler, TIM_CHANNEL_2); //����TIM2�Ĳ���ͨ��1�����ҿ��������ж�
    __HAL_TIM_ENABLE_IT(&TIM2_Handler, TIM_IT_UPDATE); //ʹ�ܸ����ж�
}

//��ʱ��5�ײ�������ʱ��ʹ�ܣ���������
//�˺����ᱻHAL_TIM_IC_Init()����
// htim:��ʱ��5���
void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_TIM2_CLK_ENABLE();  //ʹ��TIM2ʱ��
    __HAL_RCC_GPIOA_CLK_ENABLE(); //����GPIOAʱ��

    GPIO_Initure.Pin = GPIO_PIN_1;          // PA0
    GPIO_Initure.Mode = GPIO_MODE_AF_PP;    //�����������
    GPIO_Initure.Pull = GPIO_PULLDOWN;      //����
    GPIO_Initure.Speed = GPIO_SPEED_HIGH;   //����
    GPIO_Initure.Alternate = GPIO_AF1_TIM2; // PA0����ΪTIM2ͨ��1
    HAL_GPIO_Init(GPIOA, &GPIO_Initure);

    HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0); //�����ж����ȼ�����ռ���ȼ�2�������ȼ�0
    HAL_NVIC_EnableIRQ(TIM2_IRQn);         //����ITM5�ж�ͨ��
}

//����״̬
//[7]:0,û�гɹ��Ĳ���;1,�ɹ�����һ��.
//[6]:0,��û���񵽵͵�ƽ;1,�Ѿ����񵽵͵�ƽ��.
//[5:0]:����͵�ƽ������Ĵ���(����32λ��ʱ����˵,1us��������1,���ʱ��:4294��)
u8 TIM2CH2_CAPTURE_STA = 0; //���벶��״̬
u32 TIM2CH2_CAPTURE_VAL;    //���벶��ֵ(TIM2/TIM2��32λ)
u8 TIM_ICOF_MAX = 0x05;
u8 TIM_ICOF_COUNT = 0;
u32 FbFreq = 0;

u32 IC_Value1 = 0;
u32 IC_Value2 = 0;
u8 First_Captured = 0;
u32 difference = 0;
//��ʱ��5�жϷ�����
void TIM2_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TIM2_Handler); //��ʱ�����ô�����
}

//��ʱ�������жϣ�����������жϴ���ص������� �ú�����HAL_TIM_IRQHandler�лᱻ����
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) //�����жϣ����������ʱִ��
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

    // if ((TIM2CH2_CAPTURE_STA & 0X80) == 0) //��δ�ɹ�����
    // {
    //     if (TIM2CH2_CAPTURE_STA & 0X40) //�Ѿ����񵽸ߵ�ƽ��
    //     {
    //         if ((TIM2CH2_CAPTURE_STA & 0X3F) == 0X3F) //�ߵ�ƽ̫����
    //         {
    //             TIM2CH2_CAPTURE_STA |= 0X80; //��ǳɹ�������һ��
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
//��ʱ�����벶���жϴ���ص��������ú�����HAL_TIM_IRQHandler�лᱻ����
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) //�����жϷ���ʱִ��
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
        { //���һ����������
            difference = (0xFFFF - IC_Value1) + IC_Value2;
        }
        else
        { //���N����������
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

        // if ((TIM2CH2_CAPTURE_STA & 0X80) == 0) //��δ�ɹ�����
        // {
        //     if (TIM2CH2_CAPTURE_STA & 0X40) //����һ���½���
        //     {
        //         TIM2CH2_CAPTURE_STA |= 0X80;                                                   //��ǳɹ�����һ�θߵ�ƽ����
        //         TIM2CH2_CAPTURE_VAL = HAL_TIM_ReadCapturedValue(&TIM2_Handler, TIM_CHANNEL_2); //��ȡ��ǰ�Ĳ���ֵ.
        //         TIM_RESET_CAPTUREPOLARITY(&TIM2_Handler, TIM_CHANNEL_2);                       //һ��Ҫ�����ԭ�������ã���
        //         TIM_SET_CAPTUREPOLARITY(&TIM2_Handler, TIM_CHANNEL_2, TIM_ICPOLARITY_RISING);  //����TIM2ͨ��1�����ز���
        //     }
        //     else //��δ��ʼ,��һ�β���������
        //     {
        //         TIM2CH2_CAPTURE_STA = 0; //���
        //         TIM2CH2_CAPTURE_VAL = 0;
        //         TIM2CH2_CAPTURE_STA |= 0X40;      //��ǲ�����������
        //         __HAL_TIM_DISABLE(&TIM2_Handler); //�رն�ʱ��5
        //         __HAL_TIM_SET_COUNTER(&TIM2_Handler, 0);
        //         TIM_RESET_CAPTUREPOLARITY(&TIM2_Handler, TIM_CHANNEL_2);                       //һ��Ҫ�����ԭ�������ã���
        //         TIM_SET_CAPTUREPOLARITY(&TIM2_Handler, TIM_CHANNEL_2, TIM_ICPOLARITY_FALLING); //��ʱ��5ͨ��1����Ϊ�½��ز���
        //         __HAL_TIM_ENABLE(&TIM2_Handler);                                               //ʹ�ܶ�ʱ��5
        //     }
        // }
    }
}