#include <Servo.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"

//Servo 
int servoPinOne = 12;
int servoPinTwo = 11;
int servoPinThree = 10;
int servoPinFour = 9;
int servoPinFive = 8;
 
Servo servo1; 
Servo servo2;  
Servo servo3;  
Servo servo4;  
Servo servo5;  
 
int servoAngle = 0;   // servo position in degrees

//Color Sensor Declerations 
// Pick analog outputs, for the UNO these three work well
// use ~560  ohm resistor between Red & Blue, ~1K for green (its brighter)
#define redpin 3
#define greenpin 5
#define bluepin 6
// for a common anode LED, connect the common pin to +5V
// for common cathode, connect the common to ground

// set to false if using a common cathode LED
#define commonAnode false

// our RGB -> eye-recognized gamma color
byte gammatable[256];

//Int's used as booleans to tigger servo action
int colorRed;
int colorBlue; 
int colorGreen;  

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
   
void setup()
{
  //Servo
  Serial.begin(9600);
  Serial.println("RGB Sensor Online, running version; 2.0.2");  
  servo5.attach(servoPinFive);
  servo4.attach(servoPinFour);
  servo3.attach(servoPinThree);
  servo2.attach(servoPinTwo);
  servo1.attach(servoPinOne);

  //Color Sensor
  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  }
   // use these three pins to drive an LED
  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
  
  // thanks PhilB for this gamma table!
  // it helps convert RGB colors to what humans see
  for (int i=0; i<256; i++) {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;
      
    if (commonAnode) {
      gammatable[i] = 255 - x;
    } else {
      gammatable[i] = x;      
    }
    //Serial.println(gammatable[i]);
  }
}
 


void loop() {
  uint16_t clear, red, green, blue;

//  tcs.setInterrupt(false);      // turn on LED

  delay(60);  // takes 50ms to read 
  
  tcs.getRawData(&red, &green, &blue, &clear);

  tcs.setInterrupt(true);  // turn off LED
  
  Serial.print("C:\t"); Serial.print(clear);
  Serial.print("\tR:\t"); Serial.print(red);
  Serial.print("\tG:\t"); Serial.print(green);
  Serial.print("\tB:\t"); Serial.print(blue);

  // Figure out some basic hex code for visualization
  uint32_t sum = clear;
  float r, g, b;
  r = red; r /= sum;
  g = green; g /= sum;
  b = blue; b /= sum;
  r *= 256; g *= 256; b *= 256;
  Serial.print("\t");
  Serial.print((int)r, HEX); Serial.print((int)g, HEX); Serial.print((int)b, HEX);
  Serial.println();

  //Serial.print((int)r ); Serial.print(" "); Serial.print((int)g);Serial.print(" ");  Serial.println((int)b );

  analogWrite(redpin, gammatable[(int)r]);
  analogWrite(greenpin, gammatable[(int)g]);                                                                                                                                                                       
  analogWrite(bluepin, gammatable[(int)b]);     
   
   if ((red > 525 && red < 780) && (green > 450 && green < 500) && (blue > 245 && blue <375)){ 
    Serial.print("RED RED RED RED RED RED RED ");
    servo5.write(90);
    delay(500);
    servo5.write(90);
    delay(500);
    servo5.write(140);
    
    return;
  }
  if ((red > 450 && red < 520) && (green > 250 && green < 445) && (blue > 450 && blue < 650)){
    Serial.print("BLUE BLUE BLUE BLUE BLUE BLUE BLUE ");
    servo4.write(135);
    delay(500);
    servo4.write(90);
    delay(500);
    servo4.write(90);
     
    return;
  }
}

//void ServoMove() { 
//  if (int colorRed = 1) {
//    servo5.write(90);
//    delay(500);
//    servo5.write(135); 
//    delay(500);
//    servo5.write(90);
//    delay(500);
//   return; 
//  }
//}


// void Test() {
//   servo1.write(90);
//   servo2.write(90);
//   servo3.write(90);
//   servo4.write(90);
//   servo5.write(90); 
//   delay(500);            // Wait 1/2 of a second
//   servo1.write(135);     // Turn the firve SG90 servos Right to 135 degrees
//   servo2.write(135);     
//   servo3.write(135);      
//   servo4.write(135);      
//   servo5.write(135); 
//   delay(500);            // Wait 1/2 of a second
//   servo1.write(90);      // Turn the five SG90 servos back to 90 degrees (center position)
//   servo2.write(90);     
//   servo3.write(90);      
//   servo4.write(90);      
//   servo5.write(90);
//   delay(500);
//   return;
//}   
//end control the servo's direction and the position of the motor 

//Control the servo's speed  
//if you change the delay value (from example change 50 to 10), the speed of the servo changes
//  for(servoAngle = 0; servoAngle < 180; servoAngle++)  //move the micro servo from 0 degrees to 180 degrees
//  {                                  
//    servo.write(servoAngle);              
//    delay(50);                  
//  }
// 
//  for(servoAngle = 180; servoAngle > 0; servoAngle--)  //now move back the micro servo from 0 degrees to 180 degrees
//  {                                
//    servo.write(servoAngle);          
//    delay(10);      
//  }
//  //end control the servo's speed  
//}
