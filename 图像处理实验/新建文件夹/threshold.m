function threshold=threshold(scoreImage)  
[height,length]=size(scoreImage);  
totalNum=height*length;  
pixelCount=zeros(1,256);%统计各个像素值的个数  
for i=1:length  
    for j=1:height  
        number=scoreImage(j,i)+1;  
        pixelCount(number)=pixelCount(number)+1;  
    end  
end  
pf=pixelCount/totalNum;  
deltaMax=0;  
a=1:256;  
maxmax=max(max(scoreImage));  
for i=1:maxmax  
      
    w1=sum(pf(1:i));  
    w2=1-w1;  
    mean1=sum(pf(1:i).*a(1:i))/sum(pf(1:i));  
    mean2=sum(pf(i+1:maxmax).*a(i+1:maxmax))/sum(pf(i+1:maxmax));  
    delta=w1*w2*(mean1-mean2)^2;  
    if delta>deltaMax  
        deltaMax=delta;  
        threshold=i;  
    end   
end  

