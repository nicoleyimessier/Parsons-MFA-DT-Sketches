/*
  SD card and Serial port datalogger for 3 axis accelerations
  Written by: Jacob Hollister
  
 This code is in the public domain.
 	 
 */

#include "SD.h"
#include <Wire.h>
#include "RTClib.h"

#define redLEDpin 7
#define greenLEDpin 6

RTC_DS1307 RTC;  //Declaring RTC device

const int chipSelect = 10;

void setup()
{
  Serial.begin(9600);
  Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(10, OUTPUT);

  pinMode(0, OUTPUT);   //For sleep on the accelerometer
 digitalWrite(0, HIGH); 
 
  pinMode(1, OUTPUT);   //For 6g select on the accelerometer
 digitalWrite(1, HIGH); 
 
  pinMode(redLEDpin, OUTPUT);
  pinMode(greenLEDpin, OUTPUT);
  digitalWrite(greenLEDpin, HIGH);  // Green light should always be on

  
  
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
  float X,Y,Z;
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  dataFile.println("Timestamp  millis   X   Y   Z");
  dataFile.close();
  Serial.println("Timestamp  millis   X   Y   Z");
  
}

void loop()
{ Wire.begin();

float X,Y,Z;
 
  DateTime now;
  // make a string for assembling the data to log:
 // String dataString = "";

  // read three sensors and append to the string:
  for (int analogPin = 0; analogPin < 3; analogPin++) {
     delay(10);
    int sensor = analogRead(analogPin);
   
    float g = sensor*.0237-8.0086; // Equation for bit->V->g's
    
    if(analogPin==0)
    {
      X=g;
      }
      
    if(analogPin==1)
    {
      Y=g;
       }
       
    if(analogPin==2)
    {
      Z=g;
      }
      
    
  }

  // open the file.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    
     // fetch the time
  now = RTC.now();
  
  dataFile.print(now.year(), DEC);
  dataFile.print("/");
  dataFile.print(now.month(), DEC);
  dataFile.print("/");
  dataFile.print(now.day(), DEC);
  dataFile.print(" ");
  dataFile.print(now.hour(), DEC);
  dataFile.print(":");
  dataFile.print(now.minute(), DEC);
  dataFile.print(":");
  dataFile.print(now.second(), DEC);
  dataFile.print("  ");
  dataFile.print(millis());
  dataFile.print("  ");
  
     dataFile.print(X);
     dataFile.print("  ");
     dataFile.print(Y);
     dataFile.print("  ");
     dataFile.println(Z);
     
    dataFile.close();
    
    // print to the serial port too:
    
    
  // log time
  // Serial.print(now.unixtime()); // seconds since 1970
 // Serial.print(", ");
  Serial.print(now.year(), DEC);
  Serial.print("/");
  Serial.print(now.month(), DEC);
  Serial.print("/");
  Serial.print(now.day(), DEC);
  Serial.print(" ");
  Serial.print(now.hour(), DEC);
  Serial.print(":");
  Serial.print(now.minute(), DEC);
  Serial.print(":");
  Serial.print(now.second(), DEC);
  Serial.print("  ");
   Serial.print(millis(), DEC);
  Serial.print("  ");
  
  Serial.print(X);
  Serial.print("  ");
  Serial.print(Y);
  Serial.print("  ");
  Serial.println(Z);

  
  }  
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
    digitalWrite(redLEDpin, HIGH);  // Error light
  } 
}
