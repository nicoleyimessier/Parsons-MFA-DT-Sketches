int motorPin = 8;
 
void setup() 
{ 
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
} 
 
 
void loop() 
{ 
    int motorSpeed = 135;
    analogWrite(motorPin, motorSpeed); 
}
