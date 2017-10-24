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
int K=2;
const int c = 261/K;
const int d = 294/K;
const int e = 329/K;
const int f = 349/K;
const int g = 391/K;
const int gS = 415/K;
const int a = 440/K;
const int aS = 455/K;
const int b = 466/K;
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

// Pins
#define clockPin 3 
#define inibPin 11 
#define dirPin 5 

// States
int clockState = LOW;
int inibState  = LOW;
int dirState   = LOW;

// Command recorder 
char commandList[commandListLength] = "3636363636";

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial);

  // First print on serial
  Serial.write("Song!\n");

  // Set pin mode

}




void firstSection()
{
  tone(clockPin,a, 500);  delay(500);
  tone(clockPin,a, 500);  delay(500);
  tone(clockPin,a, 500);  delay(500);
  tone(clockPin,f, 350); delay(350);
  tone(clockPin,cH, 150); delay(150);  
  tone(clockPin,a, 500); delay(500);
  tone(clockPin,f, 350); delay(350);
  tone(clockPin,cH, 150); delay(150);
  tone(clockPin,a, 650); delay(650);
  Serial.println(a);
  delay(500);
 
  tone(clockPin,eH, 500); delay(500);
  tone(clockPin,eH, 500); delay(500);
  tone(clockPin,eH, 500); delay(500);  
  tone(clockPin,fH, 350); delay(350);
  tone(clockPin,cH, 150); delay(150);
  tone(clockPin,gS, 500); delay(500);
  tone(clockPin,f, 350); delay(350);
  tone(clockPin,cH, 150); delay(150);
  tone(clockPin,a, 650); delay(650);
 
  delay(500);

}

void secondSection()
{
  tone(clockPin,aH, 500); delay(500);
  tone(clockPin,a, 300); delay(300);
  tone(clockPin,a, 150); delay(150);
  tone(clockPin,aH, 500); delay(500);
  tone(clockPin,gSH, 325); delay(325);
  tone(clockPin,gH, 175); delay(175);
  tone(clockPin,fSH, 125); delay(125);
  tone(clockPin,fH, 125); delay(125);    
  tone(clockPin,fSH, 250); delay(250);
 
  delay(325);
 
  tone(clockPin,aS, 250); delay(250);
  tone(clockPin,dSH, 500); delay(500);
  tone(clockPin,dH, 325); delay(325);  
  tone(clockPin,cSH, 175); delay(175);  
  tone(clockPin,cH, 125); delay(125);  
  tone(clockPin,b, 125); delay(125);  
  tone(clockPin,cH, 250); delay(250);  
 
  delay(350);
}

void loop() { // run over and over

    firstSection();
    secondSection();

}
