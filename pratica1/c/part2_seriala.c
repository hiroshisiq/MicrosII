#include <at89x52.h>

void serialInt () __interrupt(4) {
	EA = 0 ;			// Desable interruption
	
	if(RI = 1) {		// If received char  
		RI   = 0;		// Reset flag
		SBUF = SBUF;	// Prepare char to be sent
	}

	TI = 0;				// Reset flag
	EA = 1;				// Enable interruption
}

int main() {
	SCON = 0x50; 		// Serial mode 1 + Receiver Enable
	TMOD = 0x20; 		// Timer Mode 2 (auto reload)
	TH1  = 253;  		// Baud Rate 9600
	EA = 1;				// Enable interruption
	ES = 1;				// Enable serial interruption
	TR1  = 1;    		// Start Timer

	while(1);			// Wait here
}
