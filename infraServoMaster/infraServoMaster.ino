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
 
int tiltPos = 60; // variable to store the tilt servo position
int panPos = 40;  // variable to store the pan servo position

int tiltPosMax = 110; // variable to store the Max tilt servo position
int panPosMax = 40;  // variable to store the Max pan servo position

int val; //Analog read from the distance sensor
int caliDist; //Calibrated distance from the mapping function

long prevTime = 0; //Previous time is the last time the servo was tilted 
 
void setup()
{ 
  delay(400); //Buffer time for the communication between MATLAB and Arduino
  Serial.begin(250000); //Setting up the Serial Port with the Baud rate
  myServoTilt.attach(3); //Attacj=hing the Tilt servo
  myServoPan.attach(5); //Attaching the Pan servo
  
  //reset servos
  myServoPan.write(panPos); 
  myServoTilt.write(tiltPos);
} 
 
void loop()
{ 
  for(panPos = 40; panPos <= panPosMax; panPos += 1) //From min to max for the pan servo
  {
    myServoPan.write(panPos);
    while(tiltPos <= tiltPosMax)
    {
      if ((millis() - prevTime) > 200)
      {
        myServoTilt.write(tiltPos);
        caliDist = distanceConv(); //Calibrated distance
        //Serial Print the tilt angle, pan angle and the distance with spaces in between
        Serial.print(tiltPos);Serial.print(" ");Serial.print(panPos);
        Serial.print(" ");Serial.println(caliDist);
        prevTime = millis();
        tiltPos += 1;
      }
    }
    tiltPos = 60; //Resetting the servo after the vertical sweep
    myServoTilt.write(tiltPos);
    if(panPos == panPosMax) //If it reached the end, print string to indicate the end
    {
      Serial.println("AWS");
    }
  }
}

int distanceConv(){
//This function uses the interpolation function the integer using the 
//calibrated distances and the corresponding values

  int out[] = {170,160,150,140,130,120,110,100,90,80,70,60,55,50,
                45,40,35,30,25,20,15};//out is the distance in cm
  
  int in[]  = {67,71,76,85,92,113,121,132,148,165,185,217,237,257,
                289,317,360,407,470,514,561}; // Analog A0 output
  
  val = analogRead(A0); //Reading from A0 (Distance sensor)
  return multiMap(val, in, out, 21); //Calls the map function
}

int multiMap(int val, int* _in, int* _out, uint8_t size)
{
  //Extreme cases for the value
  if (val <= _in[0]) return _out[0]; 
  if (val >= _in[size-1]) return _out[size-1];

  // search right interval
  uint8_t pos = 1;  // _in[0] allready tested
  while(val > _in[pos]) pos++;

  // this will handle all exact "points" in the _in array
  if (val == _in[pos]) return _out[pos];

  // interpolate in the right segment for the rest
  return (val - _in[pos-1]) * (_out[pos] - _out[pos-1]) / 
          (_in[pos] - _in[pos-1]) + _out[pos-1];
}
