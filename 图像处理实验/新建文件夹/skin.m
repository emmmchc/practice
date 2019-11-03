% 根据当前点的Cb Cr值判断是否为肤色  
function result = skin(Y,Cb,Cr)  
% % 参数  
% a = 25.39;  
% b = 14.03;  
% ecx = 1.60;  
% ecy = 2.41;  
% sita = 2.53;  
% cx = 109.38;  
% cy = 152.02;  
% xishu = [cos(sita) sin(sita);-sin(sita) cos(sita)];  
% % 如果亮度大于230，则将长短轴同时扩大为原来的1.1倍  
% if(Y > 230)  
    % a = 1.1*a;  
    % b = 1.1*b;  
% end  
% % 根据公式进行计算  
% Cb = double(Cb);  
% Cr = double(Cr);  
% t = [(Cb-cx);(Cr-cy)];  
% temp = xishu*t;  
% value = (temp(1) - ecx)^2/a^2 + (temp(2) - ecy)^2/b^2;  
% % 大于1则不是肤色，返回0；否则为肤色，返回1  
% if value > 1  
    % result = 0;
% else
    % result = 1;  
% end  
m = [117.4316;148.5599];%肤色均值
%C = [97.0946 24.4700;24.4700 141.9966];%肤色方差
C = [0.0108 -0.0019;-0.0019 0.0074];
x = [Cb;Cr];%颜色分量，只用CbCr分量
val=exp(-0.5*(x-m)'*C*(x-m));%肤色高斯概率
if val>0.22  
    result = 1;
else
    result = 0;  
end  