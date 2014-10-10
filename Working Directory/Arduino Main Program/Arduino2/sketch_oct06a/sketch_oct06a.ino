
void keypad()
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



























#define pcinput11 A0
#define pcinput21 A1
#define pcinput22 A2
#define pcoutput A3
#define pcled A4
#define pcoverride A5
#define pctoggle 13
#define pceeprom 6

int pcstate;

void pump_control_system(); //automatic pump control system function
//setup function
void setup() 
{
  Serial.begin(9600);
  
  pinMode(pcinput11,INPUT);
  pinMode(pcinput21,INPUT);
  pinMode(pcinput22,INPUT);
  pinMode(pcoverride,INPUT);
  pinMode(pctoggle,INPUT);
  pinMode(pcoutput,OUTPUT);
  pinMode(pcled,OUTPUT);
  pcstate=EEPROM.read(pceeprom);
}


//loop function
void loop()
{ pump_control_system(); //call the automatic pump control system function
  delay(500);
}

//pump control system
void pump_control_system()
{
  if(digitalRead(pcinput11==1)&&pcstate!=4)
  { Serial.print(45);
    pcstate=4;
    EEPROM.write(pceeprom,pcstate);
    digitalWrite(pcled,HIGH);
    delay(500);
    digitalWrite(pcled,LOW);
  }
  if(pcstate==4)
   return;
  pcstate=0;
  if(!digitalRead(pcoverride))
  { int a,b;
    a=digitalRead(pcinput21);
    b=digitalRead(pcinput22);
    if(a==1&&b==1&&pcstate!=1)
    { digitalWrite(pcoutput,HIGH);
      Serial.print(42);
      pcstate = 1;
      EEPROM.write(pceeprom,pcstate);
    }
    else if(a==0&&b==0&&pcstate!=0)
    { digitalWrite(pcoutput,LOW);
      Serial.print(41);
      pcstate = 0;
      EEPROM.write(pceeprom,pcstate);
    }
  }
  else //override function
  { if(digitalRead(pctoggle==1&&pcstate!=3)
    { digitalWrite(pcoutput,HIGH);
      Serial.print(44);
      pcstate = 3;
      EEPROM.write(pceeprom,pcstate);
    }
    else if(pctoggle==0&&pcstate!=2)
    { digitalWrite(pcoutput,LOW);
      Serial.print(43);
      pcstate = 2;
      EEPROM.write(pceeprom,pcstate);
    }
  }
  return;
}


