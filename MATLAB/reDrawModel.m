function model = reDrawModel(model, angle)
    angle_pitch = angle(1,1);  % ��x����ת
    angle_roll = angle(1,2);   % ��y����ת
    angle_yaw = angle(1,3);    % ��z����ת
    
    rotate(model,[1 0 0],angle_pitch);
    rotate(model,[0 1 0],angle_roll);
    rotate(model,[0 0 1],angle_yaw);
end
