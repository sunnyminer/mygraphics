x0 = 0;y0 =0;x1 =20;y1=10;
hold on; 
grid on;
axis equal;
plot([x0,x1],[y0,y1] ,'g-');

a=y0-y1;b=x1-x0;d=2*a+b;
d1=2*a;d2=2*(a+b);

while x0<=x1
    plot(x0,y0,'r.');
    if d<0;
        x0=x0+1;y0=y0+1;d=d+d2;
    else 
        x0=x0+1;d=d+d1;
    end
end