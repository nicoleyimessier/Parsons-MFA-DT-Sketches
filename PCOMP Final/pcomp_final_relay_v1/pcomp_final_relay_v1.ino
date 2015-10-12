#include <CapacitiveSensor.h>

int eTwo = A0; // Electrode number 2
int eThree = A1; // Electrode number 3
int eFour = A2; // Electrode number 4

// --------------Time variables to measure time constants--------------
unsigned long startTime;
unsigned long elapsedTime;
int delayInterval = 10; //The amount of time between each pulse
int pulseLength = 10; //length of high voltage pulse

int voltageReadingTwo[23]; //create an array to store voltage values from electrode number 2
int voltageReadingThree[23]; //create an array to store voltage values from electrode number 3
int voltageReadingFour[23]; //create an array to store voltage values from electrode number 4
int averageVoltageReadingTwo = 0; //average voltage values from electrode number 2
int averageVoltageReadingThree = 0; //average voltage values from electrode number 2
int averageVoltageReadingFour = 0; //average voltage values from electrode number 2

const int relayPin = 13;	    // use this pin to drive the transistor


void setup(){
  pinMode(relayPin, OUTPUT);  // set relay pin as an output
  digitalWrite(relayPin, LOW);  // turn the relay on; 0 volts being passed

  Serial.begin(9600);
}  

void loop(){

  for (int i = 0; i < 25; i++){
    digitalWrite(relayPin, LOW);   // turn the relay off; 0 volts is being passed
//    Serial.println("switch is on, and voltage is being passed"); 
    delay(pulseLength); //pauses program in microseconds (1000 microseconds/milliseconds)


    digitalWrite(relayPin, HIGH);   // turn the relay on; 8.31 volts is being passed
//    Serial.println("switch is off, and 0 voltage is being passed");  

    //store each reading into the respective arrays
    voltageReadingTwo[i] = analogRead(eTwo); 
    voltageReadingThree[i] = analogRead(eThree); 
    voltageReadingFour[i] = analogRead(eFour);

    delay(delayInterval); 

    averageVoltageReadingTwo = averageVoltageReadingTwo + voltageReadingTwo[i];
    averageVoltageReadingThree = averageVoltageReadingThree + voltageReadingThree[i];
    averageVoltageReadingFour = averageVoltageReadingFour + voltageReadingFour[i];
  }

  averageVoltageReadingTwo = averageVoltageReadingTwo/24;
  averageVoltageReadingThree = averageVoltageReadingThree/24;
  averageVoltageReadingFour = averageVoltageReadingFour/24;


  Serial.print(averageVoltageReadingTwo);
  Serial.print(",");
  for (int i = 0; i < 25; i++) {
    Serial.print(voltageReadingTwo[i]);
    Serial.print(",");
  }

  Serial.print("Electrode 3");
  Serial.print(",");
  Serial.print(averageVoltageReadingThree);
  Serial.print(",");
  for (int i = 0; i < 25; i++) {
    Serial.print(voltageReadingThree[i]);
    Serial.print(",");
  }

  Serial.print("Electrode 4");
  Serial.print(",");
  Serial.print(averageVoltageReadingFour);
  Serial.print(",");
  for (int i = 0; i < 25; i++) {
    Serial.print(voltageReadingFour[i]);
    Serial.print(",");
  }

  Serial.println(" ");
}








