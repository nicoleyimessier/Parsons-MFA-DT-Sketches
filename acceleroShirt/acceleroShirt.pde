/*
 * LilyPad example project
 *
 * Uses an accelerometer to control the
 * color of an RGB LED
 */

int sensorValue;                   //variable to hold accelerometer data
int accelero = 5;                  //analogue pin that acclerometer is tied to

void setup() {
  Serial.begin(9600);               //initialize the serial port so that you can communicate with the computer
  initializeRGB();                  //initialize the RGB LED pins and color (see RGB_lib)
  setGradient(230,320,390);         //set gradient (see RGB_lib)
                                    // 1st number is the lowest value you get from your sensor
                                    // 2nd is approximate midpoint
                                    // 3rd is highest value you get from your sensor
}

void loop() {
  sensorValue = analogRead(accelero);        // read accelereometer data
  //Serial.println(sensorValue);               // send the sensor data to the computer so you can calibrate RGB LED display
  //delay(100);                                // delay so computer can display data
                                             // NOTE: remove the delay for your final version
                                             // once you've figured out what your gradient values are
                                             // this will make your color transitions nice & smooth
  simpleColor(sensorValue);                  // display sensor value in the RGB LED (see RGB_lib)
}
