x0=0;y0=0;x1=20;y1=10;
hold on;
plot([x0 x1],[y0 y1],'g-');
dx = x1-x0;dy=y1-y0;
k=dy/dx;
e=-0.5; 
i=0;
while i<=dx;
    plot( x0,y0,'r.');
    x0=x0+1;e=e+k;
    if e>=0;
        y0=y0+1;e=e-1;
    end
    i=i+1;
end
