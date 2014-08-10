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

preprosessor definitions:
al
*/


#define alinput A0
#define aloutput 9
#define aloverride 2
#define altoggle 3

//el
#define elinput A1
#define eloutput 10
#define treshold 500
#define eloverride 4
#define eltoggle 5

//pc
#define pcinput A2
#define pcoutput 11
#define pcoverride 6
#define pctoggle 7

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
  pinMode(aloverride,INPUT);
  pinMode(altoggle,INPUT);
  //el
  pinMode(eloutput,OUTPUT);
  pinMode(eloverride,INPUT);
  pinMode(eltoggle,INPUT);
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
  delay(500);
  
  //el
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
  { if(digitalRead(eltoggle));
    { digitalWrite(eloutput,HIGH);
      Serial.println("External light is ON-toggle");
    }
    else
    { digitalWrite(eloutput,LOW);
      Serial.println("External light is OFF-toggle");
    }
  }
    
  //pc
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
  
  
  //tm
  tm=analogRead(tminput);//read the temperature value
  tmvoltage = tm * (5 / 1024);
  Serial.print("The temperature is ");//diplay the temperature
  Serial.println(tmvoltage);
  delay(500);
}
