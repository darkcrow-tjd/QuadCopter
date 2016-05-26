function model = drawModel()
    clf reset,k=8; %k ��ȡֵ��Ӱ����ɫ
    X =     [0 1 1 0; 1 1 1 1; 1 0 0 1; 0 0 0 0; 0 1 1 0; 0 1 1 0]';
    Y = 1.5*[0 0 0 0; 0 1 1 0; 1 1 1 1; 1 0 0 1; 0 0 1 1; 0 0 1 1]';
    Z = 0.5*[0 0 1 1; 0 0 1 1; 0 0 1 1; 0 0 1 1; 0 0 0 0; 1 1 1 1]';

    FC=k:(k+size(Z,2)-1);
    model = patch(X,Y,Z,FC); %������ɫ
    set(gca,'Projection','pers'); % ����͸��ͶӰ
    view([-20 12]),colormap(jet),axis equal, axis off
end



