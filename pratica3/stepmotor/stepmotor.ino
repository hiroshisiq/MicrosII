#include <SoftwareSerial.h>

/*|      | cabo  | arduino |
  | clk  |  0    |    4    |
  | dir  |  1    |    5    |
  | inib |  7    |   11    |
*/

// Constants
#define defaultPeriod 3000 // us
#define fullTurnSteps 200  // steps

// Pins
#define clockPin 4 
#define inibPin 11 
#define dirPin 5 

// States
int clockState = LOW;
int inibState  = LOW;
int dirState   = LOW;

// Command recorder (up to 10 commands)
char commandList[11] = "3636363636";

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

void changeClockState() {
    // Write to clock pin
    digitalWrite(clockPin, HIGH);
    digitalWrite(clockPin, LOW);
}

void changeDirectionState() {
    // Inverte direction state
    if (dirState == LOW) {
      dirState = HIGH;
    } else {
      dirState = LOW;
    }

    // Write to direction pin
    digitalWrite(dirPin, dirState);
}

void turn(int numOfSteps, float period, int dir) {
  // Set direction
  digitalWrite(dirPin, dir);

  // Do the steps
  int i;
  for(i = 0; i < numOfSteps; i++) {
    changeClockState();
    delayMicroseconds(period);
  }  
}

void pullTorque(boolean pullIn, int t0 = defaultPeriod, int t1 = 1000, int delta = 100) { 
  float period;

  // Test periods between 3000 and 1000 us
  for(period = t0; period >= t1; period-=delta) {
    // Print the period on serial 
    Serial.println(period);
    
    // Do a full turn with the new period
    turn(2*fullTurnSteps, period, dirState);
    
    // if pull out test, change direction
    if(pullIn) changeDirectionState();    
  }  
}

void recordCommands() {  
  int i;
  char command;
  for(i=0; i<10; i++) {
    // Wait for char
    while(!Serial.available());

    // Read char
    command = Serial.read();

    // If it's valid command, save on comandList
    if(command >= '1' && command <= '8') {
      commandList[i] = command;
    // If command is r, stop recording
    } else if (command == 'r') {
      commandList[i] = '\0';
      break;
    }     
  }

  // Clear serial buffer
  while(Serial.available()) command = Serial.read();
}

void runCommandList() {
  int i = 0;
  while(commandList[i] != '\0') {
    evaluate(false, commandList[i++]);
  }
}

void printCommandList() { 
  int i = 0;
  while(commandList[i] != '\0') {
    Serial.print(i);
    
    switch (commandList[i++]) {
      case '1': Serial.write(". One step right.\n");
        break;
      case '2': Serial.write(". Half turn right.\n");
        break;
      case '3': Serial.write(". One turn right.\n");
        break;
      case '4': Serial.write(". Five turns right.\n");
        break;
      case '5': Serial.write(". One step left.\n");
        break;
      case '6': Serial.write(". Half turn left.\n"); 
        break;
      case '7': Serial.write(". One turn left.\n");
        break;
      case '8': Serial.write(". Five turns left.\n");
        break;
    }
  }

  Serial.write("\n");
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
  Serial.write("q. Pull-in test.\n");
  Serial.write("w. Pull-out test.\n");
  Serial.write("e. Play commands.\n");
  Serial.write("r. Record commands.\n");  
}

void evaluate(bool evalMenu, char com) {
  char command;
  
  if(evalMenu == true) {
    // Wait for command
    while(!Serial.available());
    command = Serial.read();
  } else {
    command = com;
  }
  
  switch (command) {
    case '1':
      Serial.write("Turning one step to right\n\n");
      turn(1, defaultPeriod, HIGH);
      break;
    case '2':
      Serial.write("Turning half turn to right\n\n");
      turn(fullTurnSteps/2, defaultPeriod, HIGH);
      break;
    case '3':
      Serial.write("Turning one turn to right\n\n");
      turn(fullTurnSteps, defaultPeriod, HIGH);
      break;
    case '4':
      Serial.write("Turning five turns to right\n\n");
      turn(5*fullTurnSteps, defaultPeriod, HIGH);
      break;
    case '5':
      Serial.write("Turning one step to left\n\n");
      turn(1, defaultPeriod, LOW);
      break;
    case '6':
      Serial.write("Turning half turn to left\n\n");
      turn(fullTurnSteps/2, defaultPeriod, LOW);
      break;
    case '7':
      Serial.write("Turning one turn to left\n\n");
      turn(fullTurnSteps, defaultPeriod, LOW);
      break;
    case '8':
      Serial.write("Turning five turns to left\n\n");
      turn(5*fullTurnSteps, defaultPeriod, LOW);
      break;
    case 'q':
      Serial.write("\nStarting pull-in test...\n\n");
      pullTorque(true, 1500, 800, 50);
      Serial.write("\n");
      break;
    case 'w':
      Serial.write("\nStarting pull-out test...\n\n");
      pullTorque(false, 1500, 700, 50);
      Serial.write("\n");
      break;
    case 'e':
      Serial.write("\nStarting recorded commands...\n\n");
      printCommandList();
      runCommandList();
      break;
    case 'r':
      Serial.write("\nStarting teach-in mode...\n");
      Serial.write("You can record up to 10 commands using the numbers of the commands\n");
      Serial.write("The record will stop when it reads 10 comands or a \'r\' command\n");
      Serial.write("Please entry the commands: ");
      recordCommands();
      Serial.write("Finished. The commands recorded are:\n\n");
      printCommandList();
      break;
    default:
      Serial.write("404!\n");        
    } 
}

void mainMenu() {
  printMainMenu();

  // Evaluate while there is a character in the buffer
  do {
    evaluate(true, '\0');
  } while (Serial.available()); 
}

void loop() { // run over and over
    mainMenu();
}

