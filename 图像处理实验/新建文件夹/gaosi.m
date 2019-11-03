
cb = 0:0.1:250;
cr = cb;
Z = zeros(2501,2501);
M = [117.43 156.60]';
C = [160.13 12.14;12.14 299.46];    
for i=1:2501
    for j=1:2501
        Z(i,j)=(1/(2*pi*sqrt(det(C))))*exp(-0.5*([cb(i);cr(j)]-M)'*inv(C)*([cb(i);cr(j)]-M));
    end
end
mesh(cb,cr,Z)