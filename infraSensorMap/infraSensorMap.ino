/* 
 Controlling a servo position using an infrared sensorr (variable resistor) 
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott> 

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h> 

Servo myservo;
int val;    // variable to read the value from the analog pin 
 
void setup() 
{ 
  Serial.begin(9600);
  myservo.attach(3);  // attaches the servo on pin 3 to the servo object 
} 
 
void loop() 
{ 
  int out[] = {170,160,150,140,130,120,110,100,90,80,70,60,55,50,45,40,35,30,25,20,15};//out is the cm
  // note: the in array should have increasing values
  int in[]  = {67,71,76,85,92,113,121,132,148,165,185,217,237,257,289,317,360,407,470,514,561};
  
  val = analogRead(A0);
  int distanceConv = multiMap(val, in, out, 21);
  
  //Serial.println(val);
  Serial.println(distanceConv);
  delay(100);
  //myservo.write(servoPos);                  // sets the servo position according to the scaled value 
  
}

int multiMap(int val, int* _in, int* _out, uint8_t size)
{
  if (val <= _in[0]) return _out[0];
  if (val >= _in[size-1]) return _out[size-1];

  // search right interval
  uint8_t pos = 1;  // _in[0] allready tested
  while(val > _in[pos]) pos++;

  // this will handle all exact "points" in the _in array
  if (val == _in[pos]) return _out[pos];

  // interpolate in the right segment for the rest
  return (val - _in[pos-1]) * (_out[pos] - _out[pos-1]) / (_in[pos] - _in[pos-1]) + _out[pos-1];
}
