const int port[8] = {11, 10 , 9 , 8 , 3 , 2 , 5 , 4};

// https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/

void setup() {
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

  // Initial Configuration (left)
  digitalWrite(port[0], HIGH); 
  digitalWrite(port[1], LOW ); 
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

bool getCapPresence() {
  return (digitalRead(port[2]) == HIGH)? false : true;
}

bool getIndPresence() {
  return (digitalRead(port[3]) == HIGH)? false : true;
}

void loop() {
//  digitalRead(buttonPin[i]);
}
