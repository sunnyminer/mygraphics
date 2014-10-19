function liang_barskey_m
//这是梁-barskey算法的matlab实现

 x1 = 50;y1 =300;x2 =500;y2 =50; 
 x=[100,300,300,100,100];y=[100,100,250,250,100];
 xl = min(x);yb = min(y);xr = max(x);yt = max(y);



hold on;axis equal;
 plot([x1,x2],[y1,y2],'b');
plot(x,y,'g');

 u1=0;u2=1;dx=x2-x1;dy=y2-y1;
 [u1,u2,flag]=clipt(-dx,x1-xl,u1,u2);
  if flag
    [u1,u2,flag]=clipt(dx,xr-x1,u1,u2);
   if flag 
        [u1,u2,flag]=clipt(-dy,y1-yb,u1,u2);
        if flag
            [u1,u2,flag]=clipt(dy,yt-y1,u1,u2);
           if flag
                plot([x1+u1*dx ,x1+u2*dx],[y1+u1*dy, y1+u2*dy],'r','LineWidth',2); 
             end
        end
    end
  end

function [u1,u2,mflag]=clipt(p,q,u1,u2)
mflag = 1;
    if p<0
        r=q/p;
        if r>u2      mflag=0;
        elseif r>u1 u1=r;end
    elseif  p>0
        r=q/p;
        if r<u1 flag=flase
        elseif r<u2 u2=r;end
    elseif q<0 flag = flase;
    end
    
