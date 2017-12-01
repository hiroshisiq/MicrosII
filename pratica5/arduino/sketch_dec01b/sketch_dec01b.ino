#include <SoftwareSerial.h>

// Time [TODO] Ajustar tempo
unsigned long REJECT_M_TIME = 4400;
unsigned long REJECT_N_TIME = 3300;
unsigned long WAIT_M_TIME = 6000;
unsigned long WAIT_N_TIME = 6000;
unsigned long ACTING_TIME = 100;

// Configuration
#define GUI false

// Pinout
const byte port[8] = {4, 5 , 3 , 2 , 8 , 9 , 10 , 11};

// Control 
volatile bool opt   = false;
volatile bool ind   = false;
volatile bool cap   = false;

bool normalStart    = false;
bool testStart      = false;
bool rejectMetal    = true;
bool rejectNonMetal = true;
bool left           = false;
bool piston         = false;

enum normalState { RESET, SELECT, REJECT };
normalState state = RESET;

int lastState = 0;

// Time 
unsigned long serialTime; 
unsigned long nsTime;
bool nsTimerStarted = false;

// Control time list
unsigned long time_m[10]; volatile int count_m = 0;
unsigned long time_n[10]; volatile int count_n = 0;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial);
  
  // Direction              
  pinMode(port[0], OUTPUT); 
  pinMode(port[1], OUTPUT); 
                            
  // Cilinder
  pinMode(port[5], OUTPUT);
  pinMode(port[7], OUTPUT);

  // Sensors
//  pinMode(port[2], INPUT); // Ind
//  pinMode(port[3], INPUT); // Cap
  pinMode(port[4], INPUT); // Optical

  // Attach interruptions
  pinMode(port[2], INPUT_PULLUP);
  pinMode(port[3], INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(port[2]), handleIndSensor, FALLING);
  attachInterrupt(digitalPinToInterrupt(port[3]), handleCapSensor, FALLING);

  // Iniatilize 
  for(int i=0; i<10;i++) {
    time_m[i] = 4111222333;
    time_n[i] = 4111222333;
  }
  
}

void handleIndSensor() {
  ind = true; 
}

void handleCapSensor() {
  cap = true;
}

void stopConveyor() {
  digitalWrite(port[0], HIGH); 
  digitalWrite(port[1], HIGH);
}

void turnConveyorRight() {
  digitalWrite(port[0], LOW ); 
  digitalWrite(port[1], HIGH);
}

void turnConveyorLeft() {
  digitalWrite(port[0], HIGH); 
  digitalWrite(port[1], LOW );  
}

void cReject() {
  digitalWrite(port[5], HIGH); 
  digitalWrite(port[7], LOW );
}

void cReturn() {
  digitalWrite(port[5], LOW ); 
  digitalWrite(port[7], HIGH);
}

bool getOpticalPresence() {
  return opt = (digitalRead(port[4]) == HIGH)? false : true;
}

void comunicationGUI() {
  while (Serial.available()) {    
    // read the incoming byte:
    char incomingByte = Serial.read();

    // Store received information
    normalStart    = (bitRead(incomingByte, 0) == 1)? true : false;
    testStart      = (bitRead(incomingByte, 0) == 1)? true : false;
    rejectMetal    = (bitRead(incomingByte, 0) == 1)? true : false;
    rejectNonMetal = (bitRead(incomingByte, 0) == 1)? true : false;
    left           = (bitRead(incomingByte, 0) == 1)? true : false;
    piston         = (bitRead(incomingByte, 0) == 1)? true : false;
   
  }

  // Send information about the sensors
  char info = 0x00;
  if(digitalRead(port[2])) info |= 0x01;
  if(digitalRead(port[3])) info |= 0x02;
  if(digitalRead(port[4])) info |= 0x04;
  //Serial.print(info);
}

void comunication() {
  while (Serial.available()) {    
    // read the incoming byte:
    char incomingByte = Serial.read();

    // Store received information
    if(incomingByte == '0') {
      normalStart = false;
      testStart = false;
    } else if(incomingByte == '1') {
      normalStart = true;
      testStart = false;  
    } else if (incomingByte == '2') {
      normalStart = false;
      testStart = true;
    } else if (incomingByte == '3') {
      rejectMetal = !rejectMetal;
    } else if (incomingByte == '4') {
      rejectNonMetal = !rejectNonMetal;
    } else if (incomingByte == '5') {
      left = !left;
    } else if (incomingByte == '6') {
      piston = !piston;
    }   
  }

  // Send information about the sensors
  char info[10] = "000000000\0";
  //if(normalStart)          info[0] = "1"; 
  //if(testStart)            info[1] = "1"; 
  //if(rejectMetal)          info[2] = "1"; 
  //if(rejectNonMetal)       info[3] = "1"; 
  //if(left)                 info[4] = "1"; 
  //if(piston)               info[5] = "1"; 
  if(cap) info[0] = "1"; // cap 
  if(ind) info[1] = "1"; // ind
  if(opt) info[2] = "1"; // opt
  //Serial.println(info);
}

void normalStartStateMachine() {
  // NORMAL START STATE MACHINE
    switch(state) {
      case RESET: {
        Serial.println("Reset");
        
        // Conveyor on: Left
        turnConveyorLeft();

        // Reset Cilinder
        cReturn();

        // Reset variables
        ind = false;
        cap = false;
        opt = false;
        nsTimerStarted = false;         

        // Change Condition: Optical Sensor
        if(getOpticalPresence()) {
          state = SELECT;                  
        }
        
      } break;

      case SELECT: {
        //Serial.println("SELECT");
        
        // Conveyor on: Right
        turnConveyorRight();

        // Add Metal from Inductive Sensor
        if(ind) {
          // Low Pass Filter
          if(count_m > 0) {
            if(millis()-time_m[count_m-1] > 100) {
              time_m[count_m] = millis();
              count_m++;
            }
          } else {
            time_m[count_m] = millis();
            count_m++;
          }
          ind = false;                            
        }
        
        // Add Non-Metal from Capacitive Sensor
        if(cap) {
          if(millis() - time_m[count_m-1] > 1000 && millis() - time_m[count_m-1] < 2000) { // [TODO] Ajustar janela
            // Do not add anything
          } else {
            // Low Pass Filter 
            if(count_n > 0) {
              if(millis()-time_n[count_n-1] > 1000) {
                time_n[count_n] = millis();
                count_n++;
              }
            } else {
              time_n[count_n] = millis();
              count_n++;
            }
          }
          cap = false;                            
        }

        // Process metal queue
        if(millis() - time_m[0] >= REJECT_M_TIME && time_m[0] != 4111222333) {
          Serial.print("1 - - -M: ");
          Serial.print(count_m);
          Serial.print(" N: ");
          Serial.println(count_n);
        
          if(rejectMetal) {
            state = REJECT;
          }

          // Remove from queue
          for(int i=0; i<9; i++) {
            time_m[i] = time_m[i+1];
          }

          Serial.print("2 - - -M: ");
          Serial.print(count_m);
          Serial.print(" N: ");
          Serial.println(count_n);
          
          time_m[9] = 4111222333;

          count_m = count_m-1;        
        }
        
        // Process non-metal queue
        if(millis() - time_n[0] >= REJECT_N_TIME && time_n[0] != 4111222333) {
          if(rejectNonMetal) {
            state = REJECT;
          }

          // Remove from queue
          for(int i=0; i<9; i++) {
            time_n[i] = time_n[i+1];
          }
          time_n[9] = 4111222333;
                    
          count_n--;

          
        }

        nsTimerStarted = false;  
      
      } break;

      case REJECT: {
        //Serial.println("REJECT");
        
        // Start timer
        if(nsTimerStarted == false) {
          nsTime = millis();
          nsTimerStarted = true;
          cReject();
        }

        // Change Condition: Actuation Time
        if((millis()-nsTime) > ACTING_TIME) {
          cReturn();
          state = SELECT;                          
        }
        
      } break;
    }
}

void loop() {  
  if(normalStart) {
    normalStartStateMachine();      
  } else {
    // Conveyor test unit
    if(testStart) {
      if(left) {
        turnConveyorRight();
      } else {
        turnConveyorLeft();
      }
    } else {
      stopConveyor();
    }

    // Cilinder test unit
    if(piston) {
      cReject();
    } else {
      cReturn();
    }

    state = RESET;    
  }
  
  // Serial comutication ativate each 100ms
  if((millis() - serialTime) > 100) {
    // Send and receive info
    GUI? comunicationGUI() : comunication();  
    serialTime = millis();
  }
}
