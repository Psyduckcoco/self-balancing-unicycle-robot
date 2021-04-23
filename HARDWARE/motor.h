#ifndef motor_H
#define motor_H
#include "includes.h"

extern int16_t encoder_fly,encoder_walk;
extern int PWM_out1;
extern int PWM_out2;
extern u8 start_flag;

void Motor_control(void);

void MotorTopForward(u16 x);  
void MotorTopBackward(u16 x); 
void MotorBottomForward(u16 x);
void MotorBottomBackward(u16 x);
void MotorStop( void );

#endif