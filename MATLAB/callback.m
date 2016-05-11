
%%
function callback(s, ~)
    out = fscanf(s);
    
    result = regexp(out,'\S*','match');
    yaw = str2double(result(2));
    pitch = str2double(result(3));
    roll = str2double(result(4));
    global ANGLE;
    ANGLE = [pitch roll yaw];
    disp([pitch roll yaw]);
end