byte r_byte;
int state=0;
int count=0;
//boolean st=false,flag=true;
int st=0,flag=0

void setup()
{
  pinMode(13,INPUT);
  
  digitalWrite(11,LOW);
  Serial.begin(9600);
}


void loop()
{
  while(Serial.available()>0)
  {
    r_byte=Serial.read();
    if(r_byte=='1')
    {
      state=digitalRead(13);
      Serial.write(state);
    }
    else if(r_byte=='2')
      flag^=1;
  }
  if(flag==true)
  {
    digitalWrite(11,st);
    delay(1000);
    st^=st;
  }
}
 
  /*
void serialEvent()
{
  while(Serial.available()>0)
  {
    r_byte=Serial.read();
    if(r_byte==1)
    {
      state=digitalRead(13);
      Serial.write(state);
    }
    else if(r_byte==2)
      flag=!flag;
  }
}


*/
