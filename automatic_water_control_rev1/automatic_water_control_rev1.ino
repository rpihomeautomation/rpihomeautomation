/*
Automatic Water Control System
========= ===== ======= ======
rev v.1
#test program for water pump system
#turns on the pump when the input is high
#connects the input from the sensor to   pin
#output from   pin
#the output is connected to the relay drivring circuit
#the input value is sent serially for monitoring
*/

//pc-pumpcontrol

#define pcinput A0
#define pcoutput 9

int pcsensor,pcstate;

void setup()
{
  Serial.begin(9600);
  pinMode(pcinput,INPUT);  // DEEPAK, WHY ARE YOU USING AN ANALOG PIN FOR DIGITAL INPUT??? WUT BOUT THE OTHER DIGITAL PINS??
  pinMode(pcoutput,OUTPUT);
  pcsensor = digitalRead(pcinput); // why this line here? 
  pcstate = pcinput;    // is this correct??  pcinput is just a pin num isnt it??
}

void loop()
{
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
  delay(500);
}
