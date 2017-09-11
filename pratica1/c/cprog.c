#include <at89x52.h>

// P0.0 P0.1 P0.2 P0.3 P0.4 P0.5 P0.6 P0.7
// RS   RW   EN   -    D4   D5   D6   D7   

// P2.0 P2.1 P2.2 P2.3 P2.4 P2.5 P2.6 P2.7
// D0   D1   D2   D3   -    -    -    -   

// Dalay function

int counter = 0;
char buffer[16];

void delay(int mstime) {
	unsigned int i, j;
	for(i=0; i<mstime; i++)
		for(j=0; j<1275; j++);
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

void configure() {
	P0 = 0x00;
	send(0x0E); // display on
	send(0x06); // write to >>
	send(0x01); // clear
}

void configure_serial(){

	SCON = 0x50; 		// Serial mode 1 + Receiver Enable
	TMOD = 0x20; 		// Timer Mode 2 (auto reload)
	TH1  = 253;  		// Baud Rate 9600
	TR1  = 1;    		// Start Timer

}

void serialInt () __interrupt(4) {
	EA = 0 ;			// Desable interruption
	
	if(RI == 1) {		// If received char  
		RI   = 0;		// Reset flag
		buffer[counter] = SBUF;	// Prepare char to be sent
		counter++;
		buffer[counter] = '\0';
	}

	TI = 0;				// Reset flag
	EA = 1;				// Enable interruption
}

void write(char *txt) {
	P0_0 = 0x01; // RS = 1;
	while(*txt != '\0') {
		send(*txt);
		txt++;
	}
}

// ------------------------------------------------------

// int main() {

// 	while(1) {   		// Sending loop
// 		SBUF =  'A';	// Prepare char to be sent
// 		while(TI == 0);	// Wait here for char to be sent
// 		TI = 0; 	// Reset flag
// 	}
// }

// -----------------------------------------------------

int main () {
	configure();
	configure_serial();
	while(counter<16 && buffer[counter-1]!= '=' ); // = is the 'enter'
	write(buffer);
	while(1);	// end
}
