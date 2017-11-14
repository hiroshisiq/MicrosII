#include <SoftwareSerial.h>
#include <math.h>

const int buttonPin[8] = {11, 10 , 9 , 8 , 3 , 2 , 5 , 4}; // Ordem errada
                         // 6, 7, 4, 5, 8, 9, 10, 11
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
  return dec;

}


float tempLookUp(int code){

  // Temperature table
  
  float  table[140]={56,  55, 54, 53, 52, 51, 50, 49.50,  49, 48, 47.50,  47, 46, 45, 44.50,  44, 43, 42.50,  42, 41, 40.50,  40, 39, 38.50,  38, 37.50,  37, 36, 35, 34.50,  34, 33, 32.50,  32, 31.50,  31, 30, 29.50,  29, 28.50,  28, 27.50,  27, 26.50,  26, 25.667, 25.33,  25, 24, 23.50,  23, 22.667, 22.33,  22, 21.50,  21, 20.50,  20, 19.50,  19, 18.50,  18, 17.50,  17, 16.50, 16, 15.50,  15, 14.667,  14.33,  14, 13.667, 13.33,  13, 12.50,  12, 11.50,  11, 10.667, 10.33,  10, 9.50,  9,  8.50, 8,  7.667,  7.333,  7,  6.50, 6,  5.50, 5,  4.667,  4.333,  4,  3.667,  3.333,  3,  2.50, 2,  1.50, 1,  0.500,  0,  -0.500, -1, -1.333, -1.667, -2, -2.50,  -3, -3.50,  -4, -4.50,  -5, -5.333, -5.667, -6, -6.50,  -7, -7.50,  -8, -8.50,  -9, -9.333, -9.667, -10,  -11,  -11.50, -12,  -12.50, -13,  -13.33, -13.667,  -14,  -14.50, -15,  -16,  -16.50, -17};
  return table[code-33];
  
}

double tempPol(int code, int order){
  // Order must be greater than 0 and less than 6!
  // pol is a matrix of polynom coeficients: Line for order and column for a, b, c, d etc.  
  // This function returns a polynomial aproximation for temperature given the code from the A/D
  // These polynoms were calculated for x = [0:139], so it's 'x' must be code - 33 (lowest code).

  double res=0;
  int i;
  int n = code - 33;

  double pol[5][6] ={{0,0,0,0,49.7036,-0.4869},
                     {0,0,0,0.0010,-0.6308, 53.0135},     
                     {0,0,-0.00001856, 0.0067, -1.2296, 89.3541},
                     {0,55.6572, -0.8757, 0.0059, -0.000029708, 0.000000040091},
                     {55.5548, -0.8524, 0.0047, -0.0000067898, -0.00000014572, 0.00000000053472}};

  for(i=0;i<order+1;i++){
    res+=pow(n,i)*pol[order-1][5-order+i];
  }
  
  return res;
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
  delay(500);
}


