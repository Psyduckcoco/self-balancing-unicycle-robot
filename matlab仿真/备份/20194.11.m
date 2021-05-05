M = 0.3024;%飞轮质量
R = 0.056;%飞轮半径

L = 0.1225;%飞轮质心到底端距离

m = 0.8718;%除了飞轮和旋转轮之外的全部质量  
l = 0.0935  ;%除了飞轮之外的质量的质心到底端距离 

m3=0.145;%旋转轮质量
l3=0.22;%旋转轮质心到地面距离

g=9.8;%重力加速度
Ipb = m*l*l;
%  Iwc = 0.00019685 ;%或者solidworks可直接得出 kg.m^2
 Iwc = 0.5*M*R*R;%或者solidworks可直接得出 kg.m^2
a = M*L*L + Ipb+m3*l3*l3;
b = m*l + M*L+m3*l3;
A = [0      1   0
     b*g/a  0   0
     -b*g/a 0   0
    ];%状态矩阵
B = [0;-1/a;(a+Iwc)/(a*Iwc)];%输入矩阵
C = [1 0 0];   %观测角度  
D = 0;

Q = [10000000*5 0 0 
     0 100000 0 
     0 0 50
    ];  

R = 2.5;

%计算K  
K = lqr(A,B,Q,R);  
Ac = A - B*K;  
%对系统进行模拟  
x0 = [2;0;0]; %初始状态  
t = 0:0.05:3;  
u = zeros(size(t));  
[y,x]=lsim(Ac,B,C,D,u,t,x0);

uu =  zeros(size(t)); 
ii=1;
for i = 0:0.05:3
 uu(ii) = -(K(1)*x(ii,1) + K(2)*x(ii,2) + K(3)*x(ii,3));
 ii=ii+1;
end
figure(1);
plot(t,y);
title('pitch');


figure(3);
plot(t,uu); 
title('输出');

figure(4);
plot(t,x(1:61,3)*0.1/360*44);
title('编码器');
