int state=-1,i=0;;

void setup()
{
  pinMode(2,INPUT); //way 1
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(5,INPUT); //way2
  pinMode(6,INPUT);
  pinMode(7,INPUT);
  pinMode(8,INPUT); //way3
  pinMode(9,INPUT);
  pinMode(10,INPUT);
  pinMode(11,INPUT); //way4
  pinMode(12,INPUT);
  pinMode(13,INPUT);
  
  pinMode(A0,OUTPUT); //way1-red
  pinMode(A1,OUTPUT); //way1-green
  pinMode(A2,OUTPUT); //way2-red
  pinMode(A3,OUTPUT); //way2-green
  pinMode(A4,OUTPUT); //way3-red
  pinMode(A5,OUTPUT); //way3-green
  pinMode(0,OUTPUT); //way4-red
  pinMode(1,OUTPUT); //way4-green
  
  digitalWrite(A0,HIGH);
  digitalWrite(A1,LOW);
  digitalWrite(A2,HIGH);
  digitalWrite(A3,LOW);
  digitalWrite(A4,HIGH);
  digitalWrite(A5,LOW);
  digitalWrite(0,HIGH);
  digitalWrite(1,LOW);
}

void loop()
{
  ++state;
  if(state==1)
  { digitalWrite(A0,LOW);
    digitalWrite(A1,HIGH);
    if(digitalRead(2)==1&&digitalRead(3)==1&&digitalRead(4)==0)
     dly(4);
    else if(digitalRead(2)==1&&digitalRead(3)==1&&digitalRead(4)==1)
     dly(6);
    else
     dly(2);
    digitalWrite(A0,HIGH);
    digitalWrite(A1,LOW);
  }
  else if(state==2)
  { digitalWrite(A2,LOW);
    digitalWrite(A3,HIGH);
    if(digitalRead(5)==1&&digitalRead(6)==1&&digitalRead(7)==0)
     dly(4);
    else if(digitalRead(5)==1&&digitalRead(6)==1&&digitalRead(7)==1)
     dly(6);
    else
    dly(2);
    digitalWrite(A2,HIGH);
    digitalWrite(A3,LOW);
  }
  else if(state==3)
  { digitalWrite(A4,LOW);
    digitalWrite(A5,HIGH);
    if(digitalRead(8)==1&&digitalRead(9)==1&&digitalRead(10)==0)
     dly(4);
    else if(digitalRead(8)==1&&digitalRead(9)==1&&digitalRead(10)==1)
     dly(6);
    else
    dly(2);
    digitalWrite(A4,HIGH);
    digitalWrite(A5,LOW);
  }
  else
  { digitalWrite(0,LOW);
    digitalWrite(1,HIGH);
    if(digitalRead(11)==1&&digitalRead(12)==1&&digitalRead(13)==0)
     dly(4);
    else if(digitalRead(11)==1&&digitalRead(12)==1&&digitalRead(13)==1)
     dly(6);
    else
    dly(2);
    digitalWrite(0,HIGH);
    digitalWrite(1,LOW);
  }
  if(state==4)
   state=0;
}

void dly(int dl)
{
  for(;i<=dl;++i)
   delay(1000);
}
