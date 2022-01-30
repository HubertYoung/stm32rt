#include "gui.h"
#include "pwm.h"
#include "w25qxx.h"

u32 busFre = 0;
u32 arr = 0;
u32 psc = 0;
u32 ccr = 0;
u32 pwm_fre = 0;
float pwm_dc = 0;
float pwm_dc_temp = 0;

u32 pwm_fre_temp = 0;

u16 id = 0;

u32 FG = 0;

void PWM_Status(void)
{
    busFre = HAL_RCC_GetHCLKFreq();
    arr = TIM1->ARR + 1; //自动重装载值
    psc = TIM1->PSC + 1; //定时器分频，确定时钟频率
    ccr = TIM1->CCR1;    //装载值
    pwm_fre = (busFre / arr) / psc / 1000;
    pwm_dc = 100 - ((float)ccr * 100 / arr);

    id = W25QXX_ReadID();
}

u32 switch_reg = 0;

char pic_choose = 1;
static volatile float setDutyCycle; //占空比 取值 0 - 100,
float CarSpeed;                     //加速度计角度
char *test_str = "123123";          //加速度计角度
MENU_PAGE main_page, pwm_init, other, tcp_conn, senddata;

__M_PAGE(main_page, "MainPage", PAGE_NULL,
         {
             //   84M/(pcs * aar) = 24kHz
             //  u32 busFre = HAL_RCC_GetHCLKFreq();
             //  u32 arr = TIM1->ARR + 1; //自动重装载值
             //  u32 psc = TIM1->PSC + 1; //定时器分频，确定时钟频率
             //  u32 ccr = TIM1->CCR1;    //装载值
             //  u32 pwm_fre = (busFre / arr) / psc / 1000;
             //  float pwm_dc = 1000 - (ccr * 1000 / arr);
             PWM_Status();
             pwm_fre_temp = pwm_fre;
             pwm_dc_temp = pwm_dc;
             SOLGUI_Widget_Text(0, 48, F6X8, "S=%d,r=%d,C=%d", arr, psc, busFre);
             SOLGUI_Widget_Text(0, 40, F6X8, "FG=%d", FG);
             SOLGUI_Widget_Text(0, 32, F6X8, "%d", TIM1->ARR);          //自动重装载值
             SOLGUI_Widget_Text(0, 24, F6X8, "PWM_DC  = %f%%", pwm_dc); //装载值
             SOLGUI_Widget_Text(0, 16, F6X8, "PWM_Fre = %dkHz", pwm_fre);
             SOLGUI_Widget_Text(0, 8, F6X8, "HCKL    = %dMHz", busFre / 1000000);

             SOLGUI_Cursor(0, 0, 2);
             SOLGUI_Widget_GotoPage(0, &pwm_init);
             SOLGUI_Widget_GotoPage(1, &other);
         });
__M_PAGE(pwm_init, "PWM_SET", &main_page,
         {
             //  u32 busFre = HAL_RCC_GetHCLKFreq();
             //  u32 arr = TIM1->ARR + 1; //自动重装载值
             //  u32 psc = TIM1->PSC + 1; //定时器分频，确定时钟频率
             //  u32 ccr = TIM1->CCR1;    //装载值
             //  u32 pwm_fre = (busFre / arr) / psc / 1000;
             //  float pwm_dc = 1000 - (ccr * 1000 / arr);
             SOLGUI_Cursor(6, 0, 2);
             SOLGUI_Widget_Spin(0, "fre(kHz)", INT16, 100, 1, &pwm_fre_temp);
             SOLGUI_Widget_Spin(1, "duty(%)", FLT16, 100, 0, &pwm_dc_temp);
             SOLGUI_Widget_Text(0, 8, F6X8, "arr=%d", pwm_fre);
             if (pwm_fre_temp != pwm_fre)
             {
                 pwm_fre = pwm_fre_temp;
                 arr = busFre / pwm_fre / psc / 1000;
                 //  pwm_dc = 1000 - (ccr * 1000 / arr)
                 ccr = (100 - pwm_dc) * arr / 100;
                 TIM_SetTIM1AutoReload(arr - 1, ccr + 1);
             }
             if (pwm_dc_temp != pwm_dc)
             {
                 pwm_dc = pwm_dc_temp;
                 ccr = (100 - pwm_dc) * arr / 100;
                 TIM_SetTIM1Compare2(ccr + 1);
             }
             SOLGUI_Widget_Text(0, 16, F6X8, "ccr=%d", ccr);

             //  SOLGUI_Widget_Text(0, 16, F6X8, "ccr=%d", TIM1->CCR1);
             SOLGUI_Widget_Text(0, 8, F6X8, "arr=%d", TIM1->ARR + 1);
         });
__M_PAGE(other, "other", &main_page,
         {
             u8 buf[4];
             W25QXX_Read(buf, PWM_ARR, 4);
             u32 aar = U8ArrayToU32(buf);
             W25QXX_Read(buf, PWM_CCR, 4);
             u32 crr = U8ArrayToU32(buf);
             SOLGUI_Widget_Text(0, 48, F6X8, "W25QXX_ID=%04x", id);
             printf("aar=%d", aar);
             printf("crr=%d", crr);
             //  SOLGUI_Widget_Text(0, 40, F6X8, "read=%d", aar);
             //  SOLGUI_Widget_Text(0, 40, F6X8, "read=%d", datatemp);
             SOLGUI_Cursor(0, 0, 1);

             //  SOLGUI_Widget_Button(0, "Erase_Chip", &W25QXX_Erase_Chip); argument of type "u8 **" is incompatible with parameter of type "u8 *"
             //  SOLGUI_Widget_OptionText(4, "angle:  %f", CarAngle);
         });
__M_PAGE(tcp_conn, "tcp_conn", &main_page,
         {
             SOLGUI_Cursor(0, 0, 1);

             //  SOLGUI_Widget_OptionText(5, "speed:  %f", CarSpeed);
         });
void GUI_Init_First(void)
{
    PWM_Status();
    SOLGUI_Hardware_Init();

    SOLGUI_printf(0, 24, F8X10, "FOSTEX");
    SOLGUI_printf(0, 48, F8X10, "MODLE 20");
    SOLGUI_Refresh();

    delay_ms(1000);
}
void GUI_Init(void)
{
    SOLGUI_Menu_SetHomePage(&main_page);
    SOLGUI_Menu_PageStage();
    SOLGUI_Refresh();
}

void GUI_InputKey(u8 key)
{
    SOLGUI_InputKey(key);
}

void GUI_Refresh(void)
{
    SOLGUI_Menu_PageStage();
    SOLGUI_Refresh();
}
void GUI_RefreshFreq(u32 FbFreq)
{
    FG = FbFreq;
}