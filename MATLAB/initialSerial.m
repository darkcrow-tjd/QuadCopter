%%
function serialPort = initialSerial(port)
    serialPort = serial('COM18');
    set(serialPort, 'BaudRate', 115200, 'DataBits', 8, 'StopBits', 1, 'Parity', 'none', 'FlowControl', 'none');
    serialPort.BytesAvailableFcnMode = 'terminator';
    serialPort.BytesAvailableFcn = {@callback};
    try
        fopen(serialPort);
    catch
        error('Can not open serial');
    end

    global ANGLE;
    ANGLE = [0 0 0];
    while(1)
        drawModel(ANGLE);
        pause(0.03);
    end

    fclose(serialPort);
    delete(serialPort);
    clear serialPort
end

