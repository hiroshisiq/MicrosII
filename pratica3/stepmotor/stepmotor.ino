#include <SoftwareSerial.h>

/*|      | cabo  | arduino |
  | clk  |  0    |    4    |
  | dir  |  1    |    5    |
  | inib |  7    |   11    |
*/

/* Pull in  2.2 ms delay
 * Pull out 1.1 ms delay
 */

// Constants
#define defaultPeriod 3000 // us
#define fullTurnSteps 200  // steps
#define commandListLength 21 // (up to 10 commands)

// Pins
#define clockPin 4 
#define inibPin 11 
#define dirPin 5 

// States
int clockState = LOW;
int inibState  = LOW;
int dirState   = LOW;

// Command recorder 
char commandList[commandListLength] = "3636363636";

// Notes
int K=2;
const int c = 261/K;
const int cS= 278/K;
const int d = 294/K;
const int e = 329/K;
const int f = 349/K;
const int fS= 370/K;
const int g = 391/K;
const int gS = 415/K;
const int a = 440/K;
const int aS = 466/K;
const int b = 494/K;
const int cH = 523/K;
const int cSH = 554/K;
const int dH = 587/K;
const int dSH = 622/K;
const int eH = 659/K;
const int fH = 698/K;
const int fSH = 740/K;
const int gH = 784/K;
const int gSH = 830/K;
const int aH = 880/K;
const int REST = 1;


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

//void firstSection()
//{
//  tone(clockPin,a, 500);  delay(500);
//  tone(clockPin,a, 500);  delay(500);
//  tone(clockPin,a, 500);  delay(500);
//  tone(clockPin,f, 350); delay(350);
//  tone(clockPin,cH, 150); delay(150);  
//  tone(clockPin,a, 500); delay(500);
//  tone(clockPin,f, 350); delay(350);
//  tone(clockPin,cH, 150); delay(150);
//  tone(clockPin,a, 650); delay(650);
//  Serial.println(a);
//  delay(500);
// 
//  tone(clockPin,eH, 500); delay(500);
//  tone(clockPin,eH, 500); delay(500);
//  tone(clockPin,eH, 500); delay(500);  
//  tone(clockPin,fH, 350); delay(350);
//  tone(clockPin,cH, 150); delay(150);
//  tone(clockPin,gS, 500); delay(500);
//  tone(clockPin,f, 350); delay(350);
//  tone(clockPin,cH, 150); delay(150);
//  tone(clockPin,a, 650); delay(650);
// 
//  delay(500);
//
//}
//
//void secondSection()
//{
//  tone(clockPin,aH, 500); delay(500);
//  tone(clockPin,a, 300); delay(300);
//  tone(clockPin,a, 150); delay(150);
//  tone(clockPin,aH, 500); delay(500);
//  tone(clockPin,gSH, 325); delay(325);
//  tone(clockPin,gH, 175); delay(175);
//  tone(clockPin,fSH, 125); delay(125);
//  tone(clockPin,fH, 125); delay(125);    
//  tone(clockPin,fSH, 250); delay(250);
// 
//  delay(325);
// 
//  tone(clockPin,aS, 250); delay(250);
//  tone(clockPin,dSH, 500); delay(500);
//  tone(clockPin,dH, 325); delay(325);  
//  tone(clockPin,cSH, 175); delay(175);  
//  tone(clockPin,cH, 125); delay(125);  
//  tone(clockPin,b, 125); delay(125);  
//  tone(clockPin,cH, 250); delay(250);  
// 
//  delay(350);
//}

void playSong(int* song, int noteTime){
//  --Vector "song" is a vector of integers. It is sequencial, first a note,
//  then its duration (normalized), then a note, it's duration and so on.
//  'REST' note for no note. The vector MUST end with two 0 values in order to
//  work properly.
//  --This function plays the note for 4/5 of its duration, then plays nothing
//  for 1/5 of its duration (for better listening reasons).
//  --noteTime is the unit of time, in milisseconds. For example the call
//  "playSong(song,100);" where song[]={a,2,cH,3.5,REST,10,0.0,0.0}
//  will play note 'a' for 160 ms, note 'cH' for 260 ms (3.5*4/5*100),then will
//  remain silent for 1000 ms.

  
  int i;
  int noteDuration = noteTime*4/5;
  
  for(i=0;song[i]!=0.0;i+=2){
    if(song[i]==REST){
      noTone(clockPin);
    }else{
      tone(clockPin,song[i],song[i+1]*noteDuration);
    }
    delay(song[i+1]*noteTime);
  }
  noTone(clockPin);
  
}

void playStarWars(){

    int firstSection[]= {
      a,10,a,10,f,7,cH,3,a,10,f,7,cH,3,a,13,REST,10,
      eH,10,eH,10,eH,10,fH,7,cH,3,gS,10,f,7,cH,3,a,13,REST,10,
      0.0,0.0
    };

    int secondSection[]= {
      aH,20,a,12,a,6,aH,20,gSH,13,gH,7,fSH,5,fH,5,fSH,10,REST,13,
      aS,10,dSH,20,dH,13,cSH,7,cH,5,b,5,cH,10,REST,10,
      0.0,0.0
    };

    playSong(firstSection,50);
    playSong(secondSection,25);
}

void playStillAlive(){

  int song[] = {

  // First line
  REST, 2.0, g, 0.5, fS, 0.5, e, 0.5, e, 0.5,
  fS, 2.0, REST, 2.0,
  
  REST, 1.5, a/2, 0.5,
  g, 0.5, fS, 0.5, e, 0.5, e, 1.0,
  
  fS, 1.5,
  d, 1.0, e, 0.5, a/2, 2.5,
  
  REST, 1.5, a/2, 0.5,
  
  // Second line
  e, 1.0, fS, 0.5, g, 1.5, e, 0.5, cS, 1.0,
  d, 1.5, e, 1.0, a/2, 0.5, a/2, 1.0,
  fS, 1.5, REST, 2.0,
  
  REST, 2.0, g, 0.5, fS, 0.5, e, 0.5, e, 0.5,
  fS, 2.0, REST, 2.0,
  
  // Third line
  REST, 1.0, REST, 0.5, a/2, 0.5, g, 0.5, fS, 0.5, e, 0.5, e, 1.5,
  fS, 0.5, d, 1.5, e, 0.5, a/2, 2.5,
  REST, 2.0,
  
  e, 1.0, fS, 0.5, g, 1.5, e, 0.5, cS, 1.5,
  d, 0.5, e, 1.0, a/2, 0.5, d, 0.5, e, 0.5,
  
  // Fourth line
  f, 0.5, e, 0.5, d, 0.5, c, 0.5, REST, 1.0, a/2, 0.5, aS/2, 0.5,
  c, 1.0, f, 1.0, e, 0.5, d, 0.5, d, 0.5, c, 0.5,
  d, 0.5, c, 0.5, c, 1.0, c, 1.0, a/2, 0.5, aS/2, 0.5,
  c, 1.0, f, 1.0, g, 0.5, f, 0.5, e, 0.5, d, 0.5,
  d, 0.5, e, 0.5, f, 1.0, f, 1.0, g, 0.5, a, 0.5,
  
  // Fifth line
  aS, 0.5, aS, 0.5, a, 1.0, g, 1.0, f, 0.5, g, 0.5,
  a, 0.5, a, 0.5, g, 1.0, f, 1.0, d, 0.5, c, 0.5,
  d, 0.5, f, 0.5, f, 0.5, e, 1.0, e, 0.5, fS, 0.5, fS, 1.5,
  
      // and belive me…
  REST, 2.0, a, 0.5, a, 0.5, 
  b, 0.5, a, 0.5, fS, 0.5, d, 1.0, e, 0.5, fS, 0.5, fS, 1.5,
  REST, 1.5, a, 0.5, a, 0.5, a, 0.5, 
  
    // science and im still…
  b, 0.5, a, 0.5, fS, 0.5, d, 1.0, e, 0.5, fS, 0.5, fS, 1.5,
  
  REST, 1.5, a, 0.5, a, 0.5, a, 0.5, 
  b, 0.5, a, 0.5, fS, 0.5, d, 1.0, e, 0.5, fS, 0.5, fS, 1.5,
  
  REST, 2.0, a, 0.5, a, 0.5, 
  b, 0.5, a, 0.5, fS, 0.5, d, 1.0, e, 0.5, fS, 0.5, fS, 1.5,
  
  REST, 1.5, a, 0.5, a, 0.5, a, 0.5, 
  b, 0.5, a, 0.5, fS, 0.5, d, 1.0, e, 0.5, fS, 0.5, fS, 1.5,
  
  REST, 1.5, a, 0.5, a, 0.5, a, 0.5, 
  b, 0.5, a, 0.5, fS, 0.5, d, 1.0, e, 0.5, fS, 0.5, fS, 1.5,
  
  // still alive… still alive…
  REST, 1.5, g, 0.5, a, 0.5, a, 1.5, 
  REST, 1.5, g, 0.5, fS, 0.5, fS, 1.5,
  
  // End of song
  0.0, 0.0
  };

  playSong(song,250);

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



void appendCommands() {  
  int i, len;
  char command;

  // Seach for the last command
  for(len=0; len < commandListLength && commandList[len] != '\0'; len++);
  
  for(i=len; i<commandListLength-1; i++) {
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
  Serial.write("t. Play Star Wars theme song.\n");
  Serial.write("y. Play Still Alive.\n");
  Serial.write("z. Continuous turning mode.\n");
}

void turnForever(){
    char command = 'a';
    int dir = HIGH;
    Serial.write("Press 'x' to stop, or another key to change direction.\n");
    while(command != 'x'){
      while(!Serial.available()){
        turn(1,defaultPeriod,dir);  
      }
      command = Serial.read();
      changeDirectionState();
    }
}

void teachInMode() {
  Serial.write("\nStarting teach-in mode...\n");
  Serial.write("You can record up to 10 commands using the numbers of the commands\n");
  Serial.write("Entry \'a\' to append or \'n\' to creat new sequence\n");

  while(!Serial.available());
  char command = Serial.read();

  switch(command) {
    case 'a':    
      Serial.write("The append will stop when it reads max commands or a \'r\' command\n");
      Serial.write("Please entry the commands: ");
      appendCommands();
      break;
    
    case 'n':
      Serial.write("The record will stop when it reads max commands or a \'r\' command\n");
      Serial.write("Please entry the commands: ");
      recordCommands();
      break;
  }
  
  Serial.write("Finished. The commands recorded are:\n\n");
  printCommandList();
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
      pullTorque(true, 2450, 2250, 10);
      Serial.write("\n");
      break;
    case 'w':
      Serial.write("\nStarting pull-out test...\n\n");
      pullTorque(false, 3000, 500, 100);
      Serial.write("\n");
      break;
    case 'e':
      Serial.write("\nStarting recorded commands...\n\n");
      printCommandList();
      runCommandList();
      break;
    case 'r':
      teachInMode();
      break;
    case 't':
      playStarWars();
      break;
    case 'y':
      playStillAlive();
      break;
    case 'z':
      turnForever();
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
