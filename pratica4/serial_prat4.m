
porta = serial('COM3', 'Baudrate', 9600);
if (isvalid(porta)==0)
    exit;
end

fopen(porta);
c0unt=1;
figure; hold on;

while(count<1000)
    temp = fscanf(porta,'%c%c%c%c%c%c%c%c'); 
    temp = bin2dec(temp);
    plot(count,temp);
    hist(count) = [clock temp];
    count = count+1;
end

fclose(porta);
delete(porta);
clear porta;



