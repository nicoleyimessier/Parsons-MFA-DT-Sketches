#include <Event.h>
#include <Timer.h>
#include "pitches.h"
#include <Time.h>

Timer t;
long startTime; //the value returned from millis when the switch is pressed
long duration; //variable to store the duration
int speaker = 8; // speaker is connected to digital pin 8
int sensor = 0; //FSR is connected to analog pin 0
int reading;
//to test make time equal to 30000000 microseconds which is 30 seconds
//to run actually app where time should be an hour change to time > 3600000000
int intervalLength = 30000000;
 

void setup(){
  Serial.begin(9600);
  pinMode(speaker, OUTPUT);
}

void loop(){
 reading = analogRead(sensor);
 Serial.print("Sensor: ");
 Serial.println(reading);

 time = micros(); //prints the time since program started running
 
 delay(1000);
 
 if(reading <= 0 & time > intervalLength){
  tone(speaker, NOTE_A7); 
 } else {
  noTone(speaker);
 }
 
 if (reading > 0  & time > intervalLength){
  startTime = millis();
  while(reading > 0);
  long duration = millis() - startTime;
  Serial.print("Duration: ");
  Serial.println(duration); 
 }
 
}

