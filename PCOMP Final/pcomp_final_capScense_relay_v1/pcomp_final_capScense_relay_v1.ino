#include <CapacitiveSensor.h>

CapacitiveSensor   cs_4_2 = CapacitiveSensor(4,2);// 1M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   cs_4_5 = CapacitiveSensor(4,5);
CapacitiveSensor   cs_4_6 = CapacitiveSensor(4,6);

// --------------Time variables to measure time constants--------------
unsigned long startTime;
unsigned long elapsedTime;
int delayInterval = 1000; //The amount of time between each pulse
int pulseLength = 1000; //length of high voltage pulse

int voltageReadingTwo[24]; //create an array to store voltage values from electrode number 2
float averageVoltageReadingTwo; //average voltage values from electrode number 2
int voltageReadingThree[24]; //create an array to store voltage values from electrode number 3
float averageVoltageReadingThree; //average voltage values from electrode number 3
int voltageReadingFour[24]; //create an array to store voltage values from electrode number 3
float averageVoltageReadingFour; //average voltage values from electrode number 3

const int relayPin = 0;	    // use this pin to drive the transisto

void setup(){
  pinMode(relayPin, OUTPUT);  // set relay pin as an output
  digitalWrite(relayPin, LOW);  // turn the relay on; 0 volts being passed
  cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
  cs_4_5.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_4_6.set_CS_AutocaL_Millis(0xFFFFFFFF);  

  Serial.begin(9600);

}  

void loop(){

  averageVoltageReadingTwo = 0;
  averageVoltageReadingThree = 0;
  averageVoltageReadingFour = 0;

  for (int i = 0; i < 24; i++){
    digitalWrite(relayPin, LOW);   // turn the relay off; 0 volts is being passed
    //    Serial.println("switch is on, and voltage is being passed"); 
    delay(pulseLength); //pauses program in microseconds (1000 microseconds/milliseconds)
    digitalWrite(relayPin, HIGH);   // turn the relay on; 8.31 volts is being passed
    //    Serial.println("switch is off, and 0 voltage is being passed");  

    //store each reading into the respective arrays
    voltageReadingTwo[i] = cs_4_2.capacitiveSensor(30);
    voltageReadingThree[i] = cs_4_5.capacitiveSensor(30);
    voltageReadingFour[i] = cs_4_6.capacitiveSensor(30);    

    delay(delayInterval);

    averageVoltageReadingTwo = averageVoltageReadingTwo + voltageReadingTwo[i];
    averageVoltageReadingThree = averageVoltageReadingThree + voltageReadingThree[i];
    averageVoltageReadingFour = averageVoltageReadingFour + voltageReadingFour[i];

  }

  averageVoltageReadingTwo = averageVoltageReadingTwo/24;
  averageVoltageReadingThree = averageVoltageReadingThree/24;
  averageVoltageReadingFour = averageVoltageReadingFour/24;

  //  Serial.print("Average Voltage 2: ");
  //  Serial.print(" Voltage Reading 2: ");
  Serial.print(averageVoltageReadingTwo);
  Serial.print(",");
  for (int i = 0; i < 24; i++) {
    Serial.print(voltageReadingTwo[i]);
    Serial.print(",");
  }

  Serial.print("ELECTRODE 3");
  Serial.print(",");
  Serial.print(averageVoltageReadingThree);
  Serial.print(",");
  for (int i = 0; i < 24; i++) {
    Serial.print(voltageReadingThree[i]);
    Serial.print(",");
  }


  Serial.print("ELECTRODE 4");
  Serial.print(",");
  Serial.print(averageVoltageReadingFour);
  Serial.print(",");
  for (int i = 0; i < 24; i++) {
    Serial.print(voltageReadingFour[i]);
    Serial.print(",");
  }

  Serial.println(" ");

}












