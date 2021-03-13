#include <LiquidCrystal.h>
#include <Keypad.h>

#define C1 7
#define C2 6
#define C3 5
#define C4 4
#define R1 11
#define R2 10
#define R3 9
#define R4 8
#define ROWS 4
#define COLS 4
#define GLED 3
#define RLED 2

byte ROWPINS [ROWS] = {R1, R2, R3, R4};
byte COLSPINS [COLS] = {C1, C2, C3, C4};
char SYMPOLS[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}};

Keypad pad = Keypad(makeKeymap(SYMPOLS), ROWPINS, COLSPINS, ROWS, COLS);

char pass[] = {'0','0','0','0'};
char newpass[sizeof(pass)];

byte i=0,a=0, s=0, j=0;

void setup() {
  Serial.begin(9600);
  pinMode(GLED,OUTPUT);
  pinMode(RLED,OUTPUT);
}

void loop() {
  char custom = pad.getKey();
  // check password
  if (custom == '*')
  {
    a = 0;
    i = 0;
    j = 0;
    while (custom !='A')
    {
      custom = pad.getKey();
      if (custom != NO_KEY && custom != 'A')
      {
        j++;
        if (custom == pass[i] && i < sizeof(pass))
        {
          a++;
          i++;
        }
        else
          a--;
      }
    }
    custom = NO_KEY;
    if (a == sizeof(pass))
    {
      digitalWrite(GLED,1);
      digitalWrite(RLED,0);
    }
    else
    {
      digitalWrite(GLED,0);
      digitalWrite(RLED,1);
    }
  }
  //make newone
  else if (custom == '#')
  {
    i =0;
    while (custom != 'A')
    {
      custom = pad.getKey();
      if (custom != NO_KEY && custom != 'A')
      {
        pass[i] = custom;
        i++;
      }
    }
    custom = NO_KEY;
  }
}
