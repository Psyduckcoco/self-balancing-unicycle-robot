figure(1);
a=before(100:2000,:)/100;
b=after(1200:3100,:)/200;
t=(0:size(a,1)-1)*0.01;

plot(t,a,'r');
hold on;
plot(t,b,'b');
hold on;

legend('未加控制','加入风控');
title('曲线对照图');
xlabel('时间（s）');
ylabel('Z轴角速度原始数据');

