#include<LiquidCrystal.h>
#include<Wire.h>
#include<Servo.h>

#define RS 13
#define EN 12
#define D4 11
#define D5 10
#define D6 9
#define D7 8
#define HDR 7
#define B1 6
#define B2 5
#define B3 4
#define FAN 3
#define LDR A3
#define LM35 A2

LiquidCrystal Screen(RS, EN, D4, D5, D6, D7);
Servo HDoor;

byte deg[8] = {
  B01110,
  B01010,
  B01110,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
  };
bool opened;
bool pattern[3][4];
void setup() {
  Serial.begin(9600);
  Wire.begin();
  HDoor.attach(HDR);
  Screen.begin(16, 2);
  Screen.createChar(1, deg);
  pinMode(B1, INPUT);
  pinMode(B2, INPUT);
  pinMode(B3, INPUT);
  pinMode(FAN, OUTPUT);
  pinMode(2, OUTPUT);
  Screen.setCursor(0,0);
  Screen.print("*Enter  Pattern*");
  HDoor.write(0);
}

void loop() {
  if(opened){
  if(Temp() > 45)
    digitalWrite(FAN, HIGH);
  else
    digitalWrite(FAN, LOW);
  Lights();
  }else{
    for(int j = 0; j < 3; j++)
      for(int k = 0; k < 4; k++)
          pattern[j][k] = 0;
    int i = 0;
    Screen.setCursor(6,1);
    while(i != 4){
      if(digitalRead(B1)){
        pattern[0][i] = 1;
        i++;
        delay(150);
        Screen.print('$');
      }
      else if (digitalRead(B2)){
        pattern[1][i] = 1;
        i++;
        delay(150);
        Screen.print('$');
      }
      else if (digitalRead(B3)){
        pattern[2][i] = 1;
        i++;
        delay(150);
        Screen.print('$');
      }
    }
    if((pattern[0][0] && pattern[2][1]) && (pattern[2][2] && pattern[1][3]))
      opened = true;
    if(opened){
      digitalWrite(2, 0);
      Screen.clear();
      Screen.setCursor(0, 0);
      Screen.print("Correct Pattern");
      delay(300);
      Screen.clear();
      Screen.setCursor(0, 0);
      Screen.print("Welcome Mr Drako");
      HDoor.write(180);
      delay(1500);
      HDoor.write(0);
      Screen.clear();
    }else{
      Screen.clear();
      Screen.setCursor(0, 0);
      Screen.print(" Wrong Pattern");
      delay(200);
      Screen.clear();
      Screen.setCursor(0, 0);
      Screen.print("Alarm Triggered");
      digitalWrite(2, 1);
      Screen.setCursor(0,1);
      Screen.print("*Enter  Pattern*");
      delay(800);
      Screen.setCursor(0,1);
      Screen.print("                ");
      
      
    }
  }
}

float Temp(){
  int val = analogRead(LM35);
  float cl = (val /1023.0) * 5.0;
  cl = ((cl - 0.5) * 1000) / 10;
  Screen.setCursor(0, 0);
  Screen.print("Temp : ");
  Screen.print(cl);
  Screen.write(1);
  if(cl < 100 || cl > 0)
    Screen.print(" ");
  return cl;
}

void Lights(){
  float val = (analogRead(LDR) / 1023.0) * 5000;
  int value = map(val, 1681, 4970, 0, 255);
  if(value < 45)
    value = 45;
  Serial.println(value);
  Wire.beginTransmission(3);
  Wire.write(value);
  Wire.endTransmission(3);
}

