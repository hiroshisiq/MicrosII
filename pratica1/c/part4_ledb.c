#include <at89x52.h> 

// Dalay function
void delay(int mstime) {
	unsigned int i, j;
	for(i=0; i<mstime; i++)
		for(j=0; j<1275; j++);
}

int main() {
	while(1) {
		P0 = P1;
		while(P0 != 0xFE) {
			P0 = P0 >> 1;
			delay(500);
		}
	}
}