#include "key.h"
#include "delay.h"
u8 key=0;
void KEY_Init(void) //IO初始化 //拨码开关
{ 
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB| RCC_APB2Periph_AFIO,ENABLE);//使能PORTC时钟
  
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
  
//  PWR_BackupAccessCmd(ENABLE);//允许修改RTC 和后备寄存器
//  RCC_LSEConfig(RCC_LSE_OFF);//关闭外部低速外部时钟信号功能 后，PC13 PC14 PC15 才可以当普通IO用。
//  PWR_BackupAccessCmd(DISABLE);//禁止修改后备寄存器
}

u8 KEY_Scan(void)
{
   if(KEY1==0)
   {
     delay_ms(50);//去抖动 
     if(KEY1==0) return 1;
     else return 0;
   }
   
   return 0;
   
}


