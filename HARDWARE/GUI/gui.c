#include "gui.h"
#include "key.h"
#include "led.h"
#include <stdio.h>
#include <string.h>

// #include "driver_ssd1306_basic.h"

static u8 func_index = _Main_UI;			   //当前页面索引值
static u8 last_index = _Main_UI;			   //上一个界面索引值
static void (*current_operation_func)(u8, u8); //定义一个函数指针
// static u8 BEEP_swi = ON;

//索引表
Main_Menu table[20] =
	{
		// Cur_Index,previous,next,enter,back,(*current_operation)(u8,u8)
		//主界面
		{_Main_UI, _Main_UI, _Main_UI, _Wifi_Option, _OLED_Lock, Main_UI},
		//主菜单
		{_Wifi_Option, _Info_Option, _Bluetooth_Option, _Wifi_Child, _Main_UI, Main_Menu_Func},			// Wifi
		{_Bluetooth_Option, _Wifi_Option, _Setting_Option, _Bluetooth_Child, _Main_UI, Main_Menu_Func}, //蓝牙
		{_Setting_Option, _Bluetooth_Option, _Info_Option, _Setting_Child, _Main_UI, Main_Menu_Func},	//设置
		{_Info_Option, _Setting_Option, _Wifi_Option, _Info_Child, _Main_UI, Main_Menu_Func},			//关于信息

		//子菜单
		{_Wifi_Child, _Wifi_Child, _Wifi_Child, _Wifi_Child, _Wifi_Option, Wifi_Child},								  // Wifi子菜单
		{_Bluetooth_Child, _Bluetooth_Child, _Bluetooth_Child, _Bluetooth_Child, _Bluetooth_Option, Bluetooth_Child}, //蓝牙子菜单
		{_Setting_Child, _Setting_Child, _Setting_Child, _Setting_Child, _Setting_Option, Setting_Child},			  //设置子菜单
		{_Info_Child, _Info_Child, _Info_Child, _Info_Child, _Info_Option, Info_Child},								  //关于信息子菜单
		{_OLED_Lock, _Main_UI, _Main_UI, _Main_UI, _Main_UI, OLED_Lock},											  // OLED熄屏
};

/*
函数功能：刷新界面
参数：无
返回值：无
*/
void GUI_Refresh(void)
{
	u8 key_val = KEY_Scan(0);
	if (key_val != 0) //只有按键按下才刷屏
	{
		last_index = func_index; //更新上一界面索引值
		switch (key_val)
		{
		case KEY_UP_PRES:
			func_index = table[func_index].previous; //更新索引值
			break;
		case KEY_DOWN_PRES:
			func_index = table[func_index].enter; //更新索引值
			break;
		case KEY_RIGHT_PRES:
			func_index = table[func_index].next; //更新索引值
			break;
		case KEY_LEFT_PRES:
			func_index = table[func_index].back; //更新索引值
			break;
		default:
			break;
		}
		// ssd1306_Fill(Black); //清屏
	}
	current_operation_func = table[func_index].current_operation;
	(*current_operation_func)(func_index, key_val); //执行当前索引对应的函数
}

/*
函数功能：显示主界面
参数：u8 page_index,u8 key_val
返回值：无
*/
void Main_UI(u8 page_index, u8 key_val)
{
	printf("Main_UI\r\n");
	char buff[20];
	// snprintf(buff, sizeof(buff), "当前转速%02d", 100);
	// ssd1306_basic_string(0, 0, buff, sizeof(buff), 1, SSD1306_FONT_16);
	// ssd1306_basic_string(0, 0, buff, sizeof(buff), 1, SSD1306_FONT_16);
    // ssd1306_SetCursor(0, 0); //起始点
	// char buff[20]; //创建文字缓冲区
	// snprintf(buff, sizeof(buff), "cur_s=%02d", 100);
	// ssd1306_WriteString(buff, Font_7x10, White); //压入显示缓冲区
	// ssd1306_UpdateScreen(); //刷新
	// ssd1306_SetCursor(0, 10); //起始点
	// snprintf(buff, sizeof(buff), "set_s=%02d", 150);
	// ssd1306_WriteString(buff, Font_7x10, White); //压入显示缓冲区
	// ssd1306_UpdateScreen(); //刷新
}
/*
函数功能：主菜单显示函数
参数：u8 page_index,u8 key_val
返回值：无
*/
void Main_Menu_Func(u8 page_index, u8 key_val)
{
	// char buff[20];
	// OLED_Display_Image(0, 0, 11, 7, (char *)Signal_11x7, NO_ALGIN);	  //显示信号塔
	// OLED_Display_Image(14, 0, 9, 9, (char *)Bluetooth_9x9, NO_ALGIN); //显示蓝牙
	// snprintf(buff, sizeof(buff), "%02d:%02d:%02d", Current_Time.hour, Current_Time.min, Current_Time.sec);
	// OLED_Display_String(0, 0, 8, 8, buff, NORMAL, CEN_ALIGN);		  //显示时间
	// OLED_Display_Image(112, 0, 16, 8, (char *)Bat_16x8, NO_ALGIN);	  //显示电量
	// OLED_Display_Image(15, 4, 16, 16, (char *)Left_16x16, NO_ALGIN);  //显示左箭头
	// OLED_Display_Image(97, 4, 16, 16, (char *)Right_16x16, NO_ALGIN); //显示右箭头
	// OLED_Display_Image(0, 6, 16, 16, (char *)Enter_16x16, NO_ALGIN);  //显示确定
	// OLED_Display_Image(112, 6, 16, 16, (char *)Back_16x16, NO_ALGIN); //显示返回箭头
	// switch (page_index)
	// {
	// case _Wifi_Option:
	// 	OLED_Display_Image(0, 2, 48, 48, (char *)Wifi_48x48, CEN_ALIGN); //显示Wifi图标
	// 	break;
	// case _Bluetooth_Option:
	// 	OLED_Display_Image(0, 2, 48, 48, (char *)Bluetooth_48x48, CEN_ALIGN); //显示蓝牙图标
	// 	break;
	// case _Setting_Option:
	// 	OLED_Display_Image(0, 2, 48, 48, (char *)Setting_48x48, CEN_ALIGN); //显示设置图标
	// 	break;
	// case _Info_Option:
	// 	OLED_Display_Image(0, 2, 48, 48, (char *)Info_48x48, CEN_ALIGN); //显示关于信息图标
	// 	break;
	// default:
	// 	break;
	// }
}

/*
函数功能：Wifi选项子菜单
参数：u8 page_index,u8 key_val
返回值：无
*/
void Wifi_Child(u8 page_index, u8 key_val)
{
	// static u8 cur_pos = 1;
	// static u8 wifi_status = ON;
	// static u8 wifi_mode = SoftAP_Station;
	// static u8 esp_tcpserver = OFF;
	// static u8 esp_unvarnishedmode = OFF;
	// if (last_index != _Wifi_Option) //判断是否是第一次进入此界面
	// {
	// 	switch (key_val)
	// 	{
	// 	case KEY_PREVIOUS:
	// 		cur_pos == 1 ? cur_pos = 6 : cur_pos--;
	// 		break;
	// 	case KEY_ENTER: //确定(设置)按键
	// 	{
	// 		switch (cur_pos)
	// 		{
	// 		case 1:
	// 			wifi_status = !wifi_status;
	// 			if (wifi_status == OFF)
	// 			{
	// 				esp_tcpserver = OFF;
	// 				esp_unvarnishedmode = OFF;
	// 			}
	// 			break;
	// 		case 2:
	// 			if (wifi_status == ON)
	// 			{
	// 				wifi_mode == SoftAP_Station ? wifi_mode = Station : wifi_mode++;
	// 				esp_tcpserver = OFF;
	// 				esp_unvarnishedmode = OFF;
	// 			}
	// 			break;
	// 		case 3:
	// 			if (wifi_status == ON && esp_unvarnishedmode == OFF &&
	// 				(wifi_mode == SoftAP_Station || wifi_mode == SoftAP))
	// 				esp_tcpserver = !esp_tcpserver;
	// 			break;
	// 		case 4:
	// 			if (wifi_status == ON && esp_tcpserver == OFF &&
	// 				(wifi_mode == SoftAP_Station || wifi_mode == Station))
	// 				esp_unvarnishedmode = !esp_unvarnishedmode;
	// 			break;
	// 		case 5:
	// 			break;
	// 		case 6:
	// 			break;
	// 		default:
	// 			break;
	// 		}
	// 	}
	// 	break;
	// 	case KEY_NEXT:
	// 		cur_pos == 6 ? cur_pos = 1 : cur_pos++;
	// 		break;
	// 	default:
	// 		break;
	// 	}
	// }
	// else
	// 	cur_pos = 1; //第一次进入此界面,界面指针清零
	// if (cur_pos <= 4)
	// {
	// 	OLED_Display_String(0, 0, 8, 16, wifi_status ? "1.Switch:ON" : "1.Switch:OFF", cur_pos == 1 ? REVERSE : NORMAL, NO_ALGIN);
	// 	OLED_Display_String(0, 2, 8, 16, wifi_mode == SoftAP_Station ? "2.Mode:AP+STA" : wifi_mode == SoftAP ? "2.Mode:AP"
	// 																										 : "2.Mode:STA",
	// 						cur_pos == 2 ? REVERSE : NORMAL, NO_ALGIN);
	// 	OLED_Display_String(0, 4, 8, 16, esp_tcpserver ? "3.TCP server:ON" : "3.TCP server:OFF", cur_pos == 3 ? REVERSE : NORMAL, NO_ALGIN);
	// 	OLED_Display_String(0, 6, 8, 16, esp_unvarnishedmode ? "4.Mqtt mode:ON" : "4.Mqtt mode:OFF", cur_pos == 4 ? REVERSE : NORMAL, NO_ALGIN);
	// }
	// else if (cur_pos <= 8)
	// {
	// 	OLED_Display_String(0, 0, 8, 16, "5.RSSI:", cur_pos == 5 ? REVERSE : NORMAL, NO_ALGIN);
	// 	OLED_Display_String(0, 2, 8, 16, "6.Esp touch", cur_pos == 6 ? REVERSE : NORMAL, NO_ALGIN);
	// }
}

/*
函数功能：蓝牙选项子菜单
参数：u8 page_index,u8 key_val
返回值：无
*/
void Bluetooth_Child(u8 page_index, u8 key_val)
{
	// static u8 cur_pos = 1;
	// static u8 BL_status = ON;
	// if (last_index != _Bluetooth_Option) //判断是否是第一次进入此界面
	// {
	// 	switch (key_val)
	// 	{
	// 	case KEY_PREVIOUS:
	// 		cur_pos == 1 ? cur_pos = 4 : cur_pos--;
	// 		break;
	// 	case KEY_ENTER: //确定(设置)按键
	// 	{
	// 		switch (cur_pos)
	// 		{
	// 		case 1:
	// 			BL_status = !BL_status;
	// 			break;
	// 		case 2:
	// 			break;
	// 		case 3:
	// 			break;
	// 		case 4:
	// 			break;
	// 		default:
	// 			break;
	// 		}
	// 	}
	// 	break;
	// 	case KEY_NEXT:
	// 		cur_pos == 4 ? cur_pos = 1 : cur_pos++;
	// 		break;
	// 	default:
	// 		break;
	// 	}
	// }
	// else
	// 	cur_pos = 1; //第一次进入此界面,界面指针清零
	// OLED_Display_String(0, 0, 8, 16, BL_status ? "1.Switch:ON" : "1.Switch:OFF", cur_pos == 1 ? REVERSE : NORMAL, NO_ALGIN);
	// OLED_Display_String(0, 2, 8, 16, "2.Addr match", cur_pos == 2 ? REVERSE : NORMAL, NO_ALGIN);
	// OLED_Display_String(0, 4, 8, 16, "3.RSSI:", cur_pos == 3 ? REVERSE : NORMAL, NO_ALGIN);
	// OLED_Display_String(0, 6, 8, 16, "4.Mode set", cur_pos == 4 ? REVERSE : NORMAL, NO_ALGIN);
}

/*
函数功能：设置选项子菜单
参数：u8 page_index,u8 key_val
返回值：无
*/
void Setting_Child(u8 page_index, u8 key_val)
{
	// char buff[20];
	// static u8 cur_pos = 1;
	// static u8 Remote_form = 0;
	// static u8 EEPROM_swi = ON;
	// static u8 Bri_level = 8;
	// if (last_index != _Setting_Option) //判断是否是第一次进入此界面
	// {
	// 	switch (key_val)
	// 	{
	// 	case KEY_PREVIOUS:
	// 		cur_pos == 1 ? cur_pos = 6 : cur_pos--;
	// 		break;
	// 	case KEY_ENTER: //确定(设置)按键
	// 	{
	// 		switch (cur_pos)
	// 		{
	// 		case 1:
	// 			break;
	// 		case 2:
	// 			Remote_form == 2 ? Remote_form = 0 : Remote_form++;
	// 			break;
	// 		case 3:
	// 			Bri_level == 16 ? Bri_level = 1 : Bri_level++;
	// 			OLED_SPI_WriteByte(0x81, OLED_CMD); //设置对比度
	// 			OLED_SPI_WriteByte(Bri_level * 16 - 1, OLED_CMD);
	// 			break;
	// 		case 4:
	// 			BEEP_swi = !BEEP_swi;
	// 			break;
	// 		case 5:
	// 			EEPROM_swi = !EEPROM_swi;
	// 			break;
	// 		case 6:
	// 			break;
	// 		default:
	// 			break;
	// 		}
	// 	}
	// 	break;
	// 	case KEY_NEXT:
	// 		cur_pos == 6 ? cur_pos = 1 : cur_pos++;
	// 		break;
	// 	default:
	// 		break;
	// 	}
	// }
	// else
	// 	cur_pos = 1; //第一次进入此界面,界面指针清零

	// if (cur_pos <= 4)
	// {
	// 	OLED_Display_String(0, 0, 8, 16, "1.Calib time", cur_pos == 1 ? REVERSE : NORMAL, NO_ALGIN);
	// 	OLED_Display_String(0, 2, 8, 16, Remote_form == 0 ? "2.Remote:NRF2.4G" : Remote_form == 1 ? "2.Remote:Wi-Fi"
	// 																							  : "2.Remote:BL",
	// 						cur_pos == 2 ? REVERSE : NORMAL, NO_ALGIN);
	// 	snprintf(buff, sizeof(buff), "3.Bri set:%d", Bri_level); //显示亮度
	// 	OLED_Display_String(0, 4, 8, 16, buff, cur_pos == 3 ? REVERSE : NORMAL, NO_ALGIN);
	// 	OLED_Display_String(0, 6, 8, 16, BEEP_swi ? "4.BEEP:ON" : "4.BEEP:OFF", cur_pos == 4 ? REVERSE : NORMAL, NO_ALGIN);
	// }
	// else if (cur_pos <= 8)
	// {
	// 	OLED_Display_String(0, 0, 8, 16, EEPROM_swi ? "5.EEPROM:ON" : "5.EEPROM:OFF", cur_pos == 5 ? REVERSE : NORMAL, NO_ALGIN);
	// 	OLED_Display_String(0, 2, 8, 16, "6.Low Power", cur_pos == 6 ? REVERSE : NORMAL, NO_ALGIN);
	// }
}
/*
函数功能：关于信息页
参数：u8 page_index,u8 key_val
返回值;无
*/
void Info_Child(u8 page_index, u8 key_val)
{
	// char buff[20];
	// snprintf(buff, sizeof(buff), "1.BAT vol:%.2f V", BAT_Voltage * 2); //分压比为2
	// OLED_Display_String(0, 0, 8, 16, buff, NORMAL, NO_ALGIN);
	// OLED_Display_String(0, 3, 8, 16, "2.Version:v1.0", NORMAL, NO_ALGIN);
}
/*
函数功能：OLED熄屏
参数：u8 page_index,u8 key_val
返回值;无
*/
void OLED_Lock(u8 page_index, u8 key_val)
{
	// OLED_Clear(0);
}
