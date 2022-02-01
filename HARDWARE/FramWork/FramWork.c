#include "FramWork.h"
#include "math.h"

MotorControlType MotorControl;

void DevelopmentFramwork(void)
{
	MotorControl.User_Kp = RM_Kp;
	MotorControl.User_Ki = RM_Ki;
	MotorControl.User_Kd = RM_Kd;
	MotorControl.Err_Lim = RM_Lim;

	MotorControl.MotorSpeedOne = 500; //写入闭环控制速度值
}
