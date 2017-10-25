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

int stillAlive[] = {

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



// Pins
#define clockPin 3 
#define inibPin 11 
#define dirPin 5 

void playSong(int* song){
  int i;
  for(i=0;song[i]!=0.0;i+=2){
    tone(clockPin,song[i],song[i+1]*200);
    delay(song[i+1]*250);
  }
}
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
    playSong(stillAlive);

}
