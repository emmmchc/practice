function facedetection(img_name)
  
%��ȡRGBͼ��,
% ����Gray Worldɫ�ʾ��ⷨ���й��ղ���
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
% r=mean(mean(R));%��ɫ��ֵ
% g=mean(mean(G));%��ɫ��ֵ
% b=mean(mean(B));%��ɫ��ֵ
% k=(r+g+b)/3;
% for i=1:s(1)
    % for j=1:s(2)
        % R(i,j)=R(i,j)*(k/r);
        % G(i,j)=G(i,j)*(k/g);
        % B(i,j)=B(i,j)*(k/b);
    % end
% end
% new=cat(3,R,G,B);

% ת��Ϊ�Ҷ�ͼ��  
gray = rgb2gray(im); 

% ���ͼ���Ⱥ͸߶�  
[Height,Width] = size(gray);

%��ɫ�ָ���ֵ
Threshold = threshold(gray)
 
% ��ͼ��ת��ΪYCbCr��ɫ�ռ�  
Ycbcr = rgb2ycbcr(im);  
  
% ���ݷ�ɫģ�ͽ�ͼ���ֵ�� 
P = zeros(Height,Width);%��ɫ���ʾ���

M = [114.3763 150.1374]';%��ɫ��ֵ
C = [99.7596 -68.6397;-68.6397 84.49837];%��ɫ����
for i=1:Height
    for j=1:Width
		x = double([Ycbcr(i,j,2);Ycbcr(i,j,3)]);
        P(i,j)=exp(-0.5*(x-M)'*inv(C)*(x-M));%�����ɫ��˹����         
		if P(i,j)*255 > Threshold
			gray(i,j) = 255;
		else
			gray(i,j) = 0;
		end
    end
end
subplot(1,4,2);
imshow(gray);

% ��ֵͼ����̬ѧ����  
Block=strel('disk',5); 
  
% imclose�������ٸ�ʴ
gray = imclose(gray,Block);  

subplot(1,4,3);
imshow(gray);  

% ȡ��ͼƬ�����а�����ɫ�������С����  
[L,num] = bwlabel(gray,8);
STATS = regionprops(L,'BoundingBox')
% ��ž���ɸѡ�Ժ�õ������о��ο�

subplot(1,4,4);
imshow(im);
%����ͨ���򻭾���
for i = 1:num
    pos = STATS(i).BoundingBox; 
	%pos(1) (2) (3) (4) �ֱ��Ӧ��������(x,y),��,��
	
	%�����֮����0.6~1.8
	rate = pos(4)/pos(3);
	if rate>0.6 && rate<1.8 && pos(3)*pos(4)>400 && pos(3)>20 && pos(4)>20
		rectangle('position',pos,'edgecolor','r');
	end
end	
