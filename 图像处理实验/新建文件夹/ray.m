function new=ray(img_name) 
%采用Gray World色彩均衡法进行光照补偿
im=imread(img_name);
subplot(1,2,1);
imshow(im);
s=size(im);
R=im(:,:,1);
G=im(:,:,2);
B=im(:,:,3);
R=reshape(R,[s(1),s(2)]);
G=reshape(G,[s(1),s(2)]);
B=reshape(B,[s(1),s(2)]);
r=mean(mean(R));%红色均值
g=mean(mean(G));%绿色均值
b=mean(mean(B));%蓝色均值
k=(r+g+b)/3;
for i=1:s(1)
    for j=1:s(2)
        R(i,j)=R(i,j)*(k/r);
        G(i,j)=G(i,j)*(k/g);
        B(i,j)=B(i,j)*(k/b);
    end
end
new=cat(3,R,G,B);

return new;
