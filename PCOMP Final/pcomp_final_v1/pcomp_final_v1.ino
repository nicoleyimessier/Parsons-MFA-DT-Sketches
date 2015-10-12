#include <CapacitiveSensor.h>

int stimulateElec = 13; //This pin will send a square wave to electrode 1
int eTwo = A0; // Electrode number 2
int eThree = A1; // Electrode number 3
int eFour = A2; // Electrode number 4

// --------------Time variables to measure time constants--------------
unsigned long startTime;
unsigned long elapsedTime;
int delayInterval = 100; //The amount of time between each pulse
int pulseLength = 100; //length of high voltage pulse

int voltageReadingTwo[23]; //create an array to store voltage values from electrode number 2
int voltageReadingThree[23]; //create an array to store voltage values from electrode number 3
int voltageReadingFour[23]; //create an array to store voltage values from electrode number 4
int averageVoltageReadingTwo = 0; //average voltage values from electrode number 2
int averageVoltageReadingThree = 0; //average voltage values from electrode number 2
int averageVoltageReadingFour = 0; //average voltage values from electrode number 2


void setup(){
  pinMode(stimulateElec, OUTPUT);
  digitalWrite(stimulateElec, LOW);

  Serial.begin(9600);
}  

void loop(){

  for (int i = 0; i < 24; i++){
    digitalWrite(stimulateElec, HIGH);
    delayMicroseconds(pulseLength); //pauses program in microseconds (1000 microseconds/milliseconds)
    digitalWrite(stimulateElec, LOW);

    //store each reading into the respective arrays
    voltageReadingTwo[i] = analogRead(eTwo); 
    voltageReadingThree[i] = analogRead(eThree); 
    voltageReadingFour[i] = analogRead(eFour);

    delayMicroseconds(delayInterval);

    averageVoltageReadingTwo = averageVoltageReadingTwo + voltageReadingTwo[i];
    averageVoltageReadingThree = averageVoltageReadingThree + voltageReadingThree[i];
    averageVoltageReadingFour = averageVoltageReadingFour + voltageReadingFour[i];
  }

  averageVoltageReadingTwo = averageVoltageReadingTwo/23;
  averageVoltageReadingThree = averageVoltageReadingThree/23;
  averageVoltageReadingThree = averageVoltageReadingThree/23;

  Serial.print("Voltage Reading 2: ");
  for (int i = 0; i < 24; i++) {
  Serial.print(voltageReadingTwo[i]);
  Serial.print(",");
  }
  
  Serial.println(" ");
  Serial.print("Voltage Reading 3: ");
  Serial.println(voltageReadingThree);
  Serial.print("Voltage Reading 4: ");
  Serial.println(voltageReadingFour);
  Serial.print("Average Voltage 2: ");
  Serial.print(averageVoltageReadingTwo);
  Serial.print("Average Voltage 3: ");
  Serial.print(averageVoltageReadingThree);
  Serial.print("Average Voltage 4: ");
  Serial.print(averageVoltageReadingFour);
}




