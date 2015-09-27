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
 
int tiltPos = 20;   // variable to store the tilt servo position
int panPos = 40;    // variable to store the pan servo position

long prevTime = 0;
long delayTime;
 
void setup()
{ 
  Serial.begin(9600);
  myServoTilt.attach(3);
  myServoPan.attach(5);
} 
 
void loop()
{ 
  myServoPan.write(40); //reset servos
  myServoTilt.write(20);
  
  for(panPos = 40; panPos <= 120; panPos += 5)
  {
    myServoPan.write(panPos);
    while(tiltPos <= 120)
    {
      if ((millis() - prevTime) > 200)
      {
        Serial.println(tiltPos);
        myServoTilt.write(tiltPos);
        prevTime = millis();
        tiltPos += 5;
      }
    }
    tiltPos = 20;
    myServoTilt.write(20);
  }
}
