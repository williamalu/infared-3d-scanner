/* Sweep
 by BARRAGAN <http://barraganstudio.com> 
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://arduino.cc/en/Tutorial/Sweep

 modified 22 Sept 2015
 by William Lu, Shruti Iyer, Aaron Greiner
*/ 

#include <Servo.h> 
 
Servo myServoTilt; // create servo object for tilt servo 
Servo myServoPan;  // create servo object for pan servo
 
int tiltPos = 0;   // variable to store the tilt servo position
int panPos = 0;    // variable to store the pan servo position

long time;
 
void setup()
{ 
  Serial.begin(9600);
  myServoTilt.attach(3);
  myServoPan.attach(5);
} 
 
void loop()
{ 
  for(panPos = 0; panPos <= 180; panPos += 5)
  {
    myServoPan.write(panPos);
      for(tiltPos = 0; tiltPos <= 180; tiltPos += 5)
      {
        myServoTilt.write(tiltPos);
        Serial.println(panPos);//theta
        Serial.println(tiltPos);//phi
        delay(200);
      }
      for(tiltPos = 180; tiltPos >= 0; tiltPos -= 5)
      {
        myServoTilt.write(tiltPos);
        Serial.println(panPos);//theta
        Serial.println(tiltPos);//phi
        delay(200);
      }
    delay(200);
  }
  
  for(panPos = 180; panPos >= 0; panPos -= 1) // goes from 180 degrees to 0 degrees 
  {                                
    myServoPan.write(panPos);              // tell servo to go to position in variable 'pos' 
    Serial.println(panPos);//theta
    Serial.println(tiltPos);//phi
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
} 
