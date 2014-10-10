int number = 10;

void setup(){
  Serial.begin(9600);
  delay(1000);
}

void loop(){
   //Serial.print("character recieved: ");
   if(Serial.available())
   { number= Serial.read();
     if(number=='a')
      Serial.print(15);
     else if(number=='b')
      Serial.print(19);
     else if(number=='c')
      Serial.print(22);
     else if(number=='d')
      Serial.print(27);
     else
      Serial.print(29);
   }
   //delay(20);
}

