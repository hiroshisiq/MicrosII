#include <at89x52.h>

int main() {
	SCON = 0x50; 		// Serial mode 1 + Receiver Enable
	TMOD = 0x20; 		// Timer Mode 2 (auto reload)
	TH1  = 253;  		// Baud Rate 9600
	TR1  = 1;    		// Start Timer

	while(1) {   		// Read/Write loop
		while(RI==0);	// Wait here for char to be received
		RI = 0;			// Reset flag
		SBUF =  SBUF;	// Prepare char to be sent
		while(TI == 0);	// Wait here for char to be sent
		TI = 0; 		// Reset flag
	}
}
