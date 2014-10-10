/*
Adaptive Lighting System
======== ======== ======
rev v.1
#Test program for Adaptive Lighting
#Controls the brightness of an LED according to the amount of light present.
#Connects the sensor at pin A0 and the LED at pin 9
#The input is read and the voltage value is sent serially.
#The prograam varies it's PWM according to the input voltage.
*/

//AI-Adaptive Lighting

#define alinput A0
#define aloutput 9
#define alinterrupt A1
#define aloverride A2
#define althresholdlow 400
#define althresholdmedium 600
#define althresholdhigh 900


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
  //Serial.print("The voltage is: ");  //prints the voltage through serial
  Serial.println(alsensor);
  if(alsensor>=althresholdlow)
   { analogWrite(aloutput,100); //output the PWM to the LED
     if(alsensor>=althresholdmedium)
      analogWrite(aloutput,175);
     else if(alsensor>=althresholdhigh)
      analogWrite(aloutput,255);
   }
   if(alsensor<althresholdlow)
    analogWrite(aloutput,0);
  
  //analogWrite(aloutput,albrightness); //output the PWM to the LED
  //while(digitalRead(alinterrupt)) //interrupt function
//  { if(digitalRead(aloverride)) //override - ON
  //   analogWrite(aloutput,255);
    //else //override - OFF
     //analogWrite(aloutput,0);
  //}
  delay(500);
}

