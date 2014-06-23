/*
Automatic External lighting
========= ======== ========
rev v.1
#turns on an external light when the amount of light falls below a preset value
#ldr is connected to the A0 pin and led is connected to pin 9
#sends info about the change of state of led serially for monitoring
*/

//el-external lighting

#define elinput A0
#define eloutput 9
#define treshold 500

int elsensor,elstate;

void setup()
{
  Serial.begin(9600);
  pinMode(eloutput,OUTPUT);
  elstate=0;
}

void loop()
{
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
  delay(500);
}
  
