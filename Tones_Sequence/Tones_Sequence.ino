#include "pitches.h"
int speaker = 11;
int button = 2;

void setup(){
 Serial.begin(9600); 
 pinMode(speaker, OUTPUT);
 pinMode(button, INPUT);
 
 
}

void loop(){
  
  
  
  
  tone(speaker, NOTE_A4);
  delay(500);
  tone(speaker, NOTE_A5);
  delay(500);
  noTone(speaker);
  delay(500);
}
