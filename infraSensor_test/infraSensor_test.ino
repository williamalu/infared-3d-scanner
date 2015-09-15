void setup(){
  Serial.begin(9600);
}

void loop() {
  int infraSensor = analogRead(A0);
  Serial.print(infraSensor);
}
