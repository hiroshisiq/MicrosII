%% Parameters
t=[253:1:333]; %Temperatura range

%(R,T) points : (2.23k,323), (7.25k,293), (28.4k,323)

X=[1 log(2.23*1000) log(2.23*1000)^3   ;1 log(7.25*1000) log(7.25*1000)^3   ;1 log(28.4*1000) log(28.4*1000)^3   ];
Y=[1/323;1/293;1/263];

p=X^-1*Y;   %A,B and C parameters
x=[];
y=[];
R=[];
tam=size(t);tam=tam(2);

%% Steinhart equation
%x parameter
for i=1:tam
x(i)=(1/p(3))*(p(1)-1/t(i));
end
%y parameter
for i=1:tam
y(i)=sqrt((p(2)/(3*p(3)))^3 + (x(i)/2)^2);
end
% Resistance
for i=1:tam
R(i)=exp((y(i)-x(i)/2)^(1/3)-(y(i)+x(i)/2)^(1/3));
end

%%Plots
plot(R,t-273)
grid on
xlabel('Resistência [\Omega]')
ylabel('Temperatura [°C]')
title('Equação de Steinhart-Hart e Valores experimentais')
hold on
plot(data(:,2)*1000,data(:,1),'ro')
legend('Equação de Steinhart-Hart','Dados experimentais','location','best');