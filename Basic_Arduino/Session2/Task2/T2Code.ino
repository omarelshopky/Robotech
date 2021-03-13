#include <LiquidCrystal.h>

#define RS 2
#define EN 3
#define D4 4
#define D5 5
#define D6 6
#define D7 7

LiquidCrystal LCD (RS,EN,D4,D5,D6,D7);

void setup() {
  LCD.begin(16,2);
}

void loop() {
  int i = -3, j = 15;
  while (i <= 4 && j >= 8)
  {
    if (i == -3)
    {
      LCD.setCursor(0,0);
      LCD.print("o");
    }
    else if (i == -2)
    {
      LCD.setCursor(0,0);
      LCD.print("bo");
    }
    else if (i == -1)
    {
      LCD.setCursor(0,0);
      LCD.print("obo");
    }
    LCD.setCursor(i,0);
    LCD.print("Robo");
    LCD.setCursor(j,0);
    LCD.print("tech");
    delay(300);
    LCD.clear();
    i++;
    j--;
  }
  i = 4;
  j = 8;
  while (i >= -3 && j <= 15)
  {
    if (i == -3)
    {
      LCD.setCursor(0,0);
      LCD.print("o");
    }
    else if (i == -2)
    {
      LCD.setCursor(0,0);
      LCD.print("bo");
    }
    else if (i == -1)
    {
      LCD.setCursor(0,0);
      LCD.print("obo");
    }
    LCD.setCursor(i,0);
    LCD.print("Robo");
    LCD.setCursor(j,0);
    LCD.print("tech");
    delay(300);
    LCD.clear();
    i--;
    j++;
  }
  

}

