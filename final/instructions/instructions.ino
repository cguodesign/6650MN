#include <LedControl.h>

#include <Adafruit_VCNL4010.h>

#include "Wire.h"
extern "C" { 
#include "utility/twi.h"  // from Wire library, so we can do bus scanning
}

#include <NewPing.h>

#define TCAADDR 0x70

//#define  TRIGGER_PIN  11
//#define  ECHO_PIN     10
//#define MAX_DISTANCE 100 

LedControl lc=LedControl(12,11,10,1);

byte frame[] =
{
   B00000001,  // First frame of invader #1
   B00000001,
   B00000001,
   B00000001,
   B00000001,
   B00000001,
   B00000001,
   B11111111
};

byte arrowLeft[] =
{
   B00011000,  // First frame of invader #1
   B00110000,
   B01100000,
   B11111111,
   B01100000,
   B00110000,
   B00011000,
   B00000000
};

byte arrowRight[] =
{
   B00011000,  // First frame of invader #1
   B00001100,
   B00000110,
   B11111111,
   B00000110,
   B00001100,
   B00011000,
   B00000000
};

byte arrowDown[] =
{
   B00011000,  // First frame of invader #1
   B00011000,
   B00011000,
   B10011001,
   B01011010,
   B00111100,
   B00011000,
   B00000000
};

byte arrowUp[] =
{
   B00011000,  // First frame of invader #1
   B00111100,
   B01011010,
   B10011001,
   B00011000,
   B00011000,
   B00011000,
   B00000000
};

byte currentimage[] =
{
   B00000001,  // First frame of invader #1
   B00000001,
   B00000001,
   B00000001,
   B00000001,
   B00000001,
   B00000001,
   B11111111
};

byte a[7]={B10000001,B01000001,B00100001,B00010001,B00001001,B00000101,B00000011};

//#define DIR_PIN 2
//#define STEP_PIN 3

Adafruit_VCNL4010 vcnl1 = Adafruit_VCNL4010();
Adafruit_VCNL4010 vcnl2 = Adafruit_VCNL4010();

int button = 7;
int valDown = 0;
int valSide = 0;
int vDown = 0;
int vSide = 0;


/*-----( Declare Variables )-----*/
int DistanceIn;
int DistanceCm;

void tcaselect(uint8_t i) {
  if (i > 7) return;
 
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  

}

void setup()
{
    while (!Serial);
    delay(1000);
 
    Wire.begin();
    
    Serial.begin(9600);
    lc.shutdown(0,false);
    lc.setIntensity(0,5);  // Set intensity levels
    lc.clearDisplay(0);
    pinMode(2, INPUT_PULLUP);

    tcaselect(2);
    if (! vcnl1.begin()){
      Serial.println("Sensor not found :(");
      while (1);
    }

    tcaselect(7);
    if (! vcnl2.begin()){
      Serial.println("Sensor not found :(");
      while (1);
    }
}
 
void loop() 
{
    delay(200);
    tcaselect(2);
    //Serial.print("Sensor #1 - ");
    vDown = vcnl1.readProximity();

    tcaselect(7);
    //Serial.print("Sensor #2 - ");
    vSide = vcnl2.readProximity();
    Serial.print(vDown);Serial.print(" "); Serial.println(vSide);
    
    changeDots(vDown, vSide);
    //DistanceCm = sonar.ping_cm();
    //Serial.print("Ping: "); Serial.print(DistanceCm); Serial.println(" cm"); 
    button = digitalRead(2);
    if (button == LOW) {         // check if the input is HIGH (button released)
      valDown = vcnl1.readProximity();
      valSide = vcnl2.readProximity();
      //Serial.println("-----Data Saved------");
    }
    ledDisplay();

    delay(200);
}

void changeDots(int xValue, int yValue){
  if (xValue < 7500  ){
    if (yValue < 7500){
      //Serial.println("-----Data Varified------");
      int lineX = (int)(xValue - 500)/1000;
      int lineY = (int)(yValue - 500)/1000;
      //Serial.print("line at "); Serial.print(lineX); Serial.print("&"); Serial.println(lineY);
      lc.setRow(0,lineX,a[lineY]);
    }
  }
}

void ledDisplay(){
   for (int i = 0; i < 8; i++)  
   {
      lc.setRow(0,i,arrowUp[i]);
   }

   delay(500);

   
   for (int i = 0; i < 8; i++)  
   {
      lc.setRow(0,i,arrowLeft[i]);
   }

   delay(500);
   for (int i = 0; i < 8; i++)  
   {
      lc.setRow(0,i,arrowRight[i]);
   }

  delay(500);
   for (int i = 0; i < 8; i++)  
   {
      lc.setRow(0,i,arrowDown[i]);
   }
}

char GetBitArrayAsByte(const char inputArray[8])
{
    char result = 0;
    for (int idx = 0; idx < 8; ++idx)
    {
        result |= (inputArray[7-idx] << idx);
    }
    return result;
}

