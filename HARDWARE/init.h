#ifndef _init_H
#define _init_H
#include "includes.h"
void Tim3_init(u16 arr,u16 psc);
void Tim5_init(u16 arr,u16 psc);
void Encoder_Init_TIM2(void);
void Encoder_Init_TIM4(void);
u16 TIM_Get_Counter(u8 TIMX);
void TIM1_Int_Init(u16 arr,u16 psc);
void parameter_Init(void);
void My_NVIC_Init(void);
void  Adc_Init(void);
u16 Get_Adc(u8 ch)  ;
u16 Get_Adc_dis(u8 ch)  ;
void tube_init();
/*
=       =       = |||   =       =       =
l3      l2      l1      r1      r2      r3

*/

#define L1_READ  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_11)//读取按键1
#define L2_READ  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_12)//读取按键1
#define L3_READ  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_13)//读取按键1

#define R1_READ  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_10)//读取按键1
#define R2_READ  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)//读取按键1
#define R3_READ  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4)//读取按键1

#endif