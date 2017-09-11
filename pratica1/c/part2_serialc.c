#include <at89x52.h>

int counter = 0;
char text0[] = "KKJ EAE MAN\n\r";
char text1[] = "Happy lil tree\n\r";
char text2[] = "Gezz Rick\n\r";
char text3[] = "Big Bad Voodoo Dad\n\r";
char text4[] = "Default\n\r";

void serialInt () __interrupt(4) {
	EA = 0 ;			// Desable interruption
	
	if(RI = 1) {		// If received char  
		RI   = 0;		// Reset flag
		sendText();		// Prepare char to be sent
	}

	counter = 0;		// Reset counter
	TI = 0;				// Reset flag
	EA = 1;				// Enable interruption
}

void sendText() {
	char *text = text4;			// Default

	// Select text based on keyboard input
	if(SBUF == 'a') text = text0;
	if(SBUF == 's') text = text1;
	if(SBUF == 'd') text = text2;
	if(SBUF == 'f') text = text3;

	do {						// Do while reach end of string
		SBUF =  text[counter];	// Prepare char to be sent
		while(TI == 0);			// Wait here for char to be sent
		TI = 0;					// Reset flag
	} while(text[++counter] != '\0'); 		
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
	configure();		// Configure 
	while(1);			// Wait here
}