cla;
M1 = csvread('滤波静止.csv');M1 = M1(1:200,:);
M2 = csvread('滤波运动.csv');M2 = M2(1:200,:);
M3 = csvread('陀螺静止.csv');M3 = M3(1:200,:);
M4 = csvread('陀螺运动.csv');M4 = M4(1:200,:);

M1 = M3;

yaw = abs(M1(:,1));
pitch = abs(M1(:,2));
roll = abs(M1(:,3));

x = 1:1:size(M1);
x = x/100;

plot(x,yaw,'r-');hold on;
plot(x,pitch,'b-');
plot(x,roll,'k-');
plot(0,0);

xlabel('时间（单位：秒）')
ylabel('姿态角（单位：度）')
title('姿态解算曲线（快速解算-静止）')
legend('航向（yaw）','俯仰（pitch）','横滚（roll)')