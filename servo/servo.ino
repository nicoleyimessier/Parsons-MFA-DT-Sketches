#include <Servo.h> 

int servoPin = 9;
int servoPinTwo = 8;

Servo servo;
Servo servoTwo;

int angle = 0;   // servo position in degrees 

void setup() 
{ 
  servo.attach(servoPin);
  servoTwo.attach(servoPinTwo); 
} 


void loop() 
{ 
  // scan from 0 to 180 degrees
  for(angle = 0; angle < 180; angle++)  
  {                                  
    servo.write(angle);               
    delay(15);

    servoTwo.write(angle);               
    delay(15);       
  } 
  // now scan back from 180 to 0 degrees
  for(angle = 180; angle > 0; angle--)    
  {                                
    servo.write(angle);           
    delay(15);
    
    servoTwo.write(angle);               
    delay(15);       
  } 
} 



