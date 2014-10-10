/*
variables 
motor
red
blue 
green
*/

#define red 3
#define blue 5
#define green 6
#define motor 7

int k,state;
unsigned long int i;
//int a[10]={,,,,,,,,,};

void setup ()
{
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(blue,OUTPUT);
  pinMode(motor,OUTPUT);
  state=HIGH;
}


void loop()
{
  ++i;
  k=random(255);
  analogWrite(red,k);
  k=random(255);
  analogWrite(green,k);
  k=random(255);
  analogWrite(blue,k);
  k=random(255);
  digitalWrite(motor,state);
  if(i==1000000)
  {
    i=0;
    state=!state;
  }
}

