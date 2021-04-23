#include "init.h"
#include "includes.h"
/*--------PID初始化------*/
void parameter_Init(void)
{
//  
//  K[0] = 0;
//  K[1] = 0;
//  K[2] = 0;
//  
//  pitch_P = 0;
//  pitch_D = 0;
//  encoder_P = 0;
//  encoder_I=0;
  
  
  
  K[0] = 6581.3;
  K[1] = 592.2085;
  K[2] = 6.3246;
  
  
  inner_p = 1400;
  inner_d = 1.69;
  speed_p=1.6;
  speed_i=0.015;
  
//  pitch_P = 1080;
//  pitch_D = 1.2;
//  encoder_P = 30;
//  encoder_I=0.1;
//  
}
/*-------初始化电机 TIM3-------*/
//TIM3->CCR1 = xxx;
void Tim3_init(u16 arr,u16 psc)
{
  /*初始化IO口*/
  GPIO_InitTypeDef GPIO_InitStructure;
  //使能电机用的时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB |RCC_APB2Periph_GPIOA, ENABLE); 
  //设置电机使用到得管脚
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 ; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1  ; 
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  /*------------*/
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能定时器3时钟
  
  //初始化TIM3
  TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
  TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值 
  TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
  
  //初始化TIM3 Channel2 PWM模式	 
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
  
  TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC1
  TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC2
  TIM_OC3Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC3
  TIM_OC4Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC4
  
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR1上的预装载寄存器
  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器
  TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR3上的预装载寄存器
  TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR4上的预装载寄存器
  
  
  TIM_Cmd(TIM3, ENABLE);  //使能TIM3
  
  TIM3->CCR1 = 0;
  TIM3->CCR2 = 0;
  TIM3->CCR3 = 0;
  TIM3->CCR4 = 0;
  
}
/*-------初始化电机 TIM3-------*/
//TIM3->CCR1 = xxx;
void Tim5_init(u16 arr,u16 psc)
{
  /*初始化IO口*/
  GPIO_InitTypeDef GPIO_InitStructure;
  //使能电机用的时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOF , ENABLE); 
  //设置电机使用到得管脚
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 ; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 |GPIO_Pin_12; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOF, &GPIO_InitStructure);
  
  /*------------*/
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);	//使能定时器3时钟
  
  //初始化TIM3
  TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
  TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值 
  TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
  TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
  
  //初始化TIM3 Channel2 PWM模式	 
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
  
  TIM_OC4Init(TIM5, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC4
  
  TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable);  //使能TIM3在CCR4上的预装载寄存器
  
  
  TIM_Cmd(TIM5, ENABLE);  //使能TIM3
  
  TIM5->CCR4 = 0;
  
  
}
/*-----编码器初始化 TIM2----*/
void Encoder_Init_TIM2(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef TIM_ICInitStructure;  
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//使能定时器4的时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//使能PB端口时钟
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;	//端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);					      //根据设定参数初始化GPIOB
  
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // 预分频器 
  TIM_TimeBaseStructure.TIM_Period = 0xFFFF; //设定计数器自动重装值
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//选择时钟分频：不分频
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;////TIM向上计数  
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
  TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 6;
  TIM_ICInit(TIM2, &TIM_ICInitStructure);
  TIM_ClearFlag(TIM2, TIM_FLAG_Update);//清除TIM的更新标志位
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  //Reset counter  
  TIM_SetCounter(TIM2,0);
  TIM_Cmd(TIM2, ENABLE); 
}
/*-----编码器初始化 TIM4----*/
void Encoder_Init_TIM4(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef TIM_ICInitStructure;  
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//使能定时器4的时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//使能PB端口时钟
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	//端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
  GPIO_Init(GPIOB, &GPIO_InitStructure);					      //根据设定参数初始化GPIOB
  
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // 预分频器 
  TIM_TimeBaseStructure.TIM_Period = 0xFFFF; //设定计数器自动重装值
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//选择时钟分频：不分频
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;////TIM向上计数  
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
  TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 6;
  TIM_ICInit(TIM4, &TIM_ICInitStructure);
  TIM_ClearFlag(TIM4, TIM_FLAG_Update);//清除TIM的更新标志位
  TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
  //Reset counter
  TIM_SetCounter(TIM4,0);
  TIM_Cmd(TIM4, ENABLE); 
}

/*-----读取编码器---*/
u16 TIM_Get_Counter(u8 TIMX)
{
  u16 Encoder_TIM;    
  switch(TIMX)
  {
  case 2:  Encoder_TIM= TIM2 -> CNT;  TIM2 -> CNT=0;break;
  case 4:  Encoder_TIM= TIM4 -> CNT;  TIM4 -> CNT=0;break;	
  default:  Encoder_TIM=0;
  }
  return Encoder_TIM;
}
/*------初始化定时器TIM1---------*/
void TIM1_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
//  NVIC_InitTypeDef NVIC_InitStructure2;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); //①时钟 TIM1 使能
  //定时器 TIM1 初始化
  TIM_TimeBaseStructure.TIM_Period = arr; //设置自动重装载寄存器周期的值
  TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置时钟频率除数的预分频值
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM 向上计数
  TIM_TimeBaseStructure.TIM_RepetitionCounter=0; //高级定时器1是用定时器功能配置这个才可以是正常的计数频率一开始的72mhz 值得注意的地方
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //②初始化 TIM1
  TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE ); //③允许更新中断

//  //中断优先级 NVIC 设置
//  NVIC_InitStructure2.NVIC_IRQChannel = TIM1_UP_IRQn; //TIM1 中断
//  NVIC_InitStructure2.NVIC_IRQChannelPreemptionPriority = 0; //先占优先级 1 级
//  NVIC_InitStructure2.NVIC_IRQChannelSubPriority = 0; //从优先级 3 级
//  NVIC_InitStructure2.NVIC_IRQChannelCmd = ENABLE; //IRQ 通道被使能
//  NVIC_Init(&NVIC_InitStructure2); //④初始化 NVIC 寄存器
  
  TIM_Cmd(TIM1, ENABLE); //⑤使能 TIM1
}
//定时器 串口
void My_NVIC_Init(void)
{
  static NVIC_InitTypeDef  NVIC_InitStructure;
  /*Usart1 NVIC配置*/
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;	//抢占优先级1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//从优先级1
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
  NVIC_Init(&NVIC_InitStructure);							//根据指定的参数初始化VIC寄存器 
  
  static  NVIC_InitTypeDef NVIC_InitStructure2;
  //中断优先级 NVIC 设置
  NVIC_InitStructure2.NVIC_IRQChannel = TIM1_UP_IRQn; //TIM1 中断
  NVIC_InitStructure2.NVIC_IRQChannelPreemptionPriority = 1; //先占优先级 1 级
  NVIC_InitStructure2.NVIC_IRQChannelSubPriority = 0; //从优先级 3 级
  NVIC_InitStructure2.NVIC_IRQChannelCmd = ENABLE; //IRQ 通道被使能
  NVIC_Init(&NVIC_InitStructure2); //④初始化 NVIC 寄存器
  
  
}
void  Adc_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC2	, ENABLE );	  //使能ADC1通道时钟
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

	//PA1 作为模拟通道输入引脚                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

	ADC_DeInit(ADC2);  //复位ADC1,将外设 ADC1 的全部寄存器重设为缺省值

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//模数转换工作在单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//模数转换工作在单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC2, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   

  
	ADC_Cmd(ADC2, ENABLE);	//使能指定的ADC1
	
	ADC_ResetCalibration(ADC2);	//使能复位校准  
	 
	while(ADC_GetResetCalibrationStatus(ADC2));	//等待复位校准结束
	
	ADC_StartCalibration(ADC2);	 //开启AD校准
 
	while(ADC_GetCalibrationStatus(ADC2));	 //等待校准结束
 
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能

}				  
//获得ADC值
u16 Get_Adc(u8 ch)   
{
  	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC2, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期	  			    
  
	ADC_SoftwareStartConvCmd(ADC2, ENABLE);		//使能指定的ADC1的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC ));//等待转换结束

	return ADC_GetConversionValue(ADC2);	//返回最近一次ADC1规则组的转换结果
}
////获得ADC值
//u16 Get_Adc_dis(u8 ch)   
//{
//  	//设置指定ADC的规则组通道，一个序列，采样时间
//	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期	  			    
//  
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能	
//	 
//	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
//
//	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
//}

void tube_init()
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOC,ENABLE);//使能PORTC时钟
  
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //
  GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIO
  
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4|GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //
  GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIO
  

}
