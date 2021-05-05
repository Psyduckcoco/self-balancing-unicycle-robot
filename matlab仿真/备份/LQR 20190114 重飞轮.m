M = 0.3025;%飞轮质量
R = 0.056;%飞轮半径
L = 0.151;%飞轮质心到底端距离

m = 0.9313;%除了飞轮之外的全部质量
l = 0.085    ;%除了飞轮之外的质量的质心到底端距离 

g=9.8;%重力加速度
 Ipb = m*l*l;
 Iwc = 0.5*M*R*R;%或者solidworks可直接得出 kg.m^2
a = M*L*L + Ipb;
b = m*l + M*L;
A = [0      1   0
     b*g/a  0   0
     -b*g/a 0   0
    ];%状态矩阵
B = [0;1/a;-(a+Iwc)/(a*Iwc)];%输入矩阵
C = [1 0 0];   %观测角度  
D = 0;

Q = [10000000 0 0 
     0 1000 0 
     0 0 200
    ];  
R = 1;

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
% figure(2);
% plot(t,y,t,uu);  
figure(3);
plot(t,uu); 
title('输出');
figure(4);
plot(t,x(1:61,3)*0.1/360*44);
title('角速度 编码器');
