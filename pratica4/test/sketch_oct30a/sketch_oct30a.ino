#include <SoftwareSerial.h>

const int buttonPin[8] = {6, 7, 4, 5, 8, 9, 10, 11}; // Ordem errada

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial);

  // Set pin mode
  for(int i=0; i<8; i++) {
    pinMode(buttonPin[i], INPUT);
  }
}

int bin2dec(int * binNumber){

  int i,dec=0;

  for(i=0; i<8; i++) {
    if(binNumber[i] == HIGH) {
      dec += pow(2,i);
    }
  }


}


void tempLookUp(int code){

  int table[255] = {   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,  
//                   -17 -16 -15 -14 -13 -12 -11 -10  -9  -8  -7  -6  -5  -4  -3  -2  -1   0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  
                       ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,                
//                    20  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36  37  38  39  40  41  42  43  44  45  46  47  48  49  50  51  52  53  54  55
  }

  return table[code];
  
}

void loop() {
  int buttonState[8];

  // Read A/D
  for(int i=0; i<8; i++) {
    buttonState[i] = digitalRead(buttonPin[i]);
  }

  // Convert to decimal
  int dec = 0;
  for(int i=0; i<8; i++) {
    if(buttonState[i] == HIGH) {
      dec += pow(2,i);
    }
  }

  // Print
  for(int i=0; i<8; i++) {
    Serial.print(buttonState[i], "%d");
  }
  Serial.print("\n");
  delay(1000);
}


