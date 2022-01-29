
#ifndef _GUI_H
#define _GUI_H
#include "sys.h"

#include "SOLGUI_Include.h"
#include "SOLGUI_Hardware.h"

void GUI_Init_First(void);
void GUI_Init(void);
void GUI_InputKey(u8 key);

void GUI_Refresh(void);
#endif