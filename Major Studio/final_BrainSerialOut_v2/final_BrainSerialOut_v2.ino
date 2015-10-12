#include <Brain.h>
int     commaPosition;  // the position of the next comma in the string


// Set up the brain parser, pass it the hardware serial object you want to listen on.
Brain brain(Serial);

void setup() {
  // Start the hardware serial.
  Serial.begin(9600);
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
      if(commaPosition != -1)
      {
        String connectivity = brainString.substring(0,commaPosition);
        Serial.print("Connectivity: ");
        Serial.println(connectivity);
         
//        Serial.println( brainString.substring(0,commaPosition));
        brainString = brainString.substring(commaPosition+1, brainString.length());
        
        String attention = brainString.substring(0,commaPosition);
        Serial.print("Attention: ");
        Serial.println(attention);
        
        brainString = brainString.substring(commaPosition+1, brainString.length());
        
        String meditation = brainString.substring(0,commaPosition);
        Serial.print("Meditation: ");
        Serial.println(meditation);
        
        
      }
      else
      {  // here after the last comma is found
        if(brainString.length() > 0)
          Serial.println(brainString);  // if there is text after the last comma,
        // print it
      }
    }
    while(commaPosition >=0);
  }


}




