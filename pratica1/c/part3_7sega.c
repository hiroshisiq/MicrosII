#include <at89x52.h> 

// Dalay function
void delay(int mstime) {
	unsigned int i, j;
	for(i=0; i<mstime; i++)
		for(j=0; j<1275; j++);
}

int main() {
	// Conversion table
	int intTo7seg[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 
					 0x92, 0x83, 0xF8, 0x80, 0x98};
	// Table of numbers
	int numbers[4] = {1, 9, 9, 7}; 

	int i, shifter = 0xEE << 1;

	while(1) {
		for(i=0; i<4; i++) {
			P0 = intTo7seg[numbers[i]];
			P2 = shifter >> 1;
			delay(50);
		}
	}
} 

