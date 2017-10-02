#include <at89x52.h>
#include <stdio.h>
#include <string.h>
#include "lcd.h"

#define low50ms 0xFF
#define high50ms 0x4B

// P3.0 P3.1 P3.2 P3.3 P3.4 P3.5 P3.6 P3.7
// D0   D1   D2   D3   D4   D5   D6   D7

int t0 =   0;
int timerCount =  20;
int timerCount0 = 20;
int waveCounter = 0;

void configure_timers(){
    // Timer 1 as counter, Pin 3.5, Mode 1
    // Timer 0 as timer , Mode 1, 50 ms

    TMOD = 0x51;
    TH0 = high50ms;
    TL0 = low50ms;
    EA = 1;
    ET1 = 1;
    ET0 = 1;
}

void clear_counter() {
    TH1 = 0;
    TL1 = 0;
    waveCounter = 0;
}

void getFrequency(){

    int frequency;
    char buf[12];
    char scale[7];

    if(TL1 < 2 && TH1 == 0 && waveCounter == 0) {
    	timerCount0 = 100; // increment 1 second 
	clearLCD();
    	delay(20);
    	write("Changing to mHz");
    	clear_counter();
    	return;
    } else if(timerCount0 == 100 && TL1 > 16) {
	clearLCD();
    	delay(20);	
    	write("Changing to Hz");
    	timerCount0 = 20;
    	clear_counter();
    	return;
    }


    
    frequency =  TL1;
    frequency += 256*TH1;
    frequency += 65536*waveCounter;

    

    

    if(timerCount0 == 100) {
    	frequency = frequency*(1000/5);
	strcpy (scale," mHz");
    	

    } else {

	strcpy (scale," Hz");
    }

    clear_counter();
    sprintf(buf,"%u",frequency);
    strcat(buf, scale);
    delay(20);
    clearLCD();
    delay(20);
    write(buf);
}

void timer0() __interrupt(1){
    // Timer
    timerCount--;

    TH0 = high50ms;
    TL0 = low50ms;

    if(timerCount == 0){
        TR0 = 0;
        TR1 = 0;

        getFrequency();
        configure_timers();

        timerCount = timerCount0;
        TR0 = 1;
        TR1 = 1;
    }

}

void timer1() __interrupt(3){
    // Counter
    waveCounter++;
}

int main () {
    configure8bits();
    clearLCD();
    configure_timers();

    TR0 = 1;
    TR1 = 1;

    while(1);	// end
}
