cla;
M1 = csvread('�˲���ֹ.csv');M1 = M1(1:200,:);
M2 = csvread('�˲��˶�.csv');M2 = M2(1:200,:);
M3 = csvread('���ݾ�ֹ.csv');M3 = M3(1:200,:);
M4 = csvread('�����˶�.csv');M4 = M4(1:200,:);

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

xlabel('ʱ�䣨��λ���룩')
ylabel('��̬�ǣ���λ���ȣ�')
title('��̬�������ߣ����ٽ���-��ֹ��')
legend('����yaw��','������pitch��','�����roll)')