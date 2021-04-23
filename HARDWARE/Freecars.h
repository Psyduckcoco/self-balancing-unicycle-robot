#ifndef  _Freecars_H_
#define  _Freecars_H_  
#include "includes.h"
//FreeCars上位机 串口数据显示框 接收通道数，按照上位机设置改变
#define UartDataNum 17//上位机数据通道数量，必须与上位机设置一样
#define UartRxBufferLen  100
#define UartRxDataLen 41//FreeCars上位机发送浮点数据MCU接收，不要改
#define UartRxCmdLen 7//FreeCars上位机接收命令数据长度，不要改
#define UartCmdNum  SerialPortRx.Buffer[SerialPortRx.Stack-3]//命令号
#define UartCmdData SerialPortRx.Buffer[SerialPortRx.Stack-2]//命令数据

typedef struct 
{
  int Stack;
  u8 Data;
  u8 PreData;
  u8 Buffer[UartRxBufferLen];
  u8 Enable;
  u8 Check;
}SerialPortType;
void push(u8 chanel,u16 data);
void sendDataToScope(void);//Freecars示波器轮询法发送一帧数据


#endif



