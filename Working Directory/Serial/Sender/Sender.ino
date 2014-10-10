int a;
void setup()
{
 pinMode(5,INPUT_PULLUP);
 Serial.begin(9600);
}

void loop()
{
 a=digitalRead(5);
 Serial.write(a);
}
