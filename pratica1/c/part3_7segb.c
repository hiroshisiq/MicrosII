#include <at89x52.h> 

int counter = 0;
int numbers[4] = {1, 9, 9, 7}; // Table of numbers	
// Conversion table
int intTo7seg[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 
					 0x92, 0x83, 0xF8, 0x80, 0x98};

void serialInt () __interrupt(4) {
	EA = 0;				// Desable interruption
	
	if(RI = 1) {		// If received char  
		RI   = 0;		// Reset flag
		
		if(SBUF >= '0' || SBUF <= '9') {
			numbers[counter++] = (int) SBUF - '0';
		}
	}

	EA = 1;				// Enable interruption
}

// Dalay function
void delay(int mstime) {
	unsigned int i, j;
	for(i=0; i<mstime; i++)
		for(j=0; j<1275; j++);
}

void configure() {
	SCON = 0x50; 		// Serial mode 1 + Receiver Enable
	TMOD = 0x20; 		// Timer Mode 2 (auto reload)
	TH1  = 253;  		// Baud Rate 9600
	EA   = 1;			// Enable interruption
	ES   = 1;			// Enable serial interruption
	TR1  = 1;    		// Start Timer
}

int main() {
	int i, shifter = 0xEE << 1;
	configure();
	
	while(1) {
		for(i=0; i<4; i++) {
			P0 = intTo7seg[numbers[i]];
			P2 = shifter >> 1;
			delay(50);
		}
	}
} 