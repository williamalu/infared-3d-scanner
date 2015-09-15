/* 
 Controlling a servo position using an infrared sensorr (variable resistor) 
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott> 

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h> 
 
Servo myservo1;  // create servo object to control a servo
Servo myservo2; //Second servo
 
int infraVal = 0;  // analog pin used to connect the infra sensor
int val;    // variable to read the value from the analog pin 
 
void setup() 
{ 
  myservo.attach(3);  // attaches the servo on pin 3 to the servo object 
  myservo.attach(5);  // attaches the servo on pin 5 to the servo object 
} 
 
void loop() 
{ 
  val = analogRead(infraVal);            // reads the value of the potentiometer (value between 0 and 1023) 
  val = map(val, 60, 700, 0, 180);     // scale it to use it with the servo (value between 0 and 180) 
  myservo1.write(val);                  // sets the servo position according to the scaled value 
  myservo2.write(val);                  // sets the servo position according to the scaled value 
  delay(15); 
} 
