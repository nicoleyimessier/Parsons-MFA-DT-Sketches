/*Parts of this code were used from the "Example Sound Level Sketch for the
Adafruit Microphone Amplifier" & "Sparkfun ADXL3xx code"*/

// these constants describe the pins. They won't change:
const int groundpin = 18;             // analog input pin 4 -- ground
const int powerpin = 19;              // analog input pin 5 -- voltage
const int xpin = A0;                  // x-axis of the accelerometer
const int ypin = A1;                  // y-axis
const int zpin = A2;                  // z-axis (only on 3-axis models)

const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;

void setup()
{
  // initialize the serial communications:
  Serial.begin(9600);
  
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
}
