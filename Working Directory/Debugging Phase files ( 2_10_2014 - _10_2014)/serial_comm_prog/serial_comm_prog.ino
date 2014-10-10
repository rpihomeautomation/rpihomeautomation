const int ledPin = 13;
int flag=0;
int sent_data;
void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(9,INPUT);
}

void loop()
{
     
     if(flag==1)
      {
         digitalWrite(ledPin,HIGH);
         delay(500);
         digitalWrite(ledPin,LOW);
         delay(500);    
      }
     else
          digitalWrite(ledPin,LOW);
}
void serialEvent()
{
  
  while(Serial.available()) 
  { sent_data = Serial.read();
    if(sent_data=='1')
    {
      Serial.println("got_1");
      int state=digitalRead(9);
      Serial.println(state);
      //Serial.write(state);
    }
    else if(sent_data=='2')
    {
      Serial.println("got_2");
      flag=!flag;
    }
  }
}
  
    
