#include <SoftwareSerial.h>

// Time
#define REJECT_M_TIME 1000
#define REJECT_N_TIME 1000
#define WAIT_M_TIME 2000
#define WAIT_N_TIME 2000
#define ACTING_TIME 500

// Configuration
#define GUI true

// Pinout
const int port[8] = {4, 5 , 2 , 3 , 8 , 9 , 10 , 11};

// Control
bool opt            = false;
bool ind            = false;
bool cap            = false;

bool normalStart    = false;
bool testStart      = false;
bool rejectMetal    = false;
bool rejectNonMetal = false;
bool left           = false;
bool piston         = false;

enum normalState { RESET, SELECT, HANDLE_M, HANDLE_N, REJECT };
normalState state = RESET;

int lastState = 0;

// Time
unsigned int serialTime = 0;
unsigned int nsTime = 0;
bool nsTimerStarted = false;

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
  pinMode(port[2], INPUT); // Ind
  pinMode(port[3], INPUT); // Cap
  pinMode(port[4], INPUT); // Optical

  // Attach interruptions
  attachInterrupt(digitalPinToInterrupt(port[2]), handleIndSensor, FALLING);
  attachInterrupt(digitalPinToInterrupt(port[3]), handleCapSensor, FALLING);
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
  Serial.print(info);
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
  if(normalStart)          info[0] = "1";
  if(testStart)            info[1] = "1";
  if(rejectMetal)          info[2] = "1";
  if(rejectNonMetal)       info[3] = "1";
  if(left)                 info[4] = "1";
  if(piston)               info[5] = "1";
  if(digitalRead(port[2])) info[6] = "1"; // cap
  if(digitalRead(port[3])) info[7] = "1"; // ind
  if(digitalRead(port[4])) info[8] = "1"; // opt
  Serial.println(info);
}

void normalStartStateMachine() {
  // NORMAL START STATE MACHINE
    switch(state) {
      case RESET: {
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
        // Conveyor on: Right
        turnConveyorRight();

        // Change Condition: Capacitive Sensor
        if(cap) {
          state = HANDLE_N;
        }

        // Change Condition: Inductive Sensor
        if(ind) {
          state = HANDLE_M;
        }

      } break;

      case HANDLE_M: {
        // Start timer
        if(nsTimerStarted == false) {
          nsTime = millis();
        }

        // Reject or Accept material
        if(rejectMetal) {
          // Change Condition: Actuation Time
          if(abs(nsTime - millis()) < REJECT_M_TIME) {
            state = REJECT;
            nsTimerStarted = false;
          }
        } else {
          // Change Condition: Actuation Time
          if(abs(nsTime - millis()) < WAIT_M_TIME) {
            state = RESET;
          }
        }

      } break;

      case HANDLE_N: {
        // Start timer
        if(nsTimerStarted == false) {
          nsTime = millis();
        }

        // Reject or Accept material
        if(rejectNonMetal) {
          // Change Condition: Actuation Time
          if(abs(nsTime - millis()) < REJECT_N_TIME) {
            state = REJECT;
            nsTimerStarted = false;
          }
        } else {
          // Change Condition: Actuation Time
          if(abs(nsTime - millis()) < WAIT_N_TIME) {
            state = RESET;
          }
        }

      } break;

      case REJECT: {
        // Start timer
        if(nsTimerStarted == false) {
          nsTime = millis();
          cReject();
        }

        // Change Condition: Actuation Time
        if(abs(nsTime - millis()) < ACTING_TIME) {
          state = RESET;
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
  if(abs(serialTime - millis()) > 100) {
    // Send and receive info
    GUI? comunicationGUI() : comunication();
    serialTime = millis();
  }
}
