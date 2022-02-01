#ifndef _KALMAN_H
#define _KALMAN_H
#include "sys.h"

typedef struct
{
    double A, H, p, Q, R, K;
} Kalman;

void KalmanInit(Kalman *k);
double KalmanFilter(Kalman *k,double x,double y);
#endif
