#ifndef __KEY_H
#define __KEY_H	 
#include "includes.h"
 
#define KEY1  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)//读取按键1

void KEY_Init(void);//IO初始化
u8 KEY_Scan(void);				 

extern u8 key;

#endif
