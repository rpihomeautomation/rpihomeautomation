#define red 3
#define blue 7
#define motor 6
#define green 5

int i;

void setup()
{
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(blue,OUTPUT);
  pinMode(motor,OUTPUT);
  digitalWrite(motor,HIGH);
  delay(10000);
  i=3;
}

void loop()
{
  while(1)
  {
    ++i;
    switch(i)
    {
      case 1: digitalWrite(motor,HIGH);
              digitalWrite(red,HIGH);
              delay(2500);
              digitalWrite(red,LOW);
              digitalWrite(green,HIGH);
              delay(2500);
              digitalWrite(green,LOW);
              digitalWrite(blue,HIGH);
              digitalWrite(motor,LOW);
              delay(3700);
              digitalWrite(blue,LOW);
              break;
      case 2: digitalWrite(motor,HIGH);
              digitalWrite(green,HIGH);
              delay(2700);
              digitalWrite(green,LOW);
              digitalWrite(blue,HIGH);
              delay(2500);
              digitalWrite(blue,LOW);
              digitalWrite(red,HIGH);
              digitalWrite(motor,LOW);
              delay(4000);
              digitalWrite(blue,LOW);
              break;
      case 3: digitalWrite(motor,HIGH);
              digitalWrite(blue,HIGH);
              delay(2500);
              digitalWrite(blue,LOW);
              digitalWrite(red,HIGH);
              delay(2600);
              digitalWrite(red,LOW);
              digitalWrite(green,HIGH);
              digitalWrite(motor,LOW);
              delay(4200);
              digitalWrite(blue,LOW);
              break;
      case 4: digitalWrite(motor,HIGH);
              digitalWrite(blue,HIGH);
              delay(2500);
              digitalWrite(red,HIGH);
              delay(2400);
              digitalWrite(red,LOW);
              digitalWrite(green,HIGH);
              digitalWrite(motor,LOW);
              delay(4200);
              digitalWrite(blue,LOW);
              digitalWrite(green,LOW);
              break;
      case 5: digitalWrite(motor,HIGH);
              digitalWrite(red,HIGH);
              delay(2700);
              digitalWrite(green,HIGH);
              delay(2100);
              digitalWrite(green,LOW);
              digitalWrite(blue,HIGH);
              digitalWrite(motor,LOW);
              delay(3200);
              digitalWrite(blue,LOW);
              break;
     case 6:  digitalWrite(motor,HIGH);
              digitalWrite(green,HIGH);
              delay(2600);
              digitalWrite(red,HIGH);
              delay(2300);
              digitalWrite(red,LOW);
              digitalWrite(blue,HIGH);
              digitalWrite(motor,LOW);
              delay(3900);
              digitalWrite(blue,LOW);
              break;
     default: i=1;
              break;
    }
  }
}
