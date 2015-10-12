// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

byte one[8] = {
  B00001,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B10000,
};

byte two[8] = {
  B00011,
  B00001,
  B00000,
  B00000,
  B00000,
  B00000,
  B10000,
  B11000,
};

byte three[8] = {
  B00111,
  B00011,
  B00001,
  B00000,
  B00000,
  B10000,
  B11000,
  B11100,
};

byte four[8] = {
  B01111,
  B00111,
  B00011,
  B00001,
  B10000,
  B11000,
  B11100,
  B11110,
};

byte five[8] = {
  B11111,
  B01111,
  B00111,
  B10011,
  B11001,
  B11100,
  B11110,
  B11111,
};

byte six[8] = {
  B11111,
  B01111,
  B00111,
  B10011,
  B11001,
  B11100,
  B11110,
  B11111,
};

byte seven[8] = {
  B11111,
  B11111,
  B01111,
  B10111,
  B11011,
  B11101,
  B11110,
  B11111,
};

byte eight[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
};
void setup(){

  //begin the LCD interface
  lcd.begin(20,4); 

  //create custom characters
  lcd.createChar(0, one);
  lcd.createChar(1, two);
  lcd.createChar(2, three);
  lcd.createChar(3, four);
  lcd.createChar(4, five);
  lcd.createChar(5, six);
  lcd.createChar(6, seven);
  lcd.createChar(7, eight);
}

void loop() {
  //move the cursor
  //(a,b) where a is the column and b is the row
  //(0,1): 0 is the first column and 1 is the second row 
  for (int i = 0; i < 4; i ++){
    lcd.setCursor(0,i); 
    //clear the animation
    lcd.print("                                        ");
  }

  //leg of n
  //i is across and k is rows
    for (int k = 0; k < 4; k ++){
      for (int j = 0; j < 8; j++){
        lcd.setCursor(0,k);
        lcd.write(byte(j));
        delay(100);   
      }
    }

  //across of n
  for (int i = 1; i < 3; i++){
    for (int k = 0; k < 1; k ++){
      for (int j = 0; j < 8; j++){
        lcd.setCursor(i,k);
        lcd.write(byte(j));
        delay(100);   
      }
    }
  }

  //leg of n
  for (int i = 3; i < 4; i++){
    for (int k = 0; k < 4; k ++){
      for (int j = 0; j < 8; j++){
        lcd.setCursor(i,k);
        lcd.write(byte(j));
        delay(100);   
      }
    }
  }

  //y
  for (int j = 0; j < 8; j++){
    lcd.setCursor(6,0);
    lcd.write(byte(j));
    delay(100);   
  }

  for (int j = 0; j < 8; j++){
    lcd.setCursor(7,1);
    lcd.write(byte(j));
    delay(100);   
  }

  for (int k = 2; k < 4; k++){
    for (int j = 0; j < 8; j++){
      lcd.setCursor(8,k);
      lcd.write(byte(j));
      delay(100);   
    }
  }

  for (int j = 0; j < 8; j++){
    lcd.setCursor(9,1);
    lcd.write(byte(j));
    delay(100);   
  }

  for (int j = 0; j < 8; j++){
    lcd.setCursor(10,0);
    lcd.write(byte(j));
    delay(100);   
  }

  // m

  for (int k = 0; k < 4; k ++){
    for (int j = 0; j < 8; j++){
      lcd.setCursor(13,k);
      lcd.write(byte(j));
      delay(100);   
    }
  }

  for (int i = 14; i < 16; i++){
    for (int k = 0; k < 1; k ++){
      for (int j = 0; j < 8; j++){
        lcd.setCursor(i,k);
        lcd.write(byte(j));
        delay(100);   
      }
    }
  }

  for (int k = 0; k < 4; k ++){
    for (int j = 0; j < 8; j++){
      lcd.setCursor(16,k);
      lcd.write(byte(j));
      delay(100);   
    }
  }

  for (int i = 17; i < 19; i++){
    for (int k = 0; k < 1; k ++){
      for (int j = 0; j < 8; j++){
        lcd.setCursor(i,k);
        lcd.write(byte(j));
        delay(100);   
      }
    }
  }
  
    for (int k = 0; k < 4; k ++){
    for (int j = 0; j < 8; j++){
      lcd.setCursor(19,k);
      lcd.write(byte(j));
      delay(100);   
    }
  }

}








