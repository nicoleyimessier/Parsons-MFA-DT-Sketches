const int xPin = A1;     // X output of the accelerometer
const int yPin = A0; // Y output of the accelerometer
int redLEDpin = 7;
int Y;
int Y2;
int X;
int yDelta;


void setup() {
  // initialize serial communications:
  Serial.begin(9600);
  // initialize the pins connected to the accelerometer
  // as inputs:
  pinMode(redLEDpin, OUTPUT);

}

void loop() {
  // variables to read the pulse widths:
  int pulseX, pulseY;
  // variables to contain the resulting accelerations
  int accelerationX, accelerationY;
  Y=analogRead(A0);
  delay(1000);
  Y2=analogRead(A0);
  X=analogRead(A1);
  yDelta = Y2 - Y;

  Serial.print("Y= ");
  Serial.print(Y);
  Serial.print(" Y2= ");
  Serial.print(Y2);
  Serial.print(" yDelta= ");
  Serial.print(yDelta);
  Serial.print(" X= ");
  Serial.println(X);
  
    if (yDelta > -5 && yDelta < 5){
    digitalWrite(redLEDpin, HIGH); 
  }
  else{
    digitalWrite(redLEDpin, LOW); 

  } 

//  if (yDelta > -5 || yDelta < 5){
//    digitalWrite(redLEDpin, LOW); 
//  }
//  else{
//    digitalWrite(redLEDpin, LOW); 
//
//  } 

}

