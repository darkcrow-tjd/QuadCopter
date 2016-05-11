global ANGLE;
initialSerial('COM18');

while(1)
    drawModel(ANGLE);
    pause(0.03);
end
