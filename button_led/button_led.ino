int ledPin=9;
int buttonPin=3;

void setup(){
 pinMode(ledPin, OUTPUT); 
 pinMode(buttonPin, INPUT);
}

void loop(){
 
  
  //button
  if(digitalRead(buttonPin) == HIGH){
    digitalWrite(ledPin, HIGH);
  }
  else{
  digitalWrite(ledPin, LOW);  
  }
  
  
//  //sending high voltage (i.e. 5 volts) to pin 13
//  digitalWrite(ledPin, HIGH);
//  //delaying for 1000 miliseconds
//  delay(1000);
//  digitalWrite(ledPin, LOW);
//  delay(1000);
}
