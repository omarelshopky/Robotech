#define LED1 10
#define LED2 11
#define BUT 13
#define POT A5

byte cont = 0;
int pval;

void setup() {
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(BUT,INPUT);
  pinMode(POT,INPUT);
}

void loop() 
{
  
  if(digitalRead(BUT) == 1)
  {
    cont++;
    delay(500);
  }
  if (cont == 1)
  {
    analogWrite(LED1,255);
    analogWrite(LED2,255);
  }
  else if (cont == 2)
  {
    pval = map(analogRead(POT),0,1023,0,255);
    analogWrite(LED1,pval);
    analogWrite(LED2,255 - pval);
  }
  else if (cont == 3)
  {
    analogWrite(LED1,0);
    analogWrite(LED2,0);
    cont = 0;
  }
        
}
