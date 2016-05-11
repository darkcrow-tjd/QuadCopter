function model = reDrawModel(model, angle)
    angle_pitch = angle(1,1);  % ÈÆxÖáĞı×ª
    angle_roll = angle(1,2);   % ÈÆyÖáĞı×ª
    angle_yaw = angle(1,3);    % ÈÆzÖáĞı×ª
    
    rotate(model,[1 0 0],angle_pitch);
    rotate(model,[0 1 0],angle_roll);
    rotate(model,[0 0 1],angle_yaw);
end
