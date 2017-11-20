
porta = serial('COM24', 'Baudrate', 9600);
if (isvalid(porta)==0)
    a=2
    
    fclose(porta);
    delete(porta);
    clear porta;
end

fopen(porta);
count=1;
graph = plot(0,0,'r*') 
axis([0 20 0 200])

hold on;
temp=0;

while(ishandle(graph))
    temp0=temp;
    aux=clock;
    temp = fscanf(porta,'%c')
    temp = bin2dec(temp(1:8));
    
  %  set(graph,'XData',count,'YData',temp)
    hold on
        plot([count-1 count],[temp0 temp]);
    axis([0 count 0 200])
%     hist(count,1:5) = clock;
%     hist(count, 6) = temp;
    count = count+1;
    pause(.01)
end

fclose(porta);
delete(porta);
clear porta;


