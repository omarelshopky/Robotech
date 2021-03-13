#include<Servo.h>

#define LDR A2
#define POT A0
#define MOT1 2
#define MOT2 3
#define S 5

Servo myservo;

int lval;
int pval;
int mapp;

void setup() {
  pinMode(LDR, INPUT);
  pinMode(POT, INPUT);
  pinMode(MOT1, OUTPUT);
  pinMode(MOT2, OUTPUT);
  myservo.attach(S);
}

void loop() {
  lval = analogRead(LDR);
  pval = analogRead(POT);
  mapp = map(pval, 0, 1023, 0, 180);
  myservo.write(mapp);
  if (lval > 680)
  {
    digitalWrite(MOT1, HIGH);
    digitalWrite(MOT2, LOW);
  }
  else
  {
    digitalWrite(MOT2, HIGH);
    digitalWrite(MOT1, LOW);
  }
  
}
