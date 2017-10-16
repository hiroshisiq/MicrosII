
#include <SoftwareSerial.h>

//cabo         arduino
//0 clk      - 4
//1 dir      - 5
//7 /enable  - 11

int clockPin    = 4;
int clockState  = LOW;
int inibPin     = 11;
int inibState   = LOW;
int dirPin      = 5;
int dirState    = LOW;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial);
    
  Serial.println("Goodnight moon!");
  
  pinMode(clockPin, OUTPUT);
  pinMode(inibPin,  OUTPUT);
  pinMode(dirPin,   OUTPUT);
  
  digitalWrite(inibPin, inibState);
  digitalWrite(dirPin, dirState);
  
}

void loop() { // run over and over
  
    if (Serial.available()) {
      char command = Serial.read();

      switch (command) {
        case 'r':
          dirState = HIGH;
          Serial.write("to right!\n");
          break;
        case 'l':
          dirState = LOW;
          Serial.write("to left!\n");
          break;
        default:
          Serial.write("404!\n");        
      }

      digitalWrite(dirPin, dirState);
    }

    if (clockState == LOW) {
      clockState = HIGH;
    } else {
      clockState = LOW;
    }

    digitalWrite(clockPin, clockState);
    delay(1000);
}

