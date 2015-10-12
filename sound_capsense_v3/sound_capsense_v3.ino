#include <CapacitiveSensor.h>
#include "pitch.h"

CapacitiveSensor   cs_4_2 = CapacitiveSensor(4,2);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   cs_1_6 = CapacitiveSensor(1,6);        // 10M resistor between pins 4 & 6, pin 6 is sensor pin, add a wire and or foil
CapacitiveSensor   cs_3_7 = CapacitiveSensor(3,7);        // 10M resistor between pins 4 & 8, pin 7 is sensor pin, add a wire and or foil

int speaker = 8;

void setup()                    
{
   cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   cs_1_6.set_CS_AutocaL_Millis(0xFFFFFFFF);
   cs_3_7.set_CS_AutocaL_Millis(0xFFFFFFFF);
   Serial.begin(9600);
   pinMode(speaker, OUTPUT);
}

void loop()                    
{
    long start = millis();
    long total1 =  cs_4_2.capacitiveSensor(30);
    long total2 =  cs_1_6.capacitiveSensor(30);
    long total3 =  cs_3_7.capacitiveSensor(30);

    Serial.print(millis() - start);        // check on performance in milliseconds
    Serial.print("\t");                    // tab character for debug windown spacing
    
//    Serial.print(total1);                  // print sensor output 1
//    Serial.print("\t");
    
//    float newTotal1 = map(total1, 0, 30000, 0, 100);
//    Serial.print("Right Sensor ");
    Serial.println(total1);
//    Serial.print("Middle Sensor ");
//    Serial.println(total2);
//    Serial.print("Left Sensor ");
//    Serial.println(total3);

    delay(10);                             // arbitrary delay to limit data to serial port 
    
    if (total1 > 7000 ){
      tone(speaker, NOTE_A4);
    } 
    else if (total2 > 7000){
      tone(speaker, NOTE_G4);
    }
    else if (total3 > 7000){
      tone(speaker, NOTE_GS6);
    }
    else {
      noTone(speaker);
    }
    
}
