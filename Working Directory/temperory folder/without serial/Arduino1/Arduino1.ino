/*
Main Program
==== ======
rev v.1

adaptive lighting
al-adaptive lighting

external lighting
el-external lighting

temperature mesuring system
tm-temperature measurement

arduino1:
PIR:
i/p - A0

*/

#include <EEPROM.h>


//preprosessor definitions
#define alinput A1
#define aloutput 10
#define aloverride 12
#define altoggle 13
#define althresholdlow 500
#define althresholdmedium 700
#define althresholdhigh 1000
#define aleeprom 1

#define elinput A2
#define eloutput 7
#define elthreshold 500
#define eloverride 5
#define eltoggle 6
#define eleeprom 2

#define tminput A3

//variable defenitions
int pirinput = 9; // choose the input pin (for PIR sensor)
int pirstate = LOW; // we start, assuming no motion detected
int val = 0; // variable for reading the pin status
int pir_status=0;

int alstate,alsensor;

int elstate,elsensor;

int tm;

int serial_input;




//functions
int pir();
void adaptive_internal_lighting_system(); //adaptive internal lighting system function
void external_lighting_system(); //external lighting system function
void temperature_measurement(); //temperature measurement function
void alstatus();
void elstatus();

//setup function
void setup() 
{
  pinMode(pirinput, INPUT); // declare sensor as input
  pinMode(aloverride,INPUT);
  pinMode(altoggle,INPUT);
  alstate=EEPROM.read(aleeprom);
  
  pinMode(eloutput,OUTPUT);
  pinMode(eloverride,INPUT);
  pinMode(eltoggle,INPUT);
  elstate=EEPROM.read(eleeprom);
  
  delay(1000);
  Serial.begin(9600);
  
  delay(1000);
}


//cloop function
void loop() 
{ pir_status=pir();
  adaptive_internal_lighting_system(); //call the adaptive internal lighting system function
  external_lighting_system(); //call the external lighting system function
  //temperature_measurement();//call the temperature measurement function
  delay(1);
}


int pir()
{
  
val = digitalRead(pirinput); // read input value
if (val == HIGH)
    { 
      // check if the input is HIGH
      if (pirstate == LOW)
        {
          // we have just turned on
          // We only want to print on the output change, not state
          pirstate = HIGH;
          return pirstate;
        }
     }
else 
  {
          if (pirstate == HIGH)
        {
          // we have just turned of
          pirstate = LOW;
          return pirstate;
        }
  }
}


void serialEvent()
{
  if(Serial.available()==1)
  { serial_input=Serial.read();
    if(serial_input==20)
     alstatus();
    else if(serial_input==30)
     elstatus();
    else if(serial_input==60)
     temperature_measurement();
  }
}


//adaptive internal lighting system function
void adaptive_internal_lighting_system()
{
  pir_status=pir();
  if(pir_status==0&&alstate!=4)
  { Serial.print(25);
    alstate=4;
    EEPROM.write(aleeprom,alstate);
  }
  if(alstate==4)
   return;
 if(!digitalRead(aloverride))
 { alsensor = analogRead(alinput); //read the sensor value
   if(alsensor>=althresholdlow)
   { analogWrite(aloutput,150); //output the PWM to the LED
     if(alsensor>=althresholdmedium)
      analogWrite(aloutput,200);
     else if(alsensor>=althresholdhigh)
      analogWrite(aloutput,255);
     if(alstate!=1)
     {
       Serial.print(22);
       alstate=1;
       EEPROM.write(aleeprom,alstate);
     }
   }
   else
   { if(alstate!=0)
     { alstate=0;
       Serial.print(21);
       EEPROM.write(aleeprom,alstate);
      }
   }
 } 
 else //override function
 { if(digitalRead(altoggle)) //toggle - ON
   { analogWrite(aloutput,255);
     if(alstate!=3)
     { alstate=3;
       Serial.print(24);
       EEPROM.write(aleeprom,alstate);
     }
   }
   else //toggle - OFF
   { analogWrite(aloutput,0);
     if(alstate!=2)
     { alstate=2;
       Serial.print(23);
       EEPROM.write(aleeprom,alstate);
     }
   }
 }
 return;
}

void alstatus()
{
  if(alstate==1)
   Serial.print(21);
  else if(alstate==2)
   Serial.print(22);
  else if(alstate==3)
   Serial.print(23);
  else if(alstate==4)
   Serial.print(24);
  else
   Serial.print(25);
  return;
}

//external lighting system function
void external_lighting_system()
{
  if(!digitalRead(eloverride))
  { elsensor=analogRead(elinput);
    if(elsensor>elthreshold)
    { digitalWrite(eloutput,HIGH);
      if(elstate!=1)
      { Serial.print(32);
        elstate=1;
        EEPROM.write(eleeprom,elstate);
      }
    }
    else if(elsensor<elthreshold)
    { digitalWrite(eloutput,LOW);
      { if(elstate!=0)
        { Serial.print(31);
          elstate=0;
          EEPROM.write(eleeprom,elstate);
        }
      }
    }
  }
  else //override function
  { if(digitalRead(eltoggle))
    { digitalWrite(eloutput,HIGH);
      if(elstate!=3)
      { Serial.print(34);
        elstate=3;
        EEPROM.write(eleeprom,elstate);
      }
    }
    else
    { digitalWrite(eloutput,LOW);
      if(elstate!=2)
      { Serial.print(33);
        elstate=2;
        EEPROM.write(eleeprom,elstate);
      }
    }
  }
  return;
}

void elstatus()
{
  if(elstate==1)
   Serial.print(31);
  else if(elstate==2)
   Serial.print(32);
  else if(elstate==3)
   Serial.print(23);
  else
   Serial.print(24);
  return;
}



//temperature measurement system
void temperature_measurement()
{
  tm=analogRead(tminput);//read the temperature value
  //tmvoltage = tm * (5 / 1024);
  Serial.print(61);
  Serial.print(tm);
  return;
}

