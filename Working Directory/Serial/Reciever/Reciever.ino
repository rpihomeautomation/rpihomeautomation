const int ledPin = 9;
int a;
 
void setup()
{
  // initialize the serial communication:
  Serial.begin(9600);
  // initialize the ledPin as an output:
  pinMode(ledPin, OUTPUT);
  pinMode(2,OUTPUT);
}

void loop()
{
 delay(500);  // check if data has been sent from the computer:
 if (Serial.available()) 
 { a = Serial.parseInt();
   if(a==1)
   { digitalWrite(9,HIGH);
     digitalWrite(2,LOW);
   }
   else
   { analogWrite(9,50);
     digitalWrite(2,LOW);
   }
 }
 else
 { digitalWrite(2,HIGH);
   digitalWrite(9,LOW);
 }
 delay(1000);
}
