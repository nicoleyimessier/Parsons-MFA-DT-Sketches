/*Parts of this code were used from the "Example Sound Level Sketch for the
 Adafruit Microphone Amplifier" & "Sparkfun ADXL3xx code"*/

#include "SD.h"
#include <Wire.h>
#include "RTClib.h"
#include "pitches.h"

int redLEDpin = 7;
int speaker = 6;

RTC_DS1307 RTC;  //Declaring RTC device
const int chipSelect = 10;

float X,Y,Z;

//AMP Constants
const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;

//motion detection
const int xPin = A1;     // X output of the accelerometer
const int yPin = A0; // Y output of the accelerometer
int yMotion;
int y2Motion;
int yDelta;
int xMotion;
int x2Motion;
int xDelta;
int zMotion;
int z2Motion;
int zDelta;


void setup()
{
  Serial.begin(9600);
  pinMode(2,OUTPUT);
  Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(10, OUTPUT);

  pinMode(0, OUTPUT);   //For sleep on the accelerometer
  digitalWrite(0, HIGH); 

  pinMode(1, OUTPUT);   //For 6g select on the accelerometer
  digitalWrite(1, HIGH); 

  pinMode(redLEDpin, OUTPUT);
  pinMode(speaker, OUTPUT);

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
  float X,Y,Z;
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  dataFile.println("Date,Timestamp,millis,X,Y,Z,Volts,peakToPeak, yMotion, y2Motion, yDelta, xMotion, x2Motion, xDelta, zMotion, z2Motion, zDelta ");
  dataFile.close();
  Serial.println("Date  Timestamp  millis   X   Y   Z   Volts   peakToPeak");

}

void loop()
{

  // --------------------ADXL------------------------------------
  // read three sensors and append to the string:
  for (int analogPin = 0; analogPin < 3; analogPin++) {
    delay(10);
    int sensor = analogRead(analogPin);

    if(analogPin==0)
    {
      X=sensor;
    }

    if(analogPin==1)
    {
      Y=sensor;
    }

    if(analogPin==2)
    {
      Z=sensor;
    }



  }



  //-------------Motion Detection ----------------------
  yMotion=analogRead(A0);
  xMotion=analogRead(A1);
  zMotion=analogRead(A2);
  delay(1000);
  y2Motion=analogRead(A0);
  x2Motion=analogRead(A1);
  z2Motion=analogRead(A2);
  yDelta = y2Motion - yMotion;
  xDelta = x2Motion - xMotion;
  zDelta = z2Motion - zMotion;


  Serial.print("Y= ");
  Serial.print(yMotion);
  Serial.print(" Y2= ");
  Serial.print(y2Motion);
  Serial.print(" yDelta= ");
  Serial.print(yDelta);
  Serial.print(" X= ");
  Serial.print(xMotion);
  Serial.print(" X2= ");
  Serial.print(x2Motion);
  Serial.print(" xDelta= ");
  Serial.print(xDelta);
  Serial.print(" z= ");
  Serial.print(zMotion);
  Serial.print(" z2= ");
  Serial.print(z2Motion);
  Serial.print(" zDelta= ");
  Serial.println(zDelta);

  if (abs(yDelta) > 2){
    digitalWrite(redLEDpin, HIGH);
    tone(speaker, NOTE_A4); 
    Serial.println("Y IS MOVING and MUSIC is on");
  }
  else{
    digitalWrite(redLEDpin, LOW);
    noTone(speaker);
    Serial.println("Y IS NOT MOVING and MUSIC is off");  

  }
  //--------------------AMP----------------------------------------
  unsigned long startMillis= millis();  // Start of sample window
  unsigned int peakToPeak = 0;   // peak-to-peak level

  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;

  // collect data for 50 mS
  while (millis() - startMillis < sampleWindow)
  {
    sample = analogRead(3);
    if (sample < 1024)  // toss out spurious readings
    {
      if (sample > signalMax)
      {
        signalMax = sample;  // save just the max levels
      }
      else if (sample < signalMin)
      {
        signalMin = sample;  // save just the min levels
      }
    }
  }
  peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
  double volts = (peakToPeak * 3.3) / 1024;  // convert to volts

  //trigger sound off with a certain frequency
  if (peakToPeak > 150) {
    digitalWrite(2,LOW);
    Serial.println("volume_sound: low");
  }
  else {
    digitalWrite(2, HIGH);
    Serial.println("volume_sound: high");
  }

  // --------------------Data Logging------------------------------------
  // open the file.

  Wire.begin();
  DateTime now;
  File dataFile = SD.open("test1.csv", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {

    // fetch the time
    now = RTC.now();

    dataFile.print(now.year(), DEC);
    dataFile.print("/");
    dataFile.print(now.month(), DEC);
    dataFile.print("/");
    dataFile.print(now.day(), DEC);
    dataFile.print(",");
    dataFile.print(now.hour(), DEC);
    dataFile.print(":");
    dataFile.print(now.minute(), DEC);
    dataFile.print(":");
    dataFile.print(now.second(), DEC);
    dataFile.print(",");
    dataFile.print(millis());
    dataFile.print(",");

    dataFile.print(X);
    dataFile.print(",");
    dataFile.print(Y);
    dataFile.print(",");
    dataFile.print(Z);
    dataFile.print(",");
    dataFile.print(volts);
    dataFile.print(",");
    dataFile.print(peakToPeak);

    dataFile.print(",");
    dataFile.print(yMotion);
    dataFile.print(",");
    dataFile.print(y2Motion);
    dataFile.print(",");
    dataFile.print(yDelta);

    dataFile.print(",");
    dataFile.print(xMotion);
    dataFile.print(",");
    dataFile.print(x2Motion);
    dataFile.print(",");
    dataFile.print(xDelta);
    dataFile.print(",");

    dataFile.print(zMotion);
    dataFile.print(",");
    dataFile.print(z2Motion);
    dataFile.print(",");
    dataFile.println(zDelta);

    dataFile.close();

    // print to the serial port too:


    // log time
    // Serial.print(now.unixtime()); // seconds since 1970
    // Serial.print(", ");
    Serial.println(" ");
    Serial.print(now.year(), DEC);
    Serial.print("/");
    Serial.print(now.month(), DEC);
    Serial.print("/");
    Serial.print(now.day(), DEC);
    Serial.print(", ");
    Serial.print(now.hour(), DEC);
    Serial.print(":");
    Serial.print(now.minute(), DEC);
    Serial.print(":");
    Serial.print(now.second(), DEC);
    Serial.print(", ");
    Serial.print(millis(), DEC);
    Serial.print(", ");

    Serial.print(X);
    Serial.print(", ");
    Serial.print(Y);
    Serial.print(", ");
    Serial.print(Z);
    Serial.print(", ");
    Serial.print(volts);
    Serial.print(", ");
    Serial.println(peakToPeak);


  }  
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }

}






