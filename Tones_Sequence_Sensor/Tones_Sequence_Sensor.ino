#include "pitches.h"
int speaker = 11;
int sensor = A0;
int sensorValue = 0;

void setup(){
 Serial.begin(9600); 
 pinMode(speaker, OUTPUT);
 pinMode(sensor, INPUT);
 
 
}

void loop(){
  
  sensorValue = analogRead(sensor);
  Serial.println(sensorValue);
  
  sensorValue = map(sensorValue, 1, 15, 31, 3000);
  tone(speaker, sensorValue);
  delay(1000);
  noTone(speaker);
}
