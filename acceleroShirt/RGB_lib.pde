void initializeRGB(void);
void color (unsigned char red, unsigned char green, unsigned char blue);
void setGradient (int low_input, int medium_input, int high_input);
void simpleColor (unsigned char sensor_value);
void cycleColors (void);

//for gradient color display
int slope1,slope2;
int cons1,cons2,cons3,cons4;
int low = 0;
int medium = 512;
int high = 1023;

int redTab = 9;                
int blueTab = 10;                
int greenTab = 11;                

void initializeRGB(void)
{
  pinMode(redTab, OUTPUT);      
  pinMode(blueTab, OUTPUT);      
  pinMode(greenTab, OUTPUT);      

  analogWrite(redTab, 0);
  analogWrite(blueTab, 0);
  analogWrite(greenTab, 0);

  setGradient(low,medium,high);
}

void color (unsigned char red, unsigned char green, unsigned char blue)
{
  analogWrite(redTab, 255-red);
  analogWrite(blueTab, 255-blue);
  analogWrite(greenTab, 255-green);
}

void cycleColors (void)
{
  unsigned char red = 255;
  unsigned char green = 0;
  unsigned char blue = 0;

  //red
  while (green < 255)
  {
    color(red, green, blue);
    delay(3);
    green++;
  }
  //yellow
  while (red > 0)
  {
    color(red, green, blue);
    delay(3);
    red--;
  }
  //green
  while (blue < 255)
  {
    color(red, green, blue);
    delay(3);
    blue++;
  }
  //cyan
  while (green > 0)
  {
    color(red, green, blue);
    delay(3);
    green--;
  }
  //blue
  while (red < 255)
  {
    color(red, green, blue);
    delay(3);
    red++;
  }
  //magenta
  while (blue > 0)
  {
    color(red, green, blue);
    delay(3);
    blue--;
  }
  //red
}

void setGradient (int low_input, int medium_input, int high_input)
{
  if (low_input >=1020)
    low_input = 1020;
  if (medium_input >=1020)
    medium_input = 1020;
  if (high_input >=1020)
    high_input = 1020;
    
  low = low_input/4;
  medium = medium_input/4;
  high = high_input/4;

  slope1 = (255/(medium-low)) * 10;
  cons1 = (low * slope1) + 2550;
  cons2 = low * slope1;
  slope2 = (255/(high-medium)) * 10;
  cons3 = (medium * slope2) + 2550;
  cons4 = medium * slope2;
}

void simpleColor (int sensor_value)
{
  int blue = 0;
  int green = 0;
  int red = 0;
  unsigned char new_sensor_value = 0;
  
  if (sensor_value <=0)
    new_sensor_value = 0;
  else if (sensor_value >=1020)
    new_sensor_value = 255;
  else
    new_sensor_value = new_sensor_value/4;

  if (new_sensor_value <= low)			
  {
    blue = 255;		
    green = 0;
    red = 0;
  }
  else if ((new_sensor_value > low) && (new_sensor_value <= (medium-5)))
  {
    blue = ((-slope1 * new_sensor_value) + cons1)/10;
    green = ((slope1 * new_sensor_value) - cons2)/10;
    red = 0;
  }
  else if ((new_sensor_value > (medium-5)) && (new_sensor_value <= (medium+5)))    //breathing room for medium transition
  {
    green = 255;
  }
  else if ((new_sensor_value > (medium+5)) && (new_sensor_value <= high))
  {
    blue = 0;
    green = ((-slope2 * new_sensor_value) + cons3)/10;
    red = ((slope2 * new_sensor_value) - cons4)/10;
  }
  else if (new_sensor_value > high)
  {
    blue = 0;
    green = 0;
    red = 255;
  }
  color(red,green,blue);
}
