global ANGLE;
ANGLE = [0 0 0];

initialSerial('COM18');

while(1)
    subplot(2,2,3);plot(1,ANGLE);grid on;xlabel('ʱ��/s');ylabel('�Ƕ�/��');title('�Ƕ�����');
    pause(0.05);
end
