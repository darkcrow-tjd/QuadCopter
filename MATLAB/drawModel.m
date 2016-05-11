function model = drawModel(angle)
    clf reset,k=8; %k 的取值不影响着色
    X =     [0 1 1 0; 1 1 1 1; 1 0 0 1; 0 0 0 0; 0 1 1 0; 0 1 1 0]';
    Y = 1.5*[0 0 0 0; 0 1 1 0; 1 1 1 1; 1 0 0 1; 0 0 1 1; 0 0 1 1]';
    Z = 0.5*[0 0 1 1; 0 0 1 1; 0 0 1 1; 0 0 1 1; 0 0 0 0; 1 1 1 1]';

    FC=k:(k+size(Z,2)-1);
    model = patch(X,Y,Z,FC); %以面着色
    
    angle_pitch = angle(1,1);  % 绕x轴旋转
    angle_roll = angle(1,2);   % 绕y轴旋转
    angle_yaw = angle(1,3);    % 绕z轴旋转
    
    rotate(model,[1 0 0],angle_pitch);
    rotate(model,[0 1 0],angle_roll);
    rotate(model,[0 0 1],angle_yaw);
    
    set(gca,'Projection','pers'); % 采用透视投影
    view([-20 12]),colormap(jet),axis equal, axis off
end
