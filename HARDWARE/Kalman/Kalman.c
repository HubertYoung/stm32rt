#include "Kalman.h"

void KalmanInit(Kalman *k)
{
    k->A = 1;
    k->H = 1;
    k->K = 0;
    k->p = 0.05;    //p初值可以随便取，但是不能为0（0的话最优滤波器了）
    k->Q = 0.001; //q参数调滤波后的曲线平滑程度，q越小越平滑
    k->R = 0.01;     //r参数调整滤波后的曲线与实测曲线的相近程度，越小越接近
    //k->x=0;
    return;
}

double KalmanFilter(Kalman *k, double x, double y)
{
    k->p = k->A * k->p * k->A + k->Q; //p_pre(k+1)=A*p(k)*A+Q; P预测更新，直接覆盖，此时p为p_pre

    x = k->A * x; //x_pre(k+1)=A*xkf_1(k);x预测更新，直接覆盖，此时x为x_pre

    k->K = k->p * k->H / (k->H * k->p * k->H + k->R); //K更新，使用p_pre

    x = x + k->K * (y - k->H * x); //xkf(k+1)=x_pre(k+1)+Kk_1*(z(k+1)-H1*x_pre(k+1));x量测更新，使用x_pre和y

    k->p = (1 - k->K * k->H) * k->p; //p(k+1)=(I-K*H)*p_pre(k+1);p量测更新，使用p_pre

    return x;
}