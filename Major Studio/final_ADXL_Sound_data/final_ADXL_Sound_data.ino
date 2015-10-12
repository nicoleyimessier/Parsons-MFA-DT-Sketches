/*Parts of this code were used from the "Example Sound Level Sketch for the
 Adafruit Microphone Amplifier" & "Sparkfun ADXL3xx code"*/

// -------------Data Logger-------------------------------
#include "SD.h"
#include <Wire.h>
#include "RTClib.h"

// A simple data logger for the Arduino analog pins
#define LOG_INTERVAL  1000 // mills between entries
#define SYNC_INTERVAL 1000 // mills between calls to flush() - to write data to the card
uint32_t syncTime = 0; // time of last sync()
#define ECHO_TO_SERIAL   1 // echo data to serial port
#define WAIT_TO_START    0 // Wait for serial input in setup()
#define redLEDpin 7
#define greenLEDpin 6

RTC_DS1307 RTC; // define the Real Time Clock object

// for the data logging shield, we use digital pin 10 for the SD cs line
const int chipSelect = 10;

// the logging file
File logfile;

// -------------ADXL Constants--------------------------------
const int xpin = A0;                  // x-axis of the accelerometer
const int ypin = A1;                  // y-axis
const int zpin = A2;                  // z-axis (only on 3-axis models)

// --------------------AMP Constants------------------------------------
const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;

// -------------Data Logger-------------------------------
void error(char *str)
{
  Serial.print("error: ");
  Serial.println(str);

  // red LED indicates error
  digitalWrite(redLEDpin, HIGH);

  while(1);
}

void setup()
{
  // initialize the serial communications:
  Serial.begin(9600);

  // -------------Data Logger-------------------------------
  // use debugging LEDs
  pinMode(redLEDpin, OUTPUT);
  pinMode(greenLEDpin, OUTPUT);

#if WAIT_TO_START
  Serial.println("Type any character to start");
  while (!Serial.available());
#endif //WAIT_TO_START

  // initialize the SD card
  Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(10, OUTPUT);

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    error("Card failed, or not present");
  }
  Serial.println("card initialized.");

  // create a new file
  char filename[] = "LOGGER00.CSV";
  for (uint8_t i = 0; i < 100; i++) {
    filename[6] = i/10 + '0';
    filename[7] = i%10 + '0';
    if (! SD.exists(filename)) {
      // only open a new file if it doesn't exist
      logfile = SD.open(filename, FILE_WRITE); 
      break;  // leave the loop!
    }
  }

  if (! logfile) {
    error("couldnt create file");
  }

  Serial.print("Logging to: ");
  Serial.println(filename);

  // connect to RTC
  Wire.begin();  
  if (!RTC.begin()) {
    logfile.println("RTC failed");
#if ECHO_TO_SERIAL
    Serial.println("RTC failed");
#endif  //ECHO_TO_SERIAL
  }


  logfile.println("millis,stamp,datetime,light,temp,vcc");    
#if ECHO_TO_SERIAL
  Serial.println("millis,stamp,datetime,light,temp,vcc");
#endif //ECHO_TO_SERIAL

  // If you want to set the aref to something other than 5v
  analogReference(EXTERNAL);

}

void loop()
{

  // --------------------ADXL------------------------------------
  // print the sensor values:
  Serial.print("X: ");
  Serial.print(analogRead(xpin));
  // print a tab between values:
  Serial.print("\t");
  Serial.print("Y: ");
  Serial.print(analogRead(ypin));
  // print a tab between values:
  Serial.print("\t");
  Serial.print("Z: ");
  Serial.print(analogRead(zpin));
  Serial.println();
  // delay before next reading:
  delay(100);

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

  Serial.print("volts: ");
  Serial.print(volts);
  Serial.print("/t");
  Serial.print("peakToPeak: ");
  Serial.println(peakToPeak);

  // -------------Data Logger-------------------------------
    DateTime now;

  // delay for the amount of time we want between readings
  delay((LOG_INTERVAL -1) - (millis() % LOG_INTERVAL));

  digitalWrite(greenLEDpin, HIGH);

  // log milliseconds since starting
  uint32_t m = millis();
  logfile.print(m);           // milliseconds since start
  logfile.print(", ");    
#if ECHO_TO_SERIAL
  Serial.print(m);         // milliseconds since start
  Serial.print(", ");  
#endif

  // fetch the time
  now = RTC.now();
  // log time
  logfile.print(now.unixtime()); // seconds since 1/1/1970
  logfile.print(", ");
  logfile.print('"');
  logfile.print(now.year(), DEC);
  logfile.print("/");
  logfile.print(now.month(), DEC);
  logfile.print("/");
  logfile.print(now.day(), DEC);
  logfile.print(" ");
  logfile.print(now.hour(), DEC);
  logfile.print(":");
  logfile.print(now.minute(), DEC);
  logfile.print(":");
  logfile.print(now.second(), DEC);
  logfile.print('"');
#if ECHO_TO_SERIAL
  Serial.print(now.unixtime()); // seconds since 1/1/1970
  Serial.print(", ");
  Serial.print('"');
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
  Serial.print('"');
#endif //ECHO_TO_SERIAL

  logfile.print(", ");    
  logfile.print(xpin);
  logfile.print(", ");    
  logfile.print(ypin);
  logfile.print(", ");    
  logfile.print(zpin);
  logfile.print(", ");    
  logfile.print(volts);
  logfile.print(", ");    
  logfile.print(peakToPeak);
  
//#if ECHO_TO_SERIAL
//  Serial.print(", ");   
//  Serial.print(photocellReading);
//  Serial.print(", ");    
//  Serial.print(temperatureF);
//#endif //ECHO_TO_SERIAL

  logfile.println();
#if ECHO_TO_SERIAL
  Serial.println();
#endif // ECHO_TO_SERIAL

  digitalWrite(greenLEDpin, LOW);

  // Now we write data to disk! Don't sync too often - requires 2048 bytes of I/O to SD card
  // which uses a bunch of power and takes time
  if ((millis() - syncTime) < SYNC_INTERVAL) return;
  syncTime = millis();
  
  // blink LED to show we are syncing data to the card & updating FAT!
  digitalWrite(redLEDpin, HIGH);
  logfile.flush();
  digitalWrite(redLEDpin, LOW);
}


