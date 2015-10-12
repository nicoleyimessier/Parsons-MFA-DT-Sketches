// Arduino Brain Library
// Serial out example, 	grabs the brain data and sends CSV out over the hardware serial.
// Eric Mika, 2010

#include <Brain.h>
int     commaPosition;  // the position of the next comma in the string
int value[11];  

int indexPosition;


// Set up the brain parser, pass it the hardware serial object you want to listen on.
Brain brain(Serial);

void setup() {
  // Start the hardware serial.
  Serial.begin(9600);
  indexPosition = 0;
}

void loop() {
  // Expect packets about once per second.
  // The .readCSV() function returns a string (well, char*) listing the most recent brain data, in the following format:
  // "signal strength, attention, meditation, delta, theta, low alpha, high alpha, low beta, high beta, low gamma, high gamma"	
  if (brain.update()) {
    Serial.println(brain.readErrors());
    String brainString = brain.readCSV();
    Serial.println(brainString);

    do
    {
      commaPosition = brainString.indexOf(',');
      
      value[indexPosition] = brainString.toInt();
      
      if(commaPosition != -1)
      {

        Serial.println( brainString.substring(0,commaPosition));
        brainString = brainString.substring(commaPosition+1, brainString.length());
//        Serial.print(commaPosition);
      }
      else
      {  // here after the last comma is found
        if(brainString.length() > 0)
          Serial.println(brainString);  // if there is text after the last comma,
        // print it
      }
      
      Serial.print("Index: ");
      Serial.println(indexPosition);
      indexPosition++;
    }
    while(commaPosition >=0);
    indexPosition = 0;
    
    for(int i = 0; i < 11; i++){
      Serial.println(value[i]);
    }

  }


}


