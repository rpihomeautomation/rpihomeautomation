/*
Main Program
==== ======
rev v.1

*/

//adaptive lighting
//al-adaptive lighting

//external lighting
//el-external lighting

//water pump system
//pc-pumpcontrol

//temperature mesuring system
//tm-temperature measurement

//preprosessor definitions:
//al
#define alinput A0
#define aloutput 9
#define alinterrupt 2
#define aloverride 3

//el
#define elinput A1
#define eloutput 10
#define treshold 500
#define elinterrupt 4
#define eloverride 5

//pc
#define pcinput A2
#define pcoutput 11
#define pcinterrupt 6
#define pcoverride 7

//tm
#define tminput A3

//variable defenitions:
//al
float alsensor,alvoltage; 
int albrightness;

//el
int elsensor,elstate;

//pc
int pcsensor,pcstate;

//tm
float tm,tmvoltage;


//setup function:
void setup() 
{
  Serial.begin(9600);
  //al
  pinMode(alinterrupt,INPUT);
  pinMode(aloverride,INPUT);
  //el
  pinMode(eloutput,OUTPUT);
  pinMode(elinterrupt,INPUT);
  pinMode(eloverride,INPUT);
  elstate=0;
  //pc
  pinMode(pcinput,INPUT);
  pinMode(pcoutput,OUTPUT);
  pcsensor = digitalRead(pcinput);
  pcstate = pcinput;
  
}

//loop function:
void loop() 
{ //al
  alsensor = analogRead(alinput); //read the sensor value
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
  
  //el
  elsensor=analogRead(elinput);
  if((elsensor>treshold) && (elstate==0))
  { digitalWrite(eloutput,HIGH);
    Serial.println("External light is ON");
    elstate=1;
  }
  else if((elsensor<treshold) && (elstate==1))
  { digitalWrite(eloutput,LOW);
    Serial.println("External light is OFF");
    elstate=0;
  }
  while(digitalRead(elinterrupt)) //interrupt function
  { digitalWrite(eloutput,digitalRead(eloverride));
   Serial.println("External light is ON-Override");
  }
  delay(500);
    
  //pc
  pcsensor = digitalRead(pcinput);
  if(pcsensor!=pcstate)
  {
    if(pcsensor == 1)
    { digitalWrite(pcoutput,HIGH);
      Serial.println("Motor is ON");
      pcstate = pcsensor;
    }
    else
    { digitalWrite(pcoutput,LOW);
      Serial.println("Motor is OFF");
      pcstate = pcsensor;
    }
  }
  while(digitalRead(pcinterrupt)) //interrupt function
   digitalWrite(pcoutput,digitalRead(pcoverride));
  delay(500);
  
  //tm
  tm=analogRead(tminput);//read the temperature value
  tmvoltage = tm * (5 / 1024);
  Serial.print("The temperature is ");//diplay the temperature
  Serial.println(tmvoltage);
  delay(500);
}
