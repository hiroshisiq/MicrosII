#include <at89x52.h>

// P0.0 P0.1 P0.2 P0.3 P0.4 P0.5 P0.6 P0.7
// RS   RW   EN   -    D4   D5   D6   D7   

// P2.0 P2.1 P2.2 P2.3 P2.4 P2.5 P2.6 P2.7
// D0   D1   D2   D3   -    -    -    -   

// Dalay function
void delay(int mstime) {
	unsigned int i, j;
	for(i=0; i<mstime; i++)
		for(j=0; j<1275; j++);
}

void clearLCD(){
    // clear
    send(0x01);
}

void send(char data) {
	// Load most significant nibble
	P0 = (P0 & 0x0F) | (data & 0xF0);
	// Load less significant nibble
	P2 = data;
	// Enable pulse 
	P0_2 = 1;	
	P0_2 = 0;
	// Wait LCD
	delay(2);
}

void configure8bits() {
	P0 = 0x00;
	delay(20);
	send(0x0E); // display on
	send(0x06); // write to >>
	send(0x01); // clear
}

void write(char *txt) {
	P0_0 = 0x01; // RS = 1;
	while(*txt != '\0') {
		send(*txt);
		txt++;
	}
} 
