const int relayPin = 2;	    // use this pin to drive the transistor
const int timeDelay = 5000; // delay in ms for on and off phases

void setup()
{
  
  Serial.begin(9600);
  
  pinMode(relayPin, OUTPUT);  // set pin as an output
}


void loop()                    
{
  
  digitalWrite(relayPin, HIGH);  // turn the relay on
  
  Serial.println("switch is on, and zero voltage is being passed");
  
  delay(timeDelay);              // wait for one second
  
  digitalWrite(relayPin, LOW);   // turn the relay off
  
  Serial.println("switch is off, and high voltage is being passed"); 
  
  delay(timeDelay);              // wait for one second
} 

