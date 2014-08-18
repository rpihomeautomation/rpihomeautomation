/*
Main Program
==== ======
rev v.1

adaptive lighting
al-adaptive lighting

external lighting
el-external lighting

water pump system
pc-pumpcontrol

temperature mesuring system
tm-temperature measurement


INPUTS: alinput - A0
        aloverride - 2
        altoggle 3
        
        elinput - A1
        eloverride - 4
        eltoggle - 5
        
        pcinput - A2
        pcoverride - 6
        pctoggle - 7
        
        tminput - A3
        
OUTPUTS:aloutput - 9
        eloutput - 10
        pcoutput - 11
*/


//preprosessor definitions
#define alinput A0
#define aloutput 9
#define aloverride 2
#define altoggle 3

#define elinput A1
#define eloutput 10
#define treshold 500
#define eloverride 4
#define eltoggle 5

#define pcinput A2
#define pcoutput 11
#define pcoverride 6
#define pctoggle 7

#define tminput A3

//variable defenitions
float alsensor,alvoltage; 
int albrightness;

int elsensor,elstate;

int pcsensor,pcstate;

float tm,tmvoltage;

//functions
void adaptive_internal_lighting_system(); //adaptive internal lighting system function
void external_lighting_system(); //external lighting system function
void pump_control_system(); //automatic pump control system function
void temperature_measurement(); //temperature measurement function
  

//setup function
void setup() 
{
  Serial.begin(9600);
  
  pinMode(aloverride,INPUT);
  pinMode(altoggle,INPUT);
  
  pinMode(eloutput,OUTPUT);
  pinMode(eloverride,INPUT);
  pinMode(eltoggle,INPUT);
  elstate=0;
  
  pinMode(pcinput,INPUT);
  pinMode(pcoutput,OUTPUT);
  pcsensor = digitalRead(pcinput);
  pcstate = pcinput;
}


//loop function
void loop() 
{ adaptive_internal_lighting_system(); //call the adaptive internal lighting system function
  external_lighting_system(); //call the external lighting system function
  pump_control_system(); //call the automatic pump control system function
  temperature_measurement();//call the temperature measurement function
  delay(500);
}

//adaptive internal lighting system function
void adaptive_internal_lighting_system()
{
  if(!digitalRead(aloverride))
  { alsensor = analogRead(alinput); //read the sensor value
    albrightness = alsensor / 4; //convert the value from 10-bit resolution to 8-bit res
    alvoltage = alsensor * (5.0 / 1024.0); //convert the value into actual voltage range 0-5V
    Serial.print("The voltage is: ");  //prints the voltage through serial
    Serial.println(alvoltage);
    analogWrite(aloutput,albrightness); //output the PWM to the LED
  }
  else //override function
  { if(digitalRead(altoggle)) //toggle - ON
     analogWrite(aloutput,255);
    else //toggle - OFF
     analogWrite(aloutput,0);
  }
  return;
}

//external lighting system function
void external_lighting_system()
{
  if(!digitalRead(eloverride))
  { elsensor=analogRead(elinput);
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
  }
  else //override function
  { if(digitalRead(eltoggle))
    { digitalWrite(eloutput,HIGH);
      Serial.println("External light is ON-toggle");
    }
    else
    { digitalWrite(eloutput,LOW);
      Serial.println("External light is OFF-toggle");
    }
  }
  return;
}

//pump control system
void pump_control_system()
{
  if(!digitalRead(pcoverride))
  { pcsensor = digitalRead(pcinput);
    if(pcsensor!=pcstate)
    { if(pcsensor == 1)
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
  }
  else //override function
  { pcsensor = digitalRead(pctoggle);
    if(pcstate!=pcsensor)
    { if(pcsensor == 1)
      { digitalWrite(pcoutput,HIGH);
        Serial.println("Motor is ON - toggle");
        pcstate = pcsensor;
      }
      else
      { digitalWrite(pcoutput,LOW);
        Serial.println("Motor is OFF - toggle");
        pcstate = pcsensor;
      }
    }
  }
  return;
}

//temperature measurement system
void temperature_measurement()
{
  tm=analogRead(tminput);//read the temperature value
  tmvoltage = tm * (5 / 1024);
  Serial.print("The temperature is ");//diplay the temperature
  Serial.println(tmvoltage);
  Serial.print("The ADC value is: "); //display the ADC value
  Serial.println(tminput);
  return;
}
