#ifndef __ROBOT_H
#define __ROBOT_H

#include "sys.h"

// extern EncoderType GetEncoder;

typedef enum
{
    Speed = 0,
    Position = !Speed
} PidControlMode; //ѡ���ٶ�ģʽ��λ��ģʽ

/*����ʽPID�㷨���ӿڲ����ṹ����*/
typedef struct
{
    /*PID�㷨�ӿڱ��������ڸ��û���ȡ���޸�PID�㷨������*/
    float kp;      //����ϵ��
    float ki;      //����ϵ��
    float kd;      //΢��ϵ��
    float errILim; //����������

    float errNow; //��ǰ�����
    float ctrOut; //���������

    /*PID�㷨�ڲ���������ֵ�����޸�*/
    float errOld;
    float errP;
    float errI;
    float errD;

} PID_AbsoluteType;

/*����ʽPID�㷨���ӿڲ����ṹ����*/
typedef struct
{
    /*PID�㷨�ӿڱ��������ڸ��û���ȡ���޸�PID�㷨������*/
    float kp; //����ϵ��
    float ki; //����ϵ��
    float kd; //΢��ϵ��

    float errNow;  //��ǰ�����
    float dCtrOut; //�����������
    float ctrOut;  //�������

    /*PID�㷨�ڲ���������ֵ�����޸�*/
    float errOld1;
    float errOld2;

} PID_IncrementType;

//**************�������߲�ֵ�㷨
typedef struct
{
    float targetPos; //Ŀ��λ��
    float targetSpd; //Ŀ���ٶ�

    float PosNow; //���ڵ�λ��
    float SpdNow; //���ڵ��ٶ�

    float SpdLim; //�ٶ�����
    float AccLim; //Ŀ����ٶ�

    float SpdSet; //�ڲ������������޸�

} TrapezoidCurveTypedef;

void PID_AbsoluteMode(PID_AbsoluteType *PID);
void PID_IncrementMode(PID_IncrementType *PID);
void PidSpeedControlOne(s32 Speed);
void TrapezoidCurveInterpolation(TrapezoidCurveTypedef *TCI);

#endif
