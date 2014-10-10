int number = 10;

void setup(){
  Serial.begin(9600);
  delay(1000);
}

void loop(){
   //Serial.print("character recieved: ");
   Serial.println(number);
//   Serial.println("");
   ++number;
   if(number==23)
    number=10;
   delay(200);
}

