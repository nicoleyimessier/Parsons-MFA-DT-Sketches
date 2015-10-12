/*Parts of this code were used from the "Example Sound Level Sketch for the
 Adafruit Microphone Amplifier" & "Sparkfun ADXL3xx code"*/

#include "SD.h"
#include <Wire.h>
#include "RTClib.h"

#define redLEDpin 7
#define greenLEDpin 6
#define triggerOne 5
#define silentTrigger 4

RTC_DS1307 RTC;  //Declaring RTC device

const int chipSelect = 10;

//AMP Constants
const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;
float X,Y,Z;

//calibrate variables
int min_x, min_y, min_z;
int max_x, max_y, max_z;
const unsigned int X_AXIS_PIN = A0;
const unsigned int Y_AXIS_PIN = A1;
const unsigned int Z_AXIS_PIN = A2;

//motion detection
boolean moveDetected=false; // When motion is detected - changes to true


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
  dataFile.println("Date,Timestamp,millis,X,Y,Z,Volts,peakToPeak");
  dataFile.close();
  Serial.println("Date  Timestamp  millis   X   Y   Z   Volts   peakToPeak");

  //  set initial calibrate values
  min_x = min_y = min_z = 1000;
  max_x = max_y = max_z = -1000;

}

void loop()
{ 

  //  ----------------CALIBRATE----------------------
  const int x = analogRead(X_AXIS_PIN);

  const int y = analogRead(Y_AXIS_PIN);

  const int z = analogRead(Z_AXIS_PIN);

  min_x = min(x, min_x); 
  max_x = max(x, max_x);

  min_y = min(y, min_y); 
  max_y = max(y, max_y);

  min_z = min(z, min_z); 
  max_z = max(z, max_z);

  Serial.print("x(");
  Serial.print(min_x);
  Serial.print("/");
  Serial.print(max_x);
  Serial.print("), y(");
  Serial.print(min_y);
  Serial.print("/");
  Serial.print(max_y);
  Serial.print("), z(");
  Serial.print(min_z);
  Serial.print("/");
  Serial.print(max_z);
  Serial.println(")");

  //  ---------------------END Calibrate---------------------------------


  // make a string for assembling the data to log:
  // String dataString = "";

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

  //testing sound with red led pin
  if (peakToPeak > 200) {
    digitalWrite(redLEDpin, HIGH); 
  }
  else {
    digitalWrite(redLEDpin, LOW);
  }

  //trigger sound off with a certain frequency
  if (peakToPeak > 150) {
    digitalWrite(2,LOW);
    digitalWrite(triggerOne, LOW);
    Serial.println("triggerOne: low");
  }
  else {
    digitalWrite(2, HIGH);
    digitalWrite(triggerOne, HIGH);
    Serial.println("triggerOne: high");
  }


  Wire.begin();
  DateTime now;

  // --------------------Data Logging------------------------------------
  // open the file.
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
    dataFile.println(peakToPeak);

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
    digitalWrite(redLEDpin, HIGH);  // Error light
  } 

}

//Function used to detect motion. Tolerance variable adjusts the sensitivity of movement detected.
boolean checkMotion(){
 boolean tempB=false;
 xVal = analogRead(x);
 yVal = analogRead(y);
 zVal = analogRead(z);
 
 if(xVal >(xMax+tolerance)||xVal < (xMin-tolerance)){
 tempB=true;
 Serial.print("X Failed = ");
 Serial.println(xVal);
 }
 
 if(yVal >(yMax+tolerance)||yVal < (yMin-tolerance)){
 tempB=true;
 Serial.print("Y Failed = ");
 Serial.println(yVal);
 }
 
 if(zVal >(zMax+tolerance)||zVal < (zMin-tolerance)){
 tempB=true;
 Serial.print("Z Failed = ");
 Serial.println(zVal);
 }
 
 return tempB;
}



