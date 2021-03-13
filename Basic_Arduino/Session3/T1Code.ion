#include<Keypad.h>

#define LDR A1
#define LM A0
#define TRG 13
#define ECO 12
#define R1 11
#define R2 10
#define R3 9
#define R4 8
#define C1 7
#define C2 6
#define C3 5
#define C4 4
#define BUZZER 3
#define LED 2
#define ROWS 4
#define COLS 4

byte ROWPINS[ROWS] = {R1, R2, R3, R4};
byte COLPINS[COLS] = {C1, C2, C3, C4};
char SYMPOLS[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}};

int LRAN = 100;
int URAN = 100;
int TRAN = 100;

int time;
int distance;

float MV;
float C;
int LDRVAL;

Keypad pad = Keypad(makeKeymap(SYMPOLS), ROWPINS, COLPINS, ROWS, COLS);

void setup() 
{
  Serial.begin(3600);
  pinMode(LDR, INPUT);
  pinMode(LM, INPUT);
  pinMode(ECO, INPUT);
  pinMode(TRG, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED, OUTPUT);
}

void loop() 
{
  char custom = pad.getKey();
  if (custom)
  {
    if (custom == '1')
    {
      Serial.print("LDR Sensor Range: ");
      Serial.println(LRAN);
      Serial.println("Enter LDR Range (three digits)");
      LRAN = 0;
      for (int i = 100; i >= 1; i = i / 10)
      {
        custom = pad.waitForKey();
        LRAN += (custom - 48) * i;
      }
      Serial.print("New LDR Range: ");
      Serial.println(LRAN);
    }
    else if (custom == '2')
    {
      Serial.print("Ultrasonic Sensor Range: ");
      Serial.println(URAN);
      Serial.println("Enter Ultrasonic Range (three digits)");
      URAN = 0;
      for (int i = 100; i >= 1; i = i / 10)
      {
        custom = pad.waitForKey();
        URAN += (custom - 48) * i;
      }
      Serial.print("New Ultrasonic Range: ");
      Serial.println(URAN);
    }
    else if (custom == '3')
    {
      Serial.print("Temperature Sensor Range: ");
      Serial.println(TRAN);
      Serial.println("Enter Temperature Range (three digits)");
      TRAN = 0;
      for (int i = 100; i >= 1; i = i / 10)
      {
        custom = pad.waitForKey();
        TRAN += (custom - 48) * i;
      }
      Serial.print("New Temperature Range: ");
      Serial.println(TRAN);
    }
    else if (custom == '#')
    {
      Serial.print("Now LDR Value: ");
      Serial.println(CALLDR());
      Serial.print("Now Ultrasonic Value: ");
      Serial.print(CALDIS());
      Serial.println(" cm.");
      Serial.print("Now Tempreture Value: ");
      Serial.print(CALTEM());
      Serial.println(" *C.");
    }
  }
  
  if (CALDIS() > URAN || CALTEM() > TRAN || CALLDR() > LRAN)
  {
    digitalWrite(BUZZER, HIGH);
    digitalWrite(LED, HIGH);
  }
  else
  {
    digitalWrite(BUZZER, LOW);
    digitalWrite(LED, LOW);
  } 
}

int CALDIS()
{
  digitalWrite(TRG, LOW);
  delayMicroseconds(5);
  digitalWrite(TRG, HIGH);
  delayMicroseconds(5);
  digitalWrite(TRG, LOW);
  time = pulseIn(ECO, HIGH);
  distance = time/29/2;
  return distance;
}

float CALTEM()
{
  MV = (analogRead(LM) / 1024.0) * 5000;
  C = MV / 10;
  return C;
}

int CALLDR()
{
  LDRVAL = analogRead(LDR);
  return LDRVAL;
}

