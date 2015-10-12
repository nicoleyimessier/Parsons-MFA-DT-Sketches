//gadgiTeration Code 2014
//Joselyn McDonald & Nicole Messier

//Code uses a button and state changes to rotate through a number of different songs

//library that holdes the notes that are used in the various songs
#include "pitches.h"

const int pushButton1 = 13; //digital pin of button1
const int pushButton2 = 12; //digital pin of button2
const int speaker = 9; //digital pin that the speaker is attached to


int buttonState1=0; //variable assigned as the current state of button1
int lastButtonState1=0; //previous state of button1
int buttonPushCounter1 = 0; //counter for the number of button presses on button1
int buttonState2=0; //variable assigned as the current state of button2
int lastButtonState2=0; //previous state of button2
int buttonPushCounter2 = 0; //counter for the number of button presses on button2
int song=0; //counter for the song
int songStorage=0; //variable to store song value

void setup(){
  //initialize the serial port
  Serial.begin(9600);
  //initialize speaker as an output
  pinMode(speaker,OUTPUT);
  //initialize pushbutton1 as an input
  pinMode(pushButton1, INPUT); 
  //initialize pushbutton2 as an input
  pinMode(pushButton2, INPUT); 
}

void loop(){

  //set buttonState variables to the state of the buttons (high or low which is 1 or 1)
  buttonState1 = digitalRead(pushButton1);
  buttonState2 = digitalRead(pushButton2);
  //Serial print the song, buttonState, and buttonPushCounter variables for debugging
  Serial.print("song: ");  
  Serial.print(song);
  Serial.print(", ");
  Serial.print("\t");
  Serial.print("songStorage: ");  
  Serial.println(songStorage);
  //button1 variables print out on one line  
  Serial.print("buttonState1: "); 
  Serial.print(buttonState1);
  Serial.print(", ");
  Serial.print("\t"); 
  Serial.print("buttonPushCounter1: "); 
  Serial.println(buttonPushCounter1);
  //button2 variables print out on another line 
  Serial.print("buttonState2: "); 
  Serial.print(buttonState2);
  Serial.print(", ");
  Serial.print("\t"); 
  Serial.print("buttonPushCounter2: "); 
  Serial.println(buttonPushCounter2);
  Serial.println();
  delay(10);

  //compare the buttonStates to its previous state
  if (buttonState1 != lastButtonState1){
    // if the state has changed, increment the counter
    buttonPushCounter1++;
    song++;    

    // check if song is equal to 0    
    if(song==0){
      //play overworld song    
      noTone(speaker);    
    }        


    // check if song is equal to 1    
    if(song==1){
      //play overworld song    
      overworld();    
    }        


    // check if song is equal to 2     
    if (song == 2){
      //play songOfStorms song        
      songOfStorms();
    }


    // check if song is equal to 3
    if (song == 3){
      //play windFish song          
      windFish();
      // set song equal to zero to reshuffle through songs
     
    }
    
    //reset song loop
    if (song == 4){
     song = 1;  
    }
  }
  
  //set the song number to the songStorage value to store this as the chosen song
  songStorage = song;

  //compare the buttonStates to its previous state
  if (buttonState2 != lastButtonState2){
    buttonPushCounter2++;

    if(songStorage==0){
      //play overworld song    
       noTone(speaker); 
    }        

    // check if song is equal to 1     
    if (songStorage == 1){
      //play songOfStorms song        
      overworld();
    }


    // check if song is equal to 2
    if (songStorage == 2){
      //play windFish song          
      songOfStorms();
    }
    
    // check if song is equal to 3
    if (songStorage == 3){
      //play windFish song          
      windFish();
    }

  }

}

void windFish (){
  tone(speaker, NOTE_D5);
  delay(400);
  tone(speaker, NOTE_E5);
  delay(400);
  tone(speaker, NOTE_F5);
  delay(1400);
  tone(speaker, NOTE_D5);
  delay(400);
  tone(speaker, NOTE_E5);
  delay(400);
  tone(speaker, NOTE_F5);
  delay(1400);
  tone(speaker, NOTE_E5);
  delay(400);
  tone(speaker, NOTE_D5);
  delay(400);
  tone(speaker, NOTE_A4);
  delay(400);
  tone(speaker, NOTE_C5);
  delay(800);
  tone(speaker, NOTE_D5);
  delay(1000);
  noTone(speaker); 
}

void songOfStorms (){
  tone(speaker, NOTE_D4);
  delay(200);
  tone(speaker, NOTE_F4);
  delay(200);
  tone(speaker, NOTE_D5);
  delay(600);
  noTone(speaker);
  delay(50);
  tone(speaker, NOTE_D4);
  delay(200);
  tone(speaker, NOTE_F4);
  delay(200);
  tone(speaker, NOTE_D5);
  delay(600);
  noTone(speaker);
  delay(50);
  tone(speaker, NOTE_E5);
  delay(600);
  tone(speaker, NOTE_F5);
  delay(200);
  tone(speaker, NOTE_E5);
  delay(200);
  tone(speaker, NOTE_F5);
  delay(200);
  tone(speaker, NOTE_E5);
  delay(200);
  tone(speaker, NOTE_C5);
  delay(200);
  tone(speaker, NOTE_A4);
  delay(600);
  noTone(speaker);
  delay(50);
  noTone(speaker); 
}

void overworld(){
  tone(speaker, NOTE_A4);
  delay(400);
  tone(speaker, NOTE_E4);
  delay(800);
  tone(speaker, NOTE_A4);
  delay(150);
  noTone(speaker);
  delay(10);
  tone(speaker, NOTE_A4);
  delay(150);
  tone(speaker, NOTE_B4);
  delay(150);
  tone(speaker, NOTE_C5);
  delay(150);
  tone(speaker, NOTE_D5);
  delay(150);
  tone(speaker, NOTE_E5);
  delay(800);
  noTone(speaker); 
}





