% ���ݵ�ǰ���Cb Crֵ�ж��Ƿ�Ϊ��ɫ  
function result = skin(Y,Cb,Cr)  
% % ����  
% a = 25.39;  
% b = 14.03;  
% ecx = 1.60;  
% ecy = 2.41;  
% sita = 2.53;  
% cx = 109.38;  
% cy = 152.02;  
% xishu = [cos(sita) sin(sita);-sin(sita) cos(sita)];  
% % ������ȴ���230���򽫳�����ͬʱ����Ϊԭ����1.1��  
% if(Y > 230)  
    % a = 1.1*a;  
    % b = 1.1*b;  
% end  
% % ���ݹ�ʽ���м���  
% Cb = double(Cb);  
% Cr = double(Cr);  
% t = [(Cb-cx);(Cr-cy)];  
% temp = xishu*t;  
% value = (temp(1) - ecx)^2/a^2 + (temp(2) - ecy)^2/b^2;  
% % ����1���Ƿ�ɫ������0������Ϊ��ɫ������1  
% if value > 1  
    % result = 0;
% else
    % result = 1;  
% end  
m = [117.4316;148.5599];%��ɫ��ֵ
%C = [97.0946 24.4700;24.4700 141.9966];%��ɫ����
C = [0.0108 -0.0019;-0.0019 0.0074];
x = [Cb;Cr];%��ɫ������ֻ��CbCr����
val=exp(-0.5*(x-m)'*C*(x-m));%��ɫ��˹����
if val>0.22  
    result = 1;
else
    result = 0;  
end  