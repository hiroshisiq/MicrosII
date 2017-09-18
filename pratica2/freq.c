#include <at89x52.h>
#include "serial.h"

// P3.0 P3.1 P3.2 P3.3 P3.4 P3.5 P3.6 P3.7
// D0   D1   D2   D3   D4   D5   D6   D7   

int t0 =   0;
int timerCount =    20;
int waveCounter = 0;

void configure_timers(){
    // Timer 1 as counter, Pin 3.5, Mode 1
    // Timer 0 as timer , Mode 1, 50 ms
    
    TMOD = 0x51;
    TH0 = 0x4B;
    TL0 = 0xFF;
    EA = 1;
    ET1 = 1;
    ET0 = 1;
}

void timer0() __interrupt(1){
    // Timer
    timerCount--;
    if(timerCount == 0){
        TR0 = 0;
        TR1 = 0;

        getFrequency();
        configure_timers();
        
        timerCount = 20;
        TR0 = 1;
        TR1 = 1;
    }
}




void getFrequency(){

    int frequency;
    char buf[12];    

    frequency =  65536*waveCounter + 256*TH1 + TL1;
    
    sprintf(buf,'%d',frequency);  
    strcat(buf, ' Hz');
    
    clear();
    write(buf);    
}

void timer1() __interrupt(3){
    // Counter
    waveCounter++;
}

int main () {
	configure8bits();
    configure_timers();
    






	while(1);	// end
}
