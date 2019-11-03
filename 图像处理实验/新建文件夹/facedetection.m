function facedetection(img_name)
  
%读取RGB图像,
% 采用Gray World色彩均衡法进行光照补偿
 im=imread(img_name);
 subplot(1,4,1);
 imshow(im);
% imshow(im);
% s=size(im);
% R=im(:,:,1);
% G=im(:,:,2);
% B=im(:,:,3);
% R=reshape(R,[s(1),s(2)]);
% G=reshape(G,[s(1),s(2)]);
% B=reshape(B,[s(1),s(2)]);
% r=mean(mean(R));%红色均值
% g=mean(mean(G));%绿色均值
% b=mean(mean(B));%蓝色均值
% k=(r+g+b)/3;
% for i=1:s(1)
    % for j=1:s(2)
        % R(i,j)=R(i,j)*(k/r);
        % G(i,j)=G(i,j)*(k/g);
        % B(i,j)=B(i,j)*(k/b);
    % end
% end
% new=cat(3,R,G,B);

% 转换为灰度图像  
gray = rgb2gray(im); 

% 获得图像宽度和高度  
[Height,Width] = size(gray);

%肤色分割阈值
Threshold = threshold(gray)
 
% 将图像转化为YCbCr颜色空间  
Ycbcr = rgb2ycbcr(im);  
  
% 根据肤色模型将图像二值化 
P = zeros(Height,Width);%肤色概率矩阵

M = [114.3763 150.1374]';%肤色均值
C = [99.7596 -68.6397;-68.6397 84.49837];%肤色方差
for i=1:Height
    for j=1:Width
		x = double([Ycbcr(i,j,2);Ycbcr(i,j,3)]);
        P(i,j)=exp(-0.5*(x-M)'*inv(C)*(x-M));%计算肤色高斯概率         
		if P(i,j)*255 > Threshold
			gray(i,j) = 255;
		else
			gray(i,j) = 0;
		end
    end
end
subplot(1,4,2);
imshow(gray);

% 二值图像形态学处理  
Block=strel('disk',5); 
  
% imclose先膨胀再腐蚀
gray = imclose(gray,Block);  

subplot(1,4,3);
imshow(gray);  

% 取出图片中所有包含白色区域的最小矩形  
[L,num] = bwlabel(gray,8);
STATS = regionprops(L,'BoundingBox')
% 存放经过筛选以后得到的所有矩形块

subplot(1,4,4);
imshow(im);
%对连通区域画矩形
for i = 1:num
    pos = STATS(i).BoundingBox; 
	%pos(1) (2) (3) (4) 分别对应矩形坐标(x,y),宽,高
	
	%高与宽之比在0.6~1.8
	rate = pos(4)/pos(3);
	if rate>0.6 && rate<1.8 && pos(3)*pos(4)>400 && pos(3)>20 && pos(4)>20
		rectangle('position',pos,'edgecolor','r');
	end
end	
