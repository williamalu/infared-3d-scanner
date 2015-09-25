#include <Servo.h> 
 
Servo myServoTilt; // create servo object for tilt servo 
Servo myServoPan;  // create servo object for pan servo
 
int tiltPos = 0;   // variable to store the tilt servo position
int panPos = 0;    // variable to store the pan servo position

long time;
int val;
int caliDist;
 
void setup()
{ 
  Serial.begin(9600);
  myServoTilt.attach(3);
  myServoPan.attach(5);
  myServoTilt.write(0);
  myServoPan.write(0);
} 
 
void loop(){
  tilt1();
  pan();
  tilt2();
  pan();
  if(panPos == 180){
    Serial.println("AWS");
  }
}

void tilt1(){
  for(tiltPos = 0; tiltPos <= 180; tiltPos += 5)
      {
        myServoTilt.write(tiltPos);
        caliDist = distanceConv();
        Serial.print(tiltPos);Serial.print(" ");Serial.println(panPos);Serial.print(" ");Serial.println(caliDist);
        delay(20);
      }
}
void tilt2(){
  for(tiltPos = 180; tiltPos >= 0; tiltPos -= 5)
      {
        myServoTilt.write(tiltPos);
        Serial.print(tiltPos);Serial.print(" ");Serial.println(panPos);Serial.print(" ");Serial.println(caliDist);
        delay(20);
      }
}
void pan(){
  panPos += 5;
  myServoPan.write(panPos);
  delay(20);
}

int distanceConv()
{
  int out[] = {60,55,50,45,40,35,30,25,20,15};//out is the cm
  // note: the in array should have increasing values
  int in[]  = {217,237,257,289,317,360,407,470,514,561};
  
  val = analogRead(A0);
  return multiMap(val, in, out, 10);
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
