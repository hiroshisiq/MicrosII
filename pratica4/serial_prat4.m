%% Serial opening
porta = serial('COM3', 'Baudrate', 9600);
if (isvalid(porta)==0)
    
    fclose(porta);
    delete(porta);
    clear porta;
end

fopen(porta);

%% Graph pre setting
count=1;
%graph = plot(0,0,'r*') 
axis([0 20 0 200])
g=10;
hold on;
temp=33;
tableData = [33 33];

%     btn = uicontrol('Style', 'pushbutton', 'String', 'Clear',...
%         'Position', [20 20 50 20],...
%         'Callback', @gridbutton);  

%% Plotting

while(ishandle(1))%graph))
    temp0=temp;
    aux=clock;
    temp = fscanf(porta,'%c');
    temp = temp(1:8);
    temp = bin2dec(temp(1:8))-32;
    
  %  set(graph,'XData',count,'YData',temp)
        hold on
%         subplot(4,2,1);
%         plot([count-1 count],[temp0 temp],'b-');
%         axis([count-50 count 0 255])
%         hold on
        if(temp0 > 0 && temp0< 141 && temp > 0 && temp< 141)
            tableData = [temps(temp0) temps(temp)];
        end
%%Polynoms plotting
    %% Order 2
        y=polyval(pol2,[temp0 temp]);
        subplot(4,2,3);
        plot([count-1 count]*0.2,y,'b-')
        axis([count*0.2-10 count*0.2 -30 60])
        title('Polinômio de ordem 2')
        hold on
        subplot(4,2,4);
        plot([count-1 count]*0.2,tableData - y,'b-')
        axis([count*0.2-10 count*0.2 -2 2])
        title('Erro para ordem 2')
        hold on
    %% Order 3        
        y=polyval(pol3,[temp0 temp]);
        subplot(4,2,5);
        plot([count-1 count]*0.2,y,'b-')
        axis([count*0.2-10 count*0.2 -30 60])
        title('Polinômio de ordem 3')
        hold on
        subplot(4,2,6);
        plot([count-1 count]*0.2,tableData - y ,'b-')
        axis([count*0.2-10 count*0.2 -2 2])
        title('Erro para ordem 3')
        hold on
    %% Order 4 
        y=polyval(pol4,[temp0 temp]);
        subplot(4,2,7);
        plot([count-1 count]*0.2,y,'b-')
        axis([count*0.2-10 count*0.2 -30 60])
        title('Polinômio de ordem 4')
        hold on
        subplot(4,2,8);
        plot([count-1 count]*0.2, tableData - y,'b-')
        axis([count*0.2-10 count*0.2 -2 2])
        title('Erro para ordem 4')
        hold on
    %% Table lookup 
        y=tableData;
        subplot(4,2,1);
        if(temp0 >0 && temp >0 && temp0 <141 && temp < 141)
            plot([count-1 count]*0.2, y,'b-' )
        end
        axis([count*0.2-10 count*0.2 y(2)-g y(2)+g])
        title('Valor real')
        hold on
%     hist(count,1:5) = clock;
%     hist(count, 6) = temp;
    count = count+1;
    pause(.01)
end

%% Serial closing
fclose(porta);
delete(porta);
clear porta;


    

