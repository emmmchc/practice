function BinImg = GetFaceBin(file)
rgb = imread(file);
Ycbcr = rgb2ycbcr(rgb);
%人脸分割阈值
fThreshold = 0.22;
%获取图像宽度，高度和维度。
[M,N,D]=size(Ycbcr);
FaceProbImg = zeros(M,N,1);%肤色后验概率矩阵
BinImg = uint8(zeros(M,N,1));%二值图像
Mean = [117.4316 148.5599]';%肤色均值
C = [97.0946 24.4700;
        24.4700 141.9966];%肤色方差
cbcr = zeros(2,1);%颜色分量，Y分量差异较大，只用CbCr分量。
for i=1:M
    for j=1:N
        cbcr(1) = Ycbcr(i,j,2);
        cbcr(2) = Ycbcr(i,j,3);
        FaceProbImg(i,j)=exp(-0.5*(cbcr-Mean)'*inv(C)*(cbcr-Mean));%计算肤色高斯后验概率         
        if FaceProbImg(i,j)>fThreshold%如果大于阈值认为是人脸区域           
            BinImg(i,j) = 1;%生成二值图像
        end          
    end
end
se=strel('disk',3');
BinImg = imopen(BinImg,se); %使用3*3圆盘，进行图像开操作（先腐蚀后膨胀，滤除孤立点）
imdilate(BinImg,se);
 subplot(122);imshow(BinImg*255);title('腐蚀膨胀');
CC = bwconncomp(BinImg);%获取联通区域
numPixels = cellfun(@numel,CC.PixelIdxList);%计算联通区域面积。
[biggest,idx] = max(numPixels);%获取最大的联通区域坐标
for i=1:CC.NumObjects%只留最大的联通区域，去除其他的联通区域
 if i~=idx
 BinImg(CC.PixelIdxList{i}) = 0;
 end
end

 figure(2);imshow(uint8(BinImg*255));%显示二值化图像
end

