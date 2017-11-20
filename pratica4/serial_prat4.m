
porta = serial('COM24', 'Baudrate', 9600);
if (isvalid(porta)==0)
    a=2
    
    fclose(porta);
    delete(porta);
    clear porta;
end

fopen(porta);
count=1;
%graph = plot(0,0,'r*') 
axis([0 20 0 200])

hold on;
temp=33;

while(ishandle(1))%graph))
    temp0=temp;
    aux=clock;
    temp = fscanf(porta,'%c')
    temp = bin2dec(temp(1:8))-32;
    
  %  set(graph,'XData',count,'YData',temp)
        hold on
        subplot(4,1,1);
        plot([count-1 count],[temp0 temp]);
        axis([count-50 count -30 60])
        hold on
        subplot(4,1,2);
        plot([count-1 count],polyval(pol2,[temp0 temp]))
        axis([count-50 count -30 60])
        hold on
        subplot(4,1,3);
        plot([count-1 count],polyval(pol3,[temp0 temp]))
        axis([count-50 count -30 60])
        hold on
        subplot(4,1,4);
        if(temp0 >32 &&temp >32 && temp0 <107 && temp < 107)
            plot([count-1 count], [a(temp0-32,1) a(temp-32,1)] )
        end
        axis([count-50 count -30 60])
%     hist(count,1:5) = clock;
%     hist(count, 6) = temp;
    count = count+1;
    pause(.01)
end



fclose(porta);
delete(porta);
clear porta;


