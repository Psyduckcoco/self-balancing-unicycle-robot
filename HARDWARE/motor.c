#include "includes.h"
#include "motor.h"

#define MaxOutput 7000          //pwm最大输出 
int16_t encoder_fly,encoder_walk; //1飞轮 2下轮子
int PWM_out1=0;
int PWM_out2=0;

u8 start_flag=0;//1启动 0停止

/*--------------------电机速度控制--------------------*/
void Motor_control(void)
{
  
  PWM_out1 = PWM_out1>MaxOutput?MaxOutput:PWM_out1;
  PWM_out1 = PWM_out1<-MaxOutput?-MaxOutput:PWM_out1;//PWM限幅
  
  PWM_out2 = PWM_out2>MaxOutput?MaxOutput:PWM_out2;
  PWM_out2 = PWM_out2<-MaxOutput?-MaxOutput:PWM_out2;//PWM限幅
  
  
  if(PWM_out1 >= 0)
    MotorTopForward(PWM_out1);
  if(PWM_out1<0)
    MotorTopBackward(-PWM_out1);
  
  if(PWM_out2 < 0)
    MotorBottomForward(-PWM_out2);
  if(PWM_out2>=0)
    MotorBottomBackward(PWM_out2);
  
  if(start_flag==0)
  {
    MotorStop();
  }
  
}
void MotorTopForward( u16 x )
{
  TIM3->CCR1 = 0;
  TIM3->CCR2 = x;
}
void MotorTopBackward( u16 x )
{  
  TIM3->CCR1 = x;
  TIM3->CCR2 = 0;
}
void MotorBottomForward( u16 x )
{
  TIM3->CCR3 = 0;
  TIM3->CCR4 = x;
  
}
void MotorBottomBackward( u16 x )
{ 
  TIM3->CCR3 = x;
  TIM3->CCR4 = 0;
}
void MotorStop( void )
{  
  TIM3->CCR1 = 0;
  TIM3->CCR2 = 0;
  TIM3->CCR3 = 0;
  TIM3->CCR4 = 0;
}

