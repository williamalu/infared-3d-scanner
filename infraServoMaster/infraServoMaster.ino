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
 
int tiltPos = 60;   // variable to store the tilt servo position
int panPos = 40;    // variable to store the pan servo position

int val;
int caliDist;

long prevTime = 0;
long delayTime;
 
void setup()
{ 
  delay(400);
  Serial.begin(250000);
  myServoTilt.attach(3);
  myServoPan.attach(5);
  
  myServoPan.write(panPos); //reset servos
  myServoTilt.write(tiltPos);
} 
 
void loop()
{ 
  for(panPos = 40; panPos <= 110; panPos += 1)
  {
    myServoPan.write(panPos);
    while(tiltPos <= 120)
    {
      if ((millis() - prevTime) > 200)
      {
        myServoTilt.write(tiltPos);
        caliDist = distanceConv();
        Serial.print(tiltPos);Serial.print(" ");Serial.print(panPos);Serial.print(" ");Serial.println(caliDist);
        prevTime = millis();
        tiltPos += 1;
      }
    }
    tiltPos = 60;
    myServoTilt.write(tiltPos);
    if(panPos == 110)
    {
      Serial.println("AWS");
    }
  }
}

int distanceConv()
{
  int out[] = {170,160,150,140,130,120,110,100,90,80,70,60,55,50,45,40,35,30,25,20,15};//out is the cm
  // note: the in array should have increasing values
  int in[]  = {67,71,76,85,92,113,121,132,148,165,185,217,237,257,289,317,360,407,470,514,561};
  
  val = analogRead(A0);
  return multiMap(val, in, out, 21);
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
