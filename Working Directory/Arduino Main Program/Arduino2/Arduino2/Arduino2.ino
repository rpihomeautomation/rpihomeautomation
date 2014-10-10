/*
Arduino 2
======= =

water pump system
pc-pumpcontrol

*/


//preprosessor definitions

#include <Keypad.h>
#include<String.h>
#include<EEPROM.h>



#define pcinput A2
#define pcoutput 11
#define pcoverride 6
#define pctoggle 7

#define pcinput11 A0
#define pcinput21 A1
#define pcinput22 A2
#define pcoutput A3
#define pcled A4
#define pcoverride A5
#define pctoggle 13
#define pceeprom 6


const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'}
};
char t;

byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 7, 6}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
byte ledPin = 13; 
byte motorpin1=12;
byte motorpin2=11;
boolean blink = false;
boolean ledPin_state;
int addr=0,i,c[5];
char b[5],key;

//variable defenitions

int pcstate;

int serial_input;

//functions
void pump_control_system(); //automatic pump control system function
void KEYPAD();
void motorup();
void motordown();
void keypadEvent(KeypadEvent key);


  

//setup function
void setup() 
{
  pinMode(pcinput11,INPUT);
  pinMode(pcinput21,INPUT);
  pinMode(pcinput22,INPUT);
  pinMode(pcoverride,INPUT);
  pinMode(pctoggle,INPUT);
  pinMode(pcoutput,OUTPUT);
  pinMode(pcled,OUTPUT);
  pcstate=EEPROM.read(pceeprom);
  
  pinMode(ledPin, OUTPUT);              // Sets the digital pin as output.
  digitalWrite(ledPin, HIGH);           // Turn the LED on.
  ledPin_state = digitalRead(ledPin);   // Store initial LED state. HIGH when LED is on.
  keypad.addEventListener(keypadEvent); // Add an event listener for this keypad
  for(i=0,addr=0;i<4;i++,addr++)
  {
    c[i]=EEPROM.read(addr);
    b[i]=c[i]+48;
  }
  addr=0;
  
  delay(1000);
  Serial.begin(9600);
  delay(1000);
}


//loop function
void loop() 
{ pump_control_system(); //call the automatic pump control system function
  KEYPAD();
  delay(1);
}


void serialEvent()
{
  if(Serial.available()==1)
  { serial_input=Serial.read();
    if(serial_input==40)
     pcstatus();
  }
}


//pump control system
void pump_control_system()
{
  if(digitalRead(pcinput11==1)&&pcstate!=5)
  { Serial.print(45);
    pcstate=5;
    EEPROM.write(pceeprom,pcstate);
    digitalWrite(pcled,HIGH);
    delay(500);
    digitalWrite(pcled,LOW);
  }
  if(pcstate==5)
   return;
  pcstate=1;
  if(!digitalRead(pcoverride))
  { int a,b;
    a=digitalRead(pcinput21);
    b=digitalRead(pcinput22);
    if(a==1&&b==1&&pcstate!=2)
    { digitalWrite(pcoutput,HIGH);
      Serial.print(42);
      pcstate = 2;
      EEPROM.write(pceeprom,pcstate);
    }
    else if(a==0&&b==0&&pcstate!=1)
    { digitalWrite(pcoutput,LOW);
      Serial.print(41);
      pcstate = 1;
      EEPROM.write(pceeprom,pcstate);
    }
  }
  else //override function
  { if(digitalRead(pctoggle)==1&&pcstate!=4)
    { digitalWrite(pcoutput,HIGH);
      Serial.print(44);
      pcstate = 4;
      EEPROM.write(pceeprom,pcstate);
    }
    else if(pctoggle==0&&pcstate!=3)
    { digitalWrite(pcoutput,LOW);
      Serial.print(43);
      pcstate = 3;
      EEPROM.write(pceeprom,pcstate);
    }
  }
  return;
}

void pcstatus()
{
  if(pcstate==1)
   Serial.print(31);
  else if(pcstate==2)
   Serial.print(32);
  else if(pcstate==3)
   Serial.print(23);
  else
   Serial.print(24);
  return;
}

void KEYPAD()
{ int i,j,k,l;
  //Serial.println("Enter password:");
  char a[5];
  for(i=0;i<4;i++)
  { char key = keypad.waitForKey();
    //if (key)
    //{
    //    Serial.println(key);
    //}
    a[i]=key;
  }
  a[i]='\0';
  if(!strcmp(a,b))
  { //Serial.println("Password is correct\n");
    Serial.print(53);
    for(j=0;j<100;j++)
    { for(k=0;k<2000;k++)
      { if(keypad.getKey()=='*')
        { //Serial.println("Enter new password");
          for(l=0,addr=0;l<4;l++)
          { b[l]=keypad.waitForKey();
            c[l]=b[l]-48;
            EEPROM.write(addr,c[l]);
            //Serial.println(b[l]);
            addr++;
          }
          Serial.print(54);
        }
      }
    }
    //Serial.println("Delay over");
    motorup();
    key = keypad.waitForKey();
    if(key=='#')
     motordown();
  }
  else
   Serial.print(53);
  addr=0;
  if (blink)
  { digitalWrite(ledPin,!digitalRead(ledPin));    // Change the ledPin from Hi2Lo or Lo2Hi.
    delay(100);
  }
}


void motorup()
{
  digitalWrite(motorpin1,HIGH);
  digitalWrite(motorpin2,LOW);
  delay(2500);
  digitalWrite(motorpin1,LOW);
}

void motordown()
{
  digitalWrite(motorpin2,HIGH);
  digitalWrite(motorpin1,LOW);
  delay(2500);
  digitalWrite(motorpin2,LOW);
}  

// Taking care of some special events.
void keypadEvent(KeypadEvent key)
{ switch (keypad.getState()){
  case PRESSED:
       if (key == '#') {
            digitalWrite(ledPin,!digitalRead(ledPin));
            ledPin_state = digitalRead(ledPin);        // Remember LED state, lit or unlit.
        }
        break;

    case RELEASED:
        if (key == '*') {
            digitalWrite(ledPin,ledPin_state);    // Restore LED state from before it started blinking.
            blink = false;
        }
        break;

    case HOLD:
        if (key == '*') {
            blink = true;    // Blink the LED when holding the * key.
        }
        break;
    }
}

