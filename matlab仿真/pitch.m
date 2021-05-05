ts=0.005;  %采样时间=0.05s
sys=tf(0.998,[0.021,1]);   %建立被控对象传递函数，即式4.1
dsys=c2d(sys,ts,'z');      %离散化
[num,den]=tfdata(dsys,'v');   %
e_1=0;      %前一时刻的偏差      
Ee=0;       %累积偏差
u_1=0.0;    %前一时刻的控制量
y_1=0;       %前一时刻的输出
%PID参数
kp=0.009;    
ki=0.17;
kd=0;
u=zeros(1,2000);%预先分配内存
time=zeros(1,2000);%时刻点（设定1000个）

for k=1:1:2000
    time(k)=k*ts;   %时间参数
    r(k)=10;      %期望值
    y(k)=-1*den(2)*y_1+num(2)*u_1+num(1)*u(k);%系统响应输出序列
    e(k)=r(k)-y(k);   %误差信号
    u(k)=kp*e(k)+ki*Ee+kd*(e(k)-e_1); %系统PID控制器输出序列
    Ee=Ee+e(k);    %误差的累加和
    u_1=u(k);    	%前一个的控制器输出值
    y_1=y(k);    	%前一个的系统响应输出值
    e_1=e(k);		%前一个误差信号的值
end
%（仅绘制过渡过程的曲线，x坐标限制为[0,1]）
figure(1);

p2=plot(time,y-10,'r');xlim([0,10]);%不含积分分离的PID曲线
hold on;

aaa=xxx(137:2000,:)/100-0.4;
t=(0:size(aaa,1)-1)*0.01;

plot(t,aaa/2,'b');

hold on;
legend('仿真曲线','实际曲线');
title('曲线对照图');
xlabel('时间（s）');
ylabel('俯仰角(°)');



