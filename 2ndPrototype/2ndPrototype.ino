#include <Adafruit_VCNL4010.h>

#include "Wire.h"
extern "C" { 
#include "utility/twi.h"  // from Wire library, so we can do bus scanning
}

#include <NewPing.h>

#define TCAADDR 0x70
#define  TRIGGER_PIN  11
#define  ECHO_PIN     10
#define MAX_DISTANCE 100 

Adafruit_VCNL4010 vcnl1 = Adafruit_VCNL4010();
Adafruit_VCNL4010 vcnl2 = Adafruit_VCNL4010();

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
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
    delay(100);
    tcaselect(2);
    Serial.print("Sensor #1 - ");
    Serial.print("Ambient: "); Serial.println(vcnl1.readAmbient());
    Serial.print("Sensor #1 - ");
    Serial.print("Proimity: "); Serial.println(vcnl1.readProximity());

    tcaselect(7);
    Serial.print("Sensor #2 - ");
    Serial.print("Ambient: "); Serial.println(vcnl2.readAmbient());
    Serial.print("Sensor #2 - ");
    Serial.print("Proimity: "); Serial.println(vcnl2.readProximity());
    delay(400);

    DistanceCm = sonar.ping_cm();
    Serial.print("Ping: "); Serial.print(DistanceCm); Serial.println(" cm"); 
}
