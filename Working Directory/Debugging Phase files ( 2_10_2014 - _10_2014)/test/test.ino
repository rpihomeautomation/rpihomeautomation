void loop()
{
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
}

void setup()
{
  digitalWrite(3,HIGH);
  digitalWrite(5,HIGH);
  digitalWrite(6,HIGH);
  digitalWrite(7,HIGH);
  delay(1000);
  digitalWrite(3,LOW);
  digitalWrite(3,LOW);
  digitalWrite(3,LOW);
  digitalWrite(3,LOW);
  delay(1000);
}
  
