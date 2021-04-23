#ifndef _OLED_H
#define _OLED_H
#include "stm32f10x.h"
#define LED_SCLK(x)  PBout(5)=x;  //输出  
#define LED_SDA(x)   PBout(4)=x;  //输出 //d1
#define LED_RST(x)   PBout(3)=x;//复位低能电平
#define LED_DC(x)    PGout(15)=x;//偏置常低

void LED_Writedata(unsigned char data);
void LED_WrCmd(unsigned char cmd);
void LED_Set_Pos(u8 x,u8 y);
void LED_Fill(u8 bmp_data);
void LED_CLS(void);
void LED_DLY_ms(u16 ms);
void LED_P6x8Char(unsigned char x,unsigned char y,unsigned char ch);
void LED_P6x8Str(unsigned char x,unsigned char y,unsigned char ch[]);
void LED_Point(unsigned int x,unsigned int y);
void LED_PrintValueI(unsigned char x, unsigned char y, int data);
void LED_PrintValueFP(unsigned char x, unsigned char y, unsigned int data, unsigned char num);
void LED_PrintValueFPP(unsigned char x, unsigned char y, unsigned int data, unsigned char num);
void LED_PrintValueF(unsigned char x, unsigned char y, float data, unsigned char num);


void OLED_Init(void);



extern u8 column_get;
extern u8 time_500ms;
extern u8 data_getting_flag;
extern u8 data_got_flag;




#endif