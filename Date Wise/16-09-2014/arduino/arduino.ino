const int ledPin = 9;
int flag=0,st=0;

void setup()
{
  Serial.begin(9600);
  //pinMode(11,OUTPUT);
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  byte brightness;
  if(Serial.available()) 
  { brightness = Serial.read();
    Serial.write(brightness);
    if(brightness=='1')
    {
     Serial.println("Voila");
     if(flag==0)
      flag=1;
     else
      flag=0;
     Serial.println(flag);
    }
    else if(brightness=='2')
     Serial.println("Hai");
    if(flag==1)
    {
     digitalWrite(ledPin,st);
     delay(1000);
     if(st==0)
      st=1;
     else
      st=0;
     Serial.println("HELLO");
    }
   }
}