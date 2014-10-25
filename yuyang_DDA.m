x0 = 0; y0 = 0; x1 = 10; y1 = 20;
hold on; 
grid on;
axis equal;
plot([x0 x1],[y0 y1],'g-');

k = (y1-y0)/(x1-x0);
if abs(k)<=1;
x = x0; y = y0;

while x <= x1	   
 	plot(x,floor(y+0.5),'m.');	
    y = y + k; 
    x = x + 1; 
end
else
    x = x0; y = y0;

while y <= y1	   
 	plot(floor(x+0.5),y,'m.');	
    y = y + 1; 
    x = x + 1/k;
end
end
hold off;

