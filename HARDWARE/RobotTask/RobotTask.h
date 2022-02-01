#ifndef __ROBOT_H
#define __ROBOT_H

#include "sys.h"

// extern EncoderType GetEncoder;

typedef enum
{
    Speed = 0,
    Position = !Speed
} PidControlMode; //选择速度模式或位置模式

/*绝对式PID算法，接口参数结构类型*/
typedef struct
{
    /*PID算法接口变量，用于给用户获取或修改PID算法的特性*/
    float kp;      //比例系数
    float ki;      //积分系数
    float kd;      //微分系数
    float errILim; //误差积分上限

    float errNow; //当前的误差
    float ctrOut; //控制量输出

    /*PID算法内部变量，其值不能修改*/
    float errOld;
    float errP;
    float errI;
    float errD;

} PID_AbsoluteType;

/*增量式PID算法，接口参数结构类型*/
typedef struct
{
    /*PID算法接口变量，用于给用户获取或修改PID算法的特性*/
    float kp; //比例系数
    float ki; //积分系数
    float kd; //微分系数

    float errNow;  //当前的误差
    float dCtrOut; //控制增量输出
    float ctrOut;  //控制输出

    /*PID算法内部变量，其值不能修改*/
    float errOld1;
    float errOld2;

} PID_IncrementType;

//**************梯形曲线插值算法
typedef struct
{
    float targetPos; //目标位置
    float targetSpd; //目标速度

    float PosNow; //现在的位置
    float SpdNow; //现在的速度

    float SpdLim; //速度上限
    float AccLim; //目标加速度

    float SpdSet; //内部变量，不可修改

} TrapezoidCurveTypedef;

void PID_AbsoluteMode(PID_AbsoluteType *PID);
void PID_IncrementMode(PID_IncrementType *PID);
void PidSpeedControlOne(s32 Speed);
void TrapezoidCurveInterpolation(TrapezoidCurveTypedef *TCI);

#endif
