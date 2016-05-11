%%
s = serial('COM18');
set(s, 'BaudRate', 115200, 'DataBits', 8, 'StopBits', 1, 'Parity', 'none', 'FlowControl', 'none');
s.BytesAvailableFcnMode = 'terminator';
s.BytesAvailableFcn = {@callback};
try
    fopen(s);
catch
    error('Can not open serial');
end

pause;
fclose(s);
delete(s);
clear s


