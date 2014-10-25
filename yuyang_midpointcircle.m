r=20;
hold on;
grid on;
axis equal;
x = -r:0.01:r; 
y = sqrt(r^2-x.^2); 
plot(x,y,x,-y,'b-');
x=0;y=r;d=1.25-r;

plot(x,y,'r.');
while x<=y;
    if d<0;
        d=d+2*x+3;
    else
       d=2*(x-y)+5;y=y-1;
    end
    x=x+1;
   plot(x,y,'r.');
end