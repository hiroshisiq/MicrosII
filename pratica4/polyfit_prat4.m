%% Data get and pre settings
data = a;
aux = num2str(data(:,4));
data(:,4) = bin2dec(aux);

codes = data(:,4);
temps = data(:,1);

tam  = size(temps);tam=tam(1);
cod0 = codes(1);
codf = codes(tam(1));

%% Lookup table linear approximations
for i=1:size(codes)
    
    if(i > 1)
        delta =  codes(i) - codes(i-1);
    end
    
    if(i<2 || delta < 2)
        table(codes(i)-(cod0-1)) = temps(i);
    elseif(delta >= 2)
        step = 1/delta;
        for j=1:delta
            table(codes(i-1)-(cod0-1)+j) = temps(i)+(delta -j)*step;   
        end
    end
    
end
codes = [0:1:139];
temps = table;

%% Polyfit
pol1 = polyfit(codes,temps,1);
pol2 = polyfit(codes,temps,2);
pol3 = polyfit(codes,temps,3);
pol4 = polyfit(codes,temps,4);
pol5 = polyfit(codes,temps,5);
pol20 = polyfit(codes,temps,20);

x = codes; %[30:0.5:180];
y1 = polyval(pol1, x);
y2 = polyval(pol2, x);
y3 = polyval(pol3, x);
y4 = polyval(pol4, x);
y5 = polyval(pol5, x);
y20 = polyval(pol20, x);

figure; hold on;

%%Plotting
plot(codes,temps,'r*');

plot(x,y1);
plot(x,y2);
plot(x,y3);
plot(x,y4);
plot(x,y5);
plot(x,y20)
legend('Dados experimentais','Ordem 1','Ordem 2','Ordem 3','Ordem 4','Ordem 5', 'Ordem 20','location','best');
ylim([-20 60]);

m1 = mean(y1- temps);
m2 = mean(y2- temps);
m3 = mean(y3- temps);
m4 = mean(y4- temps);
m5 = mean(y5- temps);

dp1 = sqrt(sum((y1-temps).^2)/tam);
dp2 = sqrt(sum((y2-temps).^2)/tam);
dp3 = sqrt(sum((y3-temps).^2)/tam);
dp4 = sqrt(sum((y4-temps).^2)/tam);
dp5 = sqrt(sum((y5-temps).^2)/tam);
dp20 = sqrt(sum((y20-temps).^2)/tam);



% To read: tables(i - (cod0-1))