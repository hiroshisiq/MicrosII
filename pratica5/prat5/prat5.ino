#include <SoftwareSerial.h>

// Time
#define REJECT_TIME 1000
#define WAIT_TIME 2000
#define ACTING_TIME 500

// Pinout
const int port[8] = {11, 10 , 9 , 8 , 3 , 2 , 5 , 4};

// Control
bool optical = false;
bool ind = false;
bool cap = false;
bool handling = false;
bool rejectMetal = false;
bool rejectNonMetal = false;

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

  // Initial Configuration (left)
  digitalWrite(port[0], HIGH); 
  digitalWrite(port[1], LOW ); 
}

void handleIndSensor() {
  if(handling == false) {
    ind = true;
    handling = true;
  } 
}

void handleCapSensor() {
  if(handling == false) {
    cap = true;
    handling = true;
  }
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
  return (digitalRead(port[4]) == HIGH)? false : true;
}

void handle() {
  // Check if is handling something
  if(handling == true) {
    // If is handling check if is handling metal or non-metal
    if(ind == true) {
      if(rejectMetal) {
        // DISCART
        delay(REJECT_TIME);
        cReject();  
        delay(ACTING_TIME);
        cReturn();      
      } else {
        // WAIT
        delay(WAIT_TIME);
      }      
    } else if (cap == true) {
      if(rejectNonMetal) {        
        // DISCART
        delay(REJECT_TIME);
        cReject();  
        delay(ACTING_TIME);
        cReturn();        
      } else {
        // WAIT
        delay(WAIT_TIME);
      }  
    }    
  }
}

void reset() {
  // Has reject or acept, need to reset
  if(handling == true) {
    // Reset 
    turnConveyorLeft();
    
    // Wait until a block reaches the start point 
    while(getOpticalPresence == false);

    // Reconfigure
    turnConveyorRight();
    ind = false;
    cap = false; 
    handling = false;  
  }
}

void loop() {
  handle();
  reset();
  delay(50);
}
