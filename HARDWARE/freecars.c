#include "Freecars.h"
#include "includes.h"
u8 uSendBuf[UartDataNum*2]={0};
u8 FreeCarsDataNum=UartDataNum*2;//它是通道数 UartDataNum*2(因为数据是Int16型的)
double UartData[9] = {0};

SerialPortType SerialPortRx;
//显示Freecars上位机修改数据



void UartDebug(void)
{
  if(UartData[0]!=0)
  {
     K[0] = (float)UartData[0];
  }
  if(UartData[1]!=0)
  {
     K[1] = (float)UartData[1];
  }
  if(UartData[2]!=0)
  {
     K[2] = (float)UartData[2];
  }
  if(UartData[3]!=0)
  {
    inner_p = (float)UartData[3];
    
  }
  
  if(UartData[4]!=0)
  {
    inner_d  = (float)UartData[4];
  }
  if(UartData[5]!=0)
  {
    speed_p =  (float)UartData[5];
  }
  if(UartData[6]!=0)
  {
    speed_i = (float)UartData[6];
  }
  if(UartData[7]!=0)
  {
    rol = (float)UartData[7];
    roll_setoff = rol;
  }
  if(UartData[8]!=0)
  {
//    pit = (float)UartData[8];
//    pitch_setoff = pit;
//    TIM5->CCR4 = (int)UartData[8];
//    PFout(11)=0;
//    PFout(12)=1;
//    speed_set= (int)UartData[8];
  }
}
/*
命令接收函数
CmdNum：0~255号命令
DATA  ：0~255个命令所对应的命令字
*/
void UartCmd(u8 CmdNum,u8 Data)
{
  if(CmdNum==2&&Data==102)//page up
  {
    start_flag=!start_flag;
//    if(!start_flag)
//      TIM5->CCR4 = 0;
//    speed_inter=0;
  }
  if(CmdNum==2&&Data==103)//page down
  {
//    roll_setoff = roll;
//    pitch_setoff = pitch;
    follow_flag =!follow_flag;
    
  }
  
  if(CmdNum==2&&Data==104)//End
  {
    
  }
}
/*轮询法发送一帧数据
消耗时间与数据长度有关
不可以放在中断里面周期性调用
消耗时间计算看帮助文档
*/
void sendDataToScope(void)
{
  u8 i,sum=0;
  //使用轮询的方式发送数据，当数据未发送，程序停在此处直到发送完成
  USART_SendData(USART1,251); 
  USART_SendData(USART1,109); 
  USART_SendData(USART1,37); 
  sum+=(251); //全部数据加入校验
  sum+=(109);
  sum+=(37);
  for(i=0;i<FreeCarsDataNum;i++)
  {
    USART_SendData(USART1,uSendBuf[i]);
    sum+=uSendBuf[i]; //全部数据加入校验
  }
  USART_SendData(USART1,sum);
}
/*
向示波器某个通道缓冲区填充数据
chanel：通道
data ：数据-32768~32767
push 是用来将数据填充到缓冲区里面，显然date是16位的，因此用两个8位数来储存。
*/
void push(u8 chanel,u16 data)
{
  uSendBuf[chanel*2]=data/256;
  uSendBuf[chanel*2+1]=data%256;
}
//接收中断回调函数
void USART1_IRQHandler(void)  //中断处理函数
{
  static u8 get=10;
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {
    get = USART_ReceiveData(USART1); 
//    static u8 qidong_flag=0;
    if(get=='8') 
    {
      LED_Fill(0);
      LED_P6x8Str(20,0,"unicycle robot");
      LED_P6x8Str(30,2,"=");LED_P6x8Str(80,2,"=");
      LED_P6x8Str(35,3,"=");LED_P6x8Str(75,3,"=");
      LED_P6x8Str(40,4,"=");LED_P6x8Str(70,4,"=");
      LED_P6x8Str(50,6,"---");
      
      go_line_flag=0;
      follow_flag=0;
    }
    else if(get=='1')
    {
      LED_Fill(0);LED_P6x8Str(20,0,"unicycle robot");
        LED_P6x8Str(25,2,"===");LED_P6x8Str(75,2,"===");
  LED_P6x8Str(25,3,"===");LED_P6x8Str(75,3,"===");
  LED_P6x8Str(54,5,"--");
  
      start_flag=1;
      go_line_flag=0;
      follow_flag=0;
    }
      else if(get=='2')
    {
      LED_Fill(0);LED_P6x8Str(20,0,"unicycle robot");
        LED_P6x8Str(25,2,"===");LED_P6x8Str(75,2,"===");
  LED_P6x8Str(25,3,"===");LED_P6x8Str(75,3,"===");
  LED_P6x8Str(54,5,"--");
      start_flag=1;
      go_line_flag=0;
      follow_flag=1;
    }
      else if(get=='3')
      {
        LED_Fill(0);LED_P6x8Str(20,0,"unicycle robot");
          LED_P6x8Str(25,2,"===");LED_P6x8Str(75,2,"===");
  LED_P6x8Str(25,3,"===");LED_P6x8Str(75,3,"===");
  LED_P6x8Str(54,5,"--");
        start_flag=1;
        go_line_flag=1;
        follow_flag=0;
      }
       else if((get=='4'||get=='5')&&start_flag)
      {
        LED_Fill(0);LED_P6x8Str(20,0,"unicycle robot");
          LED_P6x8Str(25,2,"===");LED_P6x8Str(75,2,"===");
  LED_P6x8Str(25,3,"===");LED_P6x8Str(75,3,"===");
  LED_P6x8Str(54,5,"--");
        go_line_flag=0;
        start_flag=0;
        follow_flag=0;
      }
  }



}
//{
//  int i,b,d1;
//  u32 d;
//  //进入接收中断函数
//  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
//  {
//    SerialPortRx.Data = USART_ReceiveData(USART1);  
//    if(SerialPortRx.Stack < UartRxBufferLen)
//    {
//      SerialPortRx.Buffer[SerialPortRx.Stack++] = SerialPortRx.Data;
//      if(SerialPortRx.Stack >= UartRxDataLen//UartRxDataLen个数为一帧
//         && SerialPortRx.Buffer[SerialPortRx.Stack - UartRxDataLen]  ==0xff//校验字头
//           && SerialPortRx.Buffer[SerialPortRx.Stack - UartRxDataLen+1]==0x55
//             && SerialPortRx.Buffer[SerialPortRx.Stack - UartRxDataLen+2]==0xaa
//               && SerialPortRx.Buffer[SerialPortRx.Stack - UartRxDataLen+3]==0x10)
//      {//double data 9个通道数据校验
//        SerialPortRx.Check = 0;
//        b = SerialPortRx.Stack - UartRxDataLen;//起始位
//        for(i=b;i<SerialPortRx.Stack-1;i++)//除校验位外的位进行校验
//        {
//          SerialPortRx.Check += SerialPortRx.Buffer[i];//校验
//        }
//        if(SerialPortRx.Check == SerialPortRx.Buffer[SerialPortRx.Stack-1])
//        {//校验成功，进行数据解算
//          for(i = 0;i<9;i++)
//          {
//            d = SerialPortRx.Buffer[b+i*4+4]*0x1000000L + SerialPortRx.Buffer[b+i*4+5]*0x10000L + SerialPortRx.Buffer[b+i*4+6]*0x100L + SerialPortRx.Buffer[b+i*4+7];
//            if(d>0x7FFFFFFF)
//            {
//              d1 = 0x7FFFFFFF - d;
//            }
//            else
//            {
//              d1 = d;
//            }
//            UartData[i]=d1;
//            UartData[i]/=65536.0;
//          }
//          UartDebug();  //转去处理，把受到的数据付给变量
//        }
//        SerialPortRx.Stack = 0;
//      }
//      else if(SerialPortRx.Stack >= UartRxCmdLen//UartRxDataLen个数为一帧
//              && SerialPortRx.Buffer[SerialPortRx.Stack - UartRxCmdLen]  ==0xff
//                && SerialPortRx.Buffer[SerialPortRx.Stack - UartRxCmdLen+1]==0x55
//                  && SerialPortRx.Buffer[SerialPortRx.Stack - UartRxCmdLen+2]==0xaa
//                    && SerialPortRx.Buffer[SerialPortRx.Stack - UartRxCmdLen+3]==0x77)//cmd
//      {
//        SerialPortRx.Check = 0;
//        b = SerialPortRx.Stack - UartRxCmdLen;//起始位
//        for(i=b; i<SerialPortRx.Stack-1; i++)//除校验位外的位进行校验
//        {
//          SerialPortRx.Check += SerialPortRx.Buffer[i];//校验
//        }
//        if(SerialPortRx.Check == SerialPortRx.Buffer[SerialPortRx.Stack-1])
//        {//校验成功
//          UartCmd(UartCmdNum,UartCmdData);//处理接收到的命令，付给MCU命令变量
//        }
//        SerialPortRx.Stack = 0;
//      }
//    }
//    else
//    {
//      SerialPortRx.Stack = 0;
//    } 
//}
//}


