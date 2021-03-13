#include<LiquidCrystal.h>
#include<Wire.h>
#include<Servo.h>
#include<IRremote.h>
#define L1 12
#define L2 10
#define L3 9
#define L4 6
#define L5 5
#define IR 2
#define GDR 3
#define TRIG A1
#define ECHO A0

Servo GDoor;
IRrecv Remote(IR);
decode_results results;

int val;
bool D1 = true;
bool D2 = true;
bool D3 = true;
bool D4 = true;
bool D5 = true;
bool D6;
bool D7;
bool D8;
void setup() {
  Serial.begin(9600);
  Wire.begin(3);
  Wire.onReceive(receiveEvent);
  Remote.enableIRIn();
  GDoor.attach(GDR);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(L3, OUTPUT);
  pinMode(L4, OUTPUT);
  pinMode(L5, OUTPUT);
  GDoor.write(0);
}
void receiveEvent(int bytes){
  val = Wire.read();
}

void loop() {
  if(Remote.decode(&results)){
    Serial.println(results.value, HEX);
    switch(results.value){
      case 0xFD08F7:
        D1 =! D1;
      break ;
      case 0xFD8877:
        D2 =! D2;
      break ;
      case 0xFD48B7:
        D3 =! D3;
      break ;
      case 0xFD28D7:
        D4 =! D4;
      break ;
      case 0xFDA857:
        D5 =! D5;
      break ;
      case 0xFD6897:
        D6 =! D6;
      break ;
      case 0xFD18E7:
        D7 =! D7;
      break ;
      case 0xFD9867:
        D8 =! D8;
      break ; 
    }
    Remote.resume();
  }
  if(D1)
    analogWrite(L1, val);
  else
    analogWrite(L1, 0);
  if(D2)
    analogWrite(L2, val);
  else
    analogWrite(L2, 0); 
  if(D3)
    analogWrite(L3, val);
  else
    analogWrite(L3, 0);
  if(D4)
    analogWrite(L4, val);
  else
    analogWrite(L4, 0);
  if(D5)
    analogWrite(L5, val);
  else
    analogWrite(L5, 0);
  if(D6){
    turnof();
    delay(50);
    off(L1);
    off(L2);
    off(L3);
    off(L4);
    off(L5);
    off(L4);
    off(L3);
    off(L2);
    off(L1);
  }
  if(D7){
    turnof();
    delay(50);
    digitalWrite(L1, 1);
    digitalWrite(L3, 1);
    digitalWrite(L5, 1);
    delay(50);
    digitalWrite(L1, 0);
    digitalWrite(L3, 0);
    digitalWrite(L5, 0);
    digitalWrite(L2, 1);
    digitalWrite(L4, 1);
    delay(50);
    digitalWrite(L2, 0);
    digitalWrite(L4, 0);
  }
  if(D8){
    turnof();
    delay(50);
    digitalWrite(L1, 1);
    digitalWrite(L5, 1);
    delay(50);
    digitalWrite(L2, 1);
    digitalWrite(L4, 1);
    delay(50);
    digitalWrite(L3, 1);
    delay(50);
    digitalWrite(L1, 0);
    digitalWrite(L5, 0);
    delay(50);
    digitalWrite(L2, 0);
    digitalWrite(L4, 0);
    delay(50);
    digitalWrite(L3, 0);
    delay(50);
  }
  float dis = DisCal();
  if(dis < 15 && dis > 0){
    GDoor.write(180);
    delay(1500);
    GDoor.write(0);
  }
}

void off(int pin){
  digitalWrite(pin, 1);
  delay(50);
  digitalWrite(pin, 0);
}
void turnof(){
  digitalWrite(L1, 0);
  digitalWrite(L2, 0);
  digitalWrite(L3, 0);
  digitalWrite(L4, 0);
  digitalWrite(L5, 0);
}

float DisCal(){
  digitalWrite(TRIG, 0);
  delayMicroseconds(5);
  digitalWrite(TRIG, 1);
  delayMicroseconds(5);
  digitalWrite(TRIG, 0);
  float time = pulseIn(ECHO, 1);
  return time/29/2;
}
