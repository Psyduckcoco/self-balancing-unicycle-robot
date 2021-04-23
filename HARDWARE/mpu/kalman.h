#ifndef _kalman_H
#define _kalman_H
#include "includes.h"

void kalman_filter_pitch(float angle_m,float gryo_m);
void kalman_filter_roll(float angle_m,float gyro_m);

extern float gryo_y_b;//最优角速度
extern float gryo_x_b;//最优角速度
void Yijielvbo(float angle_m, float gyro_m);//采集后计算的角度和角加速度
void Erjielvbo(float angle_m,float gyro_m);//采集后计算的角度和角加速度
extern float angle1;extern float angle2;

#endif