function result = black2white( im )
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here
[he wi t] = size(im)
for i=1:he
    for j=1:wi
       r = im(i,j,1);
       g = im(i,j,2);
       b = im(i,j,3);
       if r==0 && g==0 && b==0 
           im(i,j,1) = 255;
           im(i,j,2) = 255;
           im(i,j,3) = 255;
       end
    end
end
    result = im;
end

