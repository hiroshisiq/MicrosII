#include <at89x52.h>

// P0.0 P0.1 P0.2 P0.3 P0.4 P0.5 P0.6 P0.7
// RS   RW   EN   -    D4   D5   D6   D7   

unsigned char text[16] = "hacked 4bits";

// Dalay function
void delay(int mstime) {
//	int i;
//	for(i = 0; i < mstime*5; i++) {
//		TMOD = 0x01;
//		TR0  = 0;
//		TH0  = 245;
//		TL0  = 0x67;
//		TR0  = 1;
//		while(TF0 != 1);
//	}
	
 	unsigned int i, j;
 	for(i=0; i<mstime; i++)
 		for(j=0; j<1275; j++);
}

void pulse() {
	// Enable pulse 
	P0_2 = 1;	
	P0_2 = 0;
	// Wait LCD
	delay(3);
}

void send(char data) {
	// Load most significant nibble
	P0 = (P0 & 0x0F) | (data & 0xF0);
	pulse();

	// Load less significant nibble
	P0 = (P0 & 0x0F) | ((data << 4) & 0xF0);
	pulse();
}

void to2line() {
	P0 = 0x00;
	send(0xC0);
}

void configure() {
	P0 = 0x00;
	delay(20);
	send(0x28); // set 4-bits
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

int main () {
	configure();
	write("hacked 4bits");
	to2line();
	write("second line");
	while(1);	// end
}