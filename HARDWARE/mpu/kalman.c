#include "includes.h"
#include "kalman.h"

float gryo_y_b;//最优绕y轴角速度
void kalman_filter_pitch(float angle_m,float gyro_m)//输入参数 测量的角度 和 测量的角速度  例：kalman_filter_pitch(atan2(accx , accz) * 180 / PI,-gyroy/16.384);
{
  float Q_angle = 0.001;
  float Q_gyroBias = 0.003;
  float R_measure = 0.03;
  static float P[2][2];
  float K[2];//卡尔曼增益
  float y,s;//残差  和 残差协方差
  static float bias;//角速度偏差 漂移造成
  float P00_temp,P01_temp;
  float dt = 0.005;//滤波器采样时间 可认为是定时器时间
  pitch+=dt*(float)(gyro_m - bias);//此时刻预测值
  
  P[0][0] += dt*(dt*P[1][1]-P[1][0]-P[0][1]+Q_angle);//先验误差协方差矩阵 表对当前预测状态的信任度
  P[0][1] -= dt*P[1][1]; 
  P[1][0] -= dt*P[1][1];
  P[1][1] += dt*Q_gyroBias;
  
  y = angle_m - pitch;//计算残差 表测量值和预测值的偏离程度
  
  s = P[0][0]+R_measure;//计算残差协方差 越大表示噪声越大 不能过于信任测量值
  
  K[0] = P[0][0]/s;//计算卡尔曼增益 表示对残差的信任程度 信任程度越大 对当前状态（测量值）信任度越小
  K[1] = P[1][0]/s;
  
  pitch+=K[0]*y;//更新当前状态后验估计
  bias+=K[1]*y;
  gryo_y_b=gyro_m-bias;//最优角速度
  
  P00_temp=P[0][0];//更新协方差矩阵
  P01_temp=P[0][1];
  P[0][0]-=K[0]*P00_temp;
  P[0][1]-=K[0]*P01_temp;
  P[1][0]-=K[1]*P00_temp;
  P[1][1]-=K[1]*P01_temp;
  
}
//roll脚滤波 同上
float gryo_x_b;//最优绕x轴角速度
void kalman_filter_roll(float angle_m,float gyro_m)
{
  float Q_angle = 0.001;
  float Q_gyroBias = 0.003;
  float R_measure = 0.03;
  static float P[2][2];
  float K[2];//卡尔曼增益
  float y,s;//残差  和 残差协方差
  static float bias;//角速度偏差 漂移造成
  float P00_temp,P01_temp;
  float dt = 0.005;//滤波器采样时间 可认为是定时器时间
  roll+=dt*(float)(gyro_m - bias);//此时刻预测值
  
  P[0][0] += dt*(dt*P[1][1]-P[1][0]-P[0][1]+Q_angle);//先验误差协方差矩阵 表对当前预测状态的信任度
  P[0][1] -= dt*P[1][1]; 
  P[1][0] -= dt*P[1][1];
  P[1][1] += dt*Q_gyroBias;
  
  y = angle_m - roll;//计算残差 表测量值和预测值的偏离程度
  
  s = P[0][0]+R_measure;//计算残差协方差 越大表示噪声越大 不能过于信任测量值
  
  K[0] = P[0][0]/s;//计算卡尔曼增益 表示对残差的信任程度 信任程度越大 对当前状态（测量值）信任度越小
  K[1] = P[1][0]/s;
  
  roll+=K[0]*y;//更新当前状态后验估计
  bias+=K[1]*y;
  gryo_x_b=gyro_m-bias;//最优角速度
  
  P00_temp=P[0][0];//更新协方差矩阵
  P01_temp=P[0][1];
  P[0][0]-=K[0]*P00_temp;
  P[0][1]-=K[0]*P01_temp;
  P[1][0]-=K[1]*P00_temp;
  P[1][1]-=K[1]*P01_temp;
  
}



//一阶互补滤波
float K1 =0.05; // 对加速度计取值的权重
float dt=0.005;//注意：dt的取值为滤波器采样时间
float angle1;
void Yijielvbo(float angle_m, float gyro_m)//采集后计算的角度和角加速度
{
     angle1 = K1 * angle_m+ (1-K1) * (angle1 + gyro_m * dt);
}
float K2 =0.2; // 对加速度计取值的权重
float x1,x2,y1;
float angle2;

void Erjielvbo(float angle_m,float gyro_m)//采集后计算的角度和角加速度
{
    x1=(angle_m-angle2)*(1-K2)*(1-K2);
    y1=y1+x1*dt;
    x2=y1+2*(1-K2)*(angle_m-angle2)+gyro_m;
    angle2=angle2+ x2*dt;
}


