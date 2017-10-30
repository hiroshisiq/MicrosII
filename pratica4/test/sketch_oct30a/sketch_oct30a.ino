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


