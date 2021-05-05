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
     0 0 110
    ];  

R = 1000;

%计算K  
K = lqr(A,B,Q,R);  
Ac = A - B*K;  
%对系统进行模拟  
x0 = [-6.56;0;0]; %初始状态  
t = 0:0.01:7.5;  
u = zeros(size(t));  
[y,x]=lsim(Ac,B,C,D,u,t,x0);

% uu =  zeros(size(t)); 
% ii=1;
% for i = 0:0.01:5
%  uu(ii) = -(K(1)*x(ii,1) + K(2)*x(ii,2) + K(3)*x(ii,3));
%  ii=ii+1;
% end

figure(1);
plot(t,y,'r');hold on;
% title('曲线对照图');
% 
% aaa=xxx(565:1300,:)/100+0.2;
% t=(0:size(aaa,1)-1)*0.01;
% for i=1:1:size(aaa)
%         if(aaa(i)>0.7)aaa(i)=aaa(i)/3;
%         end
% end
% plot(t,aaa/2,'b');

% hold on;
% legend('仿真曲线','实际曲线');

xlabel('时间（s）');
ylabel('横滚角(°)');

% figure(3);
% plot(t,uu); 
% title('输出');
% 
% figure(4);
% plot(t,x(1:61,3)*0.1/360*44);
% title('编码器');
