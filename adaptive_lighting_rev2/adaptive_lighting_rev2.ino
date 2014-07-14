/*
Adaptive Lighting System
======== ======== ======
rev v.1
#test program for adaptive lighting
#controls the brightness of an led according to the amount of light present
#connects the sensor at pin A0 and the LED at pin 9
#the input is read and the voltage value is send serially
#the prograam varies it's PWM according to the input voltage
*/

//al-adaptive lighting

#define alinput A0
#define aloutput 9
#define alinterrupt A1
#define aloverride A2


float alsensor,alvoltage; 
int albrightness;

void setup() 
{
  Serial.begin(9600);
  pinMode(alinterrupt,INPUT);
  pinMode(aloverride,INPUT);
}

void loop() 
{ alsensor = analogRead(alinput); //read the sensor value
  albrightness = alsensor / 4; //convert the value from 10-bit resolution to 8-bit res
  alvoltage = alsensor * (5.0 / 1024.0); //convert the value into actual voltage range 0-5V
  Serial.print("The voltage is: ");  //prints the voltage through serial
  Serial.println(alvoltage);
  analogWrite(aloutput,albrightness); //output the PWM to the LED
  while(digitalRead(alinterrupt)) //interrupt function
  { if(digitalRead(aloverride)) //override - ON
     analogWrite(aloutput,255);
    else //override - OFF
     analogWrite(aloutput,0);
  }
  delay(500);
}
