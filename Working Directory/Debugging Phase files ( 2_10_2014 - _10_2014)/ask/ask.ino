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

int dly,i,j,k,loopcount,state;

void setup ()
{
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(blue,OUTPUT);
  pinMode(motor,OUTPUT);
  randomSeed(analogRead(0));
 // pinMode(13,OUTPUT);
  //pinMode(12,OUTPUT);
  //state=1;
  digitalWrite(motor,HIGH);
  delay(15000);
  state=0;
  //digitalWrite(motor,LOW);
  i=-1;
  loopcount==1;
}



void loop()
{
  ++i;
  //k=255;
  k=random(150,255);
  analogWrite(red,k);
  k=random(150,255);
  analogWrite(green,k);
  k=random(200,255);
  analogWrite(blue,k);
  dly = random(200,1000);
  //dly=1000;
  delay(dly);
  //digitalWrite(red,HIGH);
  //digitalWrite(blue,HIGH);
  //digitalWrite(green,HIGH);
  //delay(1000);
  if(i==loopcount)
  { i=0;
    //digitalWrite(13,HIGH);
    loopcount=random(1,3);
    //loopcount=2;
    
    if(state==0)
     state=1;
    else
     state=0;
    digitalWrite(motor,state);
    //dly = random(0,3000);
    dly=3000;
    delay(dly);
    digitalWrite(motor,HIGH);
  }
}

//bibth: +918547575649
