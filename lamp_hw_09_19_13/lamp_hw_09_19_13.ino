int fsrAnalogPin = 0; // FSR is connected to analog 0
int LEDpin = 11;      
int fsrReading;      // the analog reading from the FSR resistor divider
int LEDbrightness;
 
void setup(void) {
  Serial.begin(9600); 
  pinMode(LEDpin, OUTPUT);
}
 
void loop(void) {
  fsrReading = analogRead(fsrAnalogPin);
 
  // map analog reading range (0-1023) to the analog write range analogWrite (0-255)
  LEDbrightness = map(fsrReading, 0, 1023, 0, 255);
  
  analogWrite(LEDpin, LEDbrightness);
 
  delay(100);
}
