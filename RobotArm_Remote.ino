#include <ESP32Servo.h>
#include <IRremote.h>

int t = 1000; //Delay
int irPin = 15; //Save and Play buttons
int save1, save2; //Save variabe
bool playPast = false, playPres = false; //Play variables for toggle button
bool saveMode1 = false, saveMode2 = false, playMode = false; //Mode for saving and play
int Aspeed = 20, Bspeed = 20;

//A
int Apos1, Apos2, Apos3, Apos4;
int AstartPos1, AstartPos2, AstartPos3, AstartPos4;
//B
int Bpos1, Bpos2, Bpos3, Bpos4;
int BstartPos1, BstartPos2, BstartPos3, BstartPos4;

int pos4, pos5, pos6, pos7;

//Servo 1
int Pot1 = 25;
float aRead = 0, AsavePos1 = 0, BsavePos1= 0;
Servo sv1;

//Servo 2
int Pot2 = 26;
float bRead = 0, AsavePos2 = 0, BsavePos2 = 0;
Servo sv2;

//Servo 3
int Pot3 = 32;
float cRead = 0, AsavePos3 = 0, BsavePos3 = 0;
Servo sv3;

//Servo 4
int joyX = 34;
float joyVal = 0, AsavePos4 = 0, BsavePos4 = 0;
Servo sv4;

void setup() {
  //put your setup code here, to run once:
  //pinMode(savePb1, INPUT_PULLUP);
  //pinMode(savePb2, INPUT_PULLUP);
  //pinMode(playPb, INPUT_PULLUP);
  Serial.begin(9600);
  IrReceiver.begin(irPin, ENABLE_LED_FEEDBACK);

  //Servo1
  sv1.attach(17);
  sv1.write(aRead);

  //Servo2
  sv2.attach(18);
  sv2.write(bRead);

  //Servo3
  sv3.attach(19);
  sv3.write(cRead);

  //Servo4
  sv4.attach(22);
  sv4.write(joyVal);
}

void loop() {
  //IR Receiver
  if (IrReceiver.decode()) {
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    {
    if (IrReceiver.decodedIRData.decodedRawData == 0xBA45FF00) {
      Serial.println("Save 1");
      saved_1();
    }
    if (IrReceiver.decodedIRData.decodedRawData == 0xB946FF00) {
      Serial.println("Save 2");
      saved_2();
    }
    if (IrReceiver.decodedIRData.decodedRawData == 0xB847FF00) {
      Serial.println("Play");
      played();
    }
  } 
}
  IrReceiver.resume();

  //Servo1
  aRead = analogRead(Pot1);
  aRead = ((180./4095.)*aRead);
  sv1.write(aRead);

  //Servo2
  bRead = analogRead(Pot2);
  bRead = (180./4095.)*bRead;
  sv2.write(bRead);

  //Servo3
  cRead = analogRead(Pot3);
  cRead = (180./4095.)*cRead;
  sv3.write(cRead);

  //Servo4
  joyVal = analogRead(joyX);
  //serPos4 = (90./4095.)*(Val4-207)
  if(joyVal <= 3000 )
  {
    joyVal = 60;
    sv4.write(joyVal);
    //Serial.println(Val4)
    //delay(t);
  }
  else if(joyVal >= 3200)
  {
    joyVal = 10;
    sv4.write(joyVal);
    //Serial.println(Val4);
    //delay(t);
  }
}

void saved_1()
{
  //Save position
  //save1 = digitalRead(savePb1);
  saveMode1 = true;
  AsavePos1 = aRead;
  AsavePos2 = bRead;
  AsavePos3 = cRead;
  AsavePos4 = joyVal;

  delay(t);
  Serial.print("AsavePos1 = ");
  Serial.println(AsavePos1);
  Serial.println();
  Serial.print("AsavePos2 = ");
  Serial.println(AsavePos2);
  Serial.println();
  Serial.print("AsavePos3 = ");
  Serial.println(AsavePos3);
  Serial.println();
  Serial.print("AsavePos4 = ");
  Serial.println(AsavePos4);
  Serial.println();
  
}

void saved_2()
{
  //Save position
  //save2 = digitalRead(savePb2);
  //if(save2 == LOW)
  saveMode2 = true;
  BsavePos1 = aRead;
  BsavePos2 = bRead;
  BsavePos3 = cRead;
  BsavePos4 = joyVal;

  delay(t);
  Serial.print("BsavePos1 = ");
  Serial.println(BsavePos1);
  Serial.println();
  Serial.print("BsavePos2 = ");
  Serial.println(BsavePos2);
  Serial.println();
  Serial.print("BsavePos3 = ");
  Serial.println(BsavePos3);
  Serial.println();
  Serial.print("BsavePos4 = ");
  Serial.println(BsavePos4);
  Serial.println();
  
}

void played()
{
  
  saveMode1 = false;
  saveMode2 = false;
  playMode = true;

  while(playMode == true){
    //A
    //Servo1
      AstartPos1 = sv1.read();
    for(Apos1 = AstartPos1; Apos1 <= AsavePos1; Apos1 += Aspeed)
    {
      sv1.write(Apos1);
      delay(500);
    }
    //Servo2
    AstartPos2 = sv2.read();
    for(Apos2 = AstartPos2; Apos2 <= AsavePos2; Apos2 += Aspeed)
    {
      sv2.write(Apos2);
      delay(500);
    }
    AstartPos3 = sv3.read();
    for(Apos3 = AstartPos3; Apos3 <= AsavePos3; Apos3 += Aspeed)
    {
      sv3.write(Apos3);
      delay(500);
    }
    AstartPos4 = sv4.read();
    for(Apos4 = AstartPos4; Apos4 <= AsavePos4; Apos4 += Aspeed)
    {
      sv4.write(Apos4);
      delay(500);
    }

    //B
    //Servo1
    BstartPos1 = sv1.read();
    for(Bpos1 = BstartPos1; Bpos1 <= BsavePos1; Bpos1 += Bspeed)
    {
      sv1.write(Bpos1);
      delay(500);
    }
    //Servo2
    BstartPos2 = sv2.read();
    for(Bpos2 = BstartPos2; Bpos2 <= BsavePos2; Bpos2 += Bspeed)
    {
      sv2.write(Bpos2);
      delay(500);
    }
    BstartPos3 = sv3.read();
    for(Bpos3 = BstartPos3; Bpos3 <= BsavePos3; Bpos3 += Bspeed)
    {
      sv3.write(Bpos3);
      delay(500);
    }
    BstartPos4 = sv4.read();
    for(Bpos4 = BstartPos4; Bpos4 <= BsavePos4; Bpos4 += Bspeed)
    {
      sv4.write(Bpos4);
      delay(500);
    }

    //pos4, pos5, pos6, pos7
    //Servo1
    for(pos4 = Bpos1; pos4 >= AstartPos1; pos4 -= Aspeed)
    {
      sv1.write(pos4);
      delay(500);
    }
    //Servo2
    for(pos5 = Bpos2; pos5 >= AstartPos2; pos5 -= Aspeed)
    {
      sv2.write(pos5);
      delay(500);
    }

    for(pos6 = Bpos3; pos6 >= AstartPos3; pos6 -= Aspeed)
    {
      sv3.write(pos6);
      delay(500);
    }

    for(pos7 = Bpos4; pos7 >= AstartPos4; pos7 -= Aspeed)
    {
      sv4.write(pos7);
      delay(500);
    }
  }
}
