#include <at89x52.h>

// P0.0 P0.1 P0.2 P0.3 P0.4 P0.5 P0.6 P0.7
// RS   RW   EN   -    D4   D5   D6   D7

// P2.0 P2.1 P2.2 P2.3 P2.4 P2.5 P2.6 P2.7
// D0   D1   D2   D3   -    -    -    -

int RS = 14;
int RW = 15;
int EN = 16;
int D4 = 17;
int D5 = 18;
int D6 = 19;
int D7 = 12;

int PO[] = {RS, RW, RN, -1, D4, D5, D6, D7};

// Delay function
void delay(int mstime) {
	unsigned int i, j;
	for(i=0; i<mstime; i++)
		for(j=0; j<1275; j++);
}

void pulse(){

	digitalWrite(EN,HIGH);
	digitalWrite(EN, LOW);

}

void digitalWriteVector(int* port, int num,int init, int fin){
	int i;

	while(num < 127){
		num *= 2;
	}

	for(i=7;i>=0;i--){
		if( port[i] > 0  && i <= init && i  >= fin){
			if(num%2 == 0){
				digitalWrite(port[i], LOW);
			}else{
				digitalWrite(port[i], HIGH);
			}
		}
		num/=2;
	}

}

void send(char data) {

	// int *aux1;
	// int *aux2;
	// aux1 = (int*) calloc(8,sizeof(int));
	// aux2 = (int*) calloc(8,sizeof(int));
	// Load most significant nibble
	//P0 = (P0 & 0x0F) | (data & 0xF0);
	digitalWriteVector(P0, (int) data & 0xF0,7,4 )
	pulse();

	// Load less significant nibble
	//P0 = (P0 & 0x0F) | ((data << 4) & 0xF0);
	digitalWriteVector(P0, ((int) data<<4) & 0xF0 , 7,4)
	pulse();

	delay(2);
}

void configure4bits() {
	digitalWriteVector(P0 , 0x00,)
	delay(20);
	send(0x28); // set 4-bits
	send(0x0E); // display on
	send(0x06); // write to >>
	send(0x01); // clear
}

void clearLCD() {
	digitalWrite(RS, LOW);
	send(0x01);
	digitalWrite(RS, HIGH);
}

void to2line() {
	digitalWriteVector(P0,0x00,7,0)
	send(0xC0);
}

void write(char *txt) {
	//P0_0 = 0x01; // RS = 1;
	digitalWrite(RS, HIGH);
	while(*txt != '\0') {
		send(*txt);
		txt++;
	}
}
