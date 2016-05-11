function model = drawModel()
    clf reset,k=8; %k 的取值不影响着色
    X =     [0 1 1 0; 1 1 1 1; 1 0 0 1; 0 0 0 0; 0 1 1 0; 0 1 1 0]';
    Y = 1.5*[0 0 0 0; 0 1 1 0; 1 1 1 1; 1 0 0 1; 0 0 1 1; 0 0 1 1]';
    Z = 0.5*[0 0 1 1; 0 0 1 1; 0 0 1 1; 0 0 1 1; 0 0 0 0; 1 1 1 1]';

    FC=k:(k+size(Z,2)-1);
    model = patch(X,Y,Z,FC); %以面着色
    set(gca,'Projection','pers'); % 采用透视投影
    view([-20 12]),colormap(jet),axis equal, axis off
end



