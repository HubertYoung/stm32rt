#include "RobotTask.h"
#include "FramWork.h"

extern MotorControlType MotorControl;

//绝对式PID算法
void PID_AbsoluteMode(PID_AbsoluteType *PID)
{
   if (PID->kp < 0)
      PID->kp = -PID->kp;
   if (PID->ki < 0)
      PID->ki = -PID->ki;
   if (PID->kd < 0)
      PID->kd = -PID->kd;
   if (PID->errILim < 0)
      PID->errILim = -PID->errILim;

   PID->errP = PID->errNow;

   PID->errI += PID->errNow;

   if (PID->errILim != 0)
   {
      if (PID->errI > PID->errILim)
         PID->errI = PID->errILim;
      else if (PID->errI < -PID->errILim)
         PID->errI = -PID->errILim;
   }

   PID->errD = PID->errNow - PID->errOld;

   PID->errOld = PID->errNow;

   PID->ctrOut = PID->kp * PID->errP + PID->ki * PID->errI + PID->kd * PID->errD;
}

//电机速度环伺服
s32 SpeedTagOne, SpeedNowOne, SpeedControlOne;

PID_AbsoluteType PidSpeedTypeOne;

void PidSpeedControlOne(s32 Speed)
{
   // SpeedNowOne = GetEncoder.V5;
   SpeedTagOne = Speed; //无量纲
   PidSpeedTypeOne.errNow = SpeedTagOne - SpeedNowOne;
   PidSpeedTypeOne.kp = MotorControl.User_Kp;
   PidSpeedTypeOne.ki = MotorControl.User_Ki;
   PidSpeedTypeOne.kd = MotorControl.User_Kd;
   PidSpeedTypeOne.errILim = MotorControl.Err_Lim;
   PID_AbsoluteMode(&PidSpeedTypeOne);
   SpeedControlOne = PidSpeedTypeOne.ctrOut;
   // MotorSpeedSetThr(SpeedControlOne);
}