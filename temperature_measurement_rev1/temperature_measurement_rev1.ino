/*
Temperature Measurement
=========== ===========
rev v.1
#measure the temperature using LM35
#sends the data serially for verification
*/


//tm-temperature measurement

#define tminput A0

void setup()
{
  Serial.begin(9600);
}

float tm,tmvoltage;
void loop()
{
  tm=analogRead(tminput);//read the temperature value
  tmvoltage = tm * (5 / 1024);
  Serial.print("The temperature is ");//diplay the temperature
  Serial.println(tmvoltage);
  delay(500);
}   
