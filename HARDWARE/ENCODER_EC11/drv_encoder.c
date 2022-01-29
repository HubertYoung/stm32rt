
#include "drv_encoder.h"

#define NOREADY 0
#define READY 1
#define INIT 3

volatile uint8_t encoder_status = INIT;
volatile int16_t encoder_steps = 0;
uint16_t PrescalerValue = 0;

extern osEventFlagsId_t LVGL_rfr_evt_id;

void TIM5_init(void)
{
    GPIO_InitTypeDef gpio_cfg;
    TIM_TimeBaseInitTypeDef TIMER_InitStructure;
    TIM_ICInitTypeDef TIM_ICInitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    // PB7 (TIM5_CH2) (encoder pin A), PB6 (TIM5_CH1) (encoder pin B)
    gpio_cfg.GPIO_Mode = GPIO_Mode_IPU;
    gpio_cfg.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_5;
    gpio_cfg.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOB, &gpio_cfg);

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
    TIM_TimeBaseStructInit(&TIMER_InitStructure);
    // Impostiamo TIM_Period = 1. Il timer conta fino a 1. L'interrupt verrà richiamato ad ogni modifica della posizione dell'encoder
    TIMER_InitStructure.TIM_Period = 1;
    TIMER_InitStructure.TIM_CounterMode = TIM_CounterMode_Up | TIM_CounterMode_Down;
    TIM_TimeBaseInit(TIM5, &TIMER_InitStructure);
    /* -----------------------------------------------------------------------
    TIM3 Configuration: Encoder mode1:
    
    In this example TIM3 input clock (TIM3CLK) is set to APB1 clock (PCLK1).
      TIM3CLK = PCLK1  
      PCLK1 = HCLK
      => TIM3CLK = HCLK = SystemCoreClock
          
    To get TIM3 counter clock at 6 MHz, the prescaler is computed as follows:
       Prescaler = (TIM3CLK / TIM3 counter clock) - 1
       Prescaler = ((SystemCoreClock) /6 MHz) - 1
   TIM3 is configured to interface with an encoder:
   - The encoder mode is encoder mode1: Counter counts up/down on TI2 rising edge 
   depending on TI1 level 
   - The Autoreload value is set to 399, so the encoder round is 400 TIM counter clock.  
                                              
    Note: 
     SystemCoreClock variable holds HCLK frequency and is defined in system_stm32f0xx.c file.
     Each time the core clock (HCLK) changes, user had to call SystemCoreClockUpdate()
     function to update SystemCoreClock variable value. Otherwise, any configuration
     based on this variable will be incorrect.    
  ----------------------------------------------------------------------- */

    // PrescalerValue = (uint16_t) ((SystemCoreClock ) / 6000000) - 1;
    // TIM_PrescalerConfig(TIM5, PrescalerValue, TIM_PSCReloadMode_Immediate);

    //debounce filter
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInitStructure.TIM_ICFilter = 0x0F;
    TIM_ICInit(TIM5, &TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInitStructure.TIM_ICFilter = 0x0F;
    TIM_ICInit(TIM5, &TIM_ICInitStructure);

    TIM_EncoderInterfaceConfig(TIM5, TIM_EncoderMode_TI1, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
    TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM5, ENABLE);

    NVIC_EnableIRQ(TIM5_IRQn);
}

void TIM5_IRQHandler(void)
{
    static uint32_t delay;

    if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
    {
        // Il primo trigger viene scartato. encoder_status == INIT può essere una sola volta
        if (encoder_status == INIT)
            encoder_status = NOREADY;
        else
            encoder_status = READY;
        //Il registro TIM3_CR1 bit TIM_CR1_DIR sarà la direzione di rotazione dell'encoder
        encoder_steps += (TIM5->CR1 & TIM_CR1_DIR ? -1 : 1);
        // debounce delay
        for (delay = 0; delay <= 500; delay++)
            __asm("nop");
        osEventFlagsSet(LVGL_rfr_evt_id, 0x0001); // LVGL Refresh
        TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
    }
}

uint16_t TIM5_read(void)
{
    int16_t count;
    if (encoder_status)
    {
        encoder_status = NOREADY;
        count = encoder_steps;
        encoder_steps = 0;
        return count;
    }
    else
        return 0;
}

uint8_t enc_pressed(void)
{
    return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5);
}
