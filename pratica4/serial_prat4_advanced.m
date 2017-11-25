%% Serial opening
porta = serial('COM3', 'Baudrate', 9600);
if (isvalid(porta)==0)
    
    fclose(porta);
    delete(porta);
    clear porta;
end

fopen(porta);

%% Graph pre setting
%graph = plot(0,0,'r*') 
graph = figure;
graph.Position = [100 100 800 600];
axis([0 20 0 200])
g=10;
hold on;
temp=33;
tableData = [33 33];
b=[0 0 0 0 0];
xm = 10;
ym =10;

%% UI settings
     a = graph.Position;
     tamx =80;
     tamy =40;
     tam = [tamx tamy];
     tamsld = [a(3)/2 20];

     order1 = uicontrol('Style', 'togglebutton', 'String', 'Order 1',...
         'Position', [[a(3:4) - [5*tamx tamy]] tam],         'Min',0,'Max',1,'Value',0         );
     order2 = uicontrol('Style', 'togglebutton', 'String', 'Order 2',...
         'Position', [[a(3:4) - [4*tamx tamy]] tam],         'Min',0,'Max',1,'Value',0         );
     order3 = uicontrol('Style', 'togglebutton', 'String', 'Order 3',...
         'Position', [[a(3:4) - [3*tamx tamy]] tam],         'Min',0,'Max',1,'Value',0         ); 
     order4 = uicontrol('Style', 'togglebutton', 'String', 'Order 4',...
         'Position', [[a(3:4) - [2*tamx tamy]] tam],         'Min',0,'Max',1,'Value',0         ); 
     order5 = uicontrol('Style', 'togglebutton', 'String', 'Order 5',...
         'Position', [[a(3:4) - [tamx tamy]] tam],...
         'Min',0,'Max',1,'Value',0         ); 
     sldx = uicontrol('Style', 'slider',...
        'Min',1,'Max',300,'Value',25,...
        'Position', [a(3:4)-[tamsld(1) 2*tamy] tamsld]        ); 
     sldy = uicontrol('Style', 'slider',...
        'Min',1,'Max',80,'Value',25,...
        'Position', [a(3:4)-[tamsld(1) 2*tamy+tamsld(2)] tamsld]        ); 

%      txty = uicontrol('Style','text',...
%         'Position',[a(3:4)-[tamsld(1) 3*tamy] tamsld],...
%         'String','Limites eixo y');
%      txtx = uicontrol('Style','text',...
%         'Position',[a(3:4)-[tamsld(1) 3*tamy+tamsld(2)] tamsld],...
%         'String','Limites eixo x');

graphNumber = 1;

%% Plotting
    count =1;
    graphNumber = 1;
    pol=[zeros(1,4) pol1;zeros(1,3) pol2; zeros(1,2) pol3; zeros(1,1) pol4; pol5 ];

while(ishandle(1))%graph))
    temp0=temp;

    temp = fscanf(porta,'%c');
    temp = bin2dec(temp(1:8))-32;
    

    if(temp > 1 && temp< 140)
        tableData = [temps(temp0) temps(temp)];
    end
%%Polynoms plotting
     
    n=2;
    i=1;
 
    while(i<=5)
        
        tic
        if(b(i))
            y=polyval(pol(i,:),[temp0 temp]);
            subplot(graphNumber+1,2,n+1);
            plot([count-1 count]*0.2,y,'b-')
            axis([count*0.2-xm count*0.2 y(2)-ym y(2)+ym])
            title(['Polinômio de ordem ', num2str(i)])
            hold on; grid on;
            subplot(graphNumber+1,2,n+2);
            plot([count-1 count]*0.2,tableData - y,'b-')
            axis([count*0.2-xm count*0.2 -3 3])
            title(['Erro de ordem ', num2str(i)])
            hold on;grid on;
            n=n+2;
        end
       [i,toc]
        i=i+1;
        
    end    
        

    %% Table lookup 
        y=tableData;
        subplot(graphNumber+1,2,1);
        
        if(temp >0 && temp < 141)
            plot([count-1 count]*0.2, y,'b-' )
        end
        
        axis([count*0.2-xm count*0.2 y(2)-ym y(2)+ym])
        title('Valor real')
        hold on;grid on;
%% Graph pos settings
    count = count+1
    
    if(~isvalid(order1))
        %% End if graph is closed
        fclose(porta);
        delete(porta);
        clear porta;
        finish;
        
    end
        b(1)=get(order1,'Value');b(2)=get(order2,'Value');b(3)=get(order3,'Value');b(4)=get(order4,'Value');b(5)=get(order5,'Value');
        xm = get(sldx,'Value');
        ym = get(sldy,'Value');

    i=1;
    graphNumber = 0;
    while(i<=5)
        if(b(i))
            graphNumber= graphNumber+1;
        end
    i=i+1;    
    end
    
    pause(.01)
    
end

%% Serial closing
fclose(porta);
delete(porta);
clear porta;


    

