int number = 10;
int flag = 0;

void setup(){
  Serial.begin(9600);
  pinMode(9,OUTPUT);
  delay(1000);
}

void loop()
{
  if(flag)
  { digitalWrite(9,HIGH);
    delay(200);
    digitalWrite(9,LOW);
    delay(200);
  }
}

void serialEvent()
{
  if(Serial.available())
   { number= Serial.read();
     if(number=='a')
     { Serial.print(15);
       flag=0;
     }
     else if(number=='b')
     { Serial.print(19);
       flag=1;
     }
     else if(number=='c')
     { Serial.print(22);
       flag=0;
     }
     else if(number=='d')
     { Serial.print(27);
       flag=1;
     }
     else
     { Serial.print(29);
       flag=0;
     }
   }
}




