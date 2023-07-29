#include<ESP32Servo.h>
int Pot1 = 25;
int Pot2 = 26;
int Pot3 = 32;
int joyX = 34;
int aRead, bRead, cRead, joyVal;
Servo sv1,sv2,sv3,sv4;

void setup() {
  sv1.attach(17);
  sv2.attach(18);
  sv3.attach(19);
  sv4.attach(22);
 
}

void loop() {

  aRead = analogRead(Pot1);
  aRead = ((180./4095.)*aRead);
  sv1.write(aRead);

  bRead = analogRead(Pot2);
  bRead = ((180./4095.)*bRead);
  sv2.write(bRead);

  cRead = analogRead(Pot3);
  cRead = ((180./4095.)*cRead);
  sv3.write(cRead);

  joyVal = analogRead(joyX);
  joyVal = ((90./4095.)*joyVal);
  sv4.write(joyVal);
  
}
