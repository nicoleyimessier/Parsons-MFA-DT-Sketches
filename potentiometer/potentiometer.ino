int speaker=9;
int potPin=A0;
int potValue = 0;
int mappedValue;

void setup(){
  pinMode(speaker, OUTPUT); 
  pinMode(potPin, INPUT);

  //opening the serial connection
  //9600 is the bod rate; it's the rate at which you send info.
  //this number is the standard unless you are using bluetooth
  Serial.begin(9600);
}

void loop(){

  potValue = analogRead(potPin);
  mappedValue = map(potValue, 0, 1023, 0, 2000);

  //use the serial connection to print the outputs
  //Serial.println(potValue);

  tone(speaker, mappedValue);
  
  //delay(50);
}

