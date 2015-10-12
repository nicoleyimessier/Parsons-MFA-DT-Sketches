int motorPin = 8;
int button = 2;
int state = HIGH;
int previous = LOW;
long time = 0;
long debounce = 0;
int motorSpeed;

 
void setup() 
{ 
  pinMode(motorPin, OUTPUT);
  pinMode(button, INPUT);
  Serial.begin(9600);
} 
 
 
void loop() {
    reading = digitalRead(button);  
   
   if (reading==HIGH && previous==LOW && millis() - time > debounce){
    if (state == HIGH)
       state=LOW;
       motorSpeed = 0;
      else
       state=HIGH;
       motorSpeed=255;
      time = millis(); 
   }
    
    analogWrite(motorPin, motorSpeed); 
    
    previous = reading; 
}
