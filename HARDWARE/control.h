#ifndef _control_H
#define _control_H
#include "includes.h"

extern float K[3];//反馈矩阵 由matlab获得 
extern float torque;//电机扭矩
extern float X[3];//状态变量 列矩阵

extern float pitch_setoff;
extern float roll_setoff;
extern float voltage;

extern  float pit,rol;
 
extern float speed_set,speed_p,speed_i,speed_out;
void speed_loop();

extern float pitch_setoff,pitch_p,pitch_d,last_pitch,pitch_out;
void angle_loop();

extern float inner_p,inner_d,last_gyro,inner_out;
void inner_loop();
extern float speed_inter,speed_limit;
extern int follow_flag;
void adc_pid();
extern int go_line_flag;
extern int left_out,right_out,left_in,right_in;;
void go_line();

extern int z_tar;
extern int fankui;

#endif