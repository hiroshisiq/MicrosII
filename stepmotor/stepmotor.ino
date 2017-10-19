#include <SoftwareSerial.h>

#define defaultPeriod 3

//cabo         arduino
//0 clk      - 4
//1 dir      - 5
//7 /enable  - 11

int clockPin = 4;  int clockState = LOW;
int inibPin  = 11; int inibState  = LOW;
int dirPin   = 5;  int dirState   = LOW;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial);

  // First print on serial
  Serial.write("Welcome to step motor arduino controller!\n");

  // Set pin mode
  pinMode(clockPin, OUTPUT);
  pinMode(inibPin,  OUTPUT);
  pinMode(dirPin,   OUTPUT);

  // Configure
  digitalWrite(inibPin, inibState); // Set inibe to false
  digitalWrite(dirPin, dirState);   // Set direction to left
}

void printMainMenu() {
  Serial.write("Options:\n");
  Serial.write("1. One step right.\n");
  Serial.write("2. Half turn right.\n");
  Serial.write("3. One turn right.\n");
  Serial.write("4. Five turns right.\n");
  Serial.write("5. One step left.\n");
  Serial.write("6. Half turn left.\n");
  Serial.write("7. One turn left.\n");
  Serial.write("8. Five turns left.\n");
  Serial.write("9. More options.\n");
}

void evaluateMainMenu() {
  // Wait for command
  while(!Serial.available());
  
  char command = Serial.read();

  switch (command) {
    case '1':
      Serial.write("\nTurning one step to right\n\n");
      turn(1, defaultPeriod, HIGH);
      break;
    case '2':
      Serial.write("\nTurning half turn to right\n\n");
      turn(200, defaultPeriod, HIGH);
      break;
    case '3':
      Serial.write("\nTurning one turn to right\n\n");
      turn(400, defaultPeriod, HIGH);
      break;
    case '4':
      Serial.write("\nTurning five turns to right\n\n");
      turn(2000, defaultPeriod, HIGH);
      break;
    case '5':
      Serial.write("\nTurning one step to left\n\n");
      turn(1, defaultPeriod, LOW);
      break;
    case '6':
      Serial.write("\nTurning half turn to left\n\n");
      turn(200, defaultPeriod, LOW);
      break;
    case '7':
      Serial.write("\nTurning one turn to left\n\n");
      turn(400, defaultPeriod, LOW);
      break;
    case '8':
      Serial.write("\nTurning five turns to left\n\n");
      turn(2000, defaultPeriod, LOW);
      break;
    case '9':
      break;
    default:
      Serial.write("404!\n");        
    } 
}

void mainMenu() {
  printMainMenu();
  
  do {
    evaluateMainMenu();
  } while (Serial.available()); 
}

void changeClockState() {
    // Inverte clock state
    if (clockState == LOW) {
      clockState = HIGH;
    } else {
      clockState = LOW;
    }

    // Write to clock pin
    digitalWrite(clockPin, clockState);
}

void turn(int numOfSteps, float period, int dir) {
  // Set direction
  digitalWrite(dirPin, dir);

  // Do the steps
  int i;
  for(i = 0; i < numOfSteps; i++) {
    changeClockState();
    delay(period);
  }  
}

void loop() { // run over and over
    mainMenu();
}

