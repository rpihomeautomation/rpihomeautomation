void setup() {
   Serial.begin(9600);
}

void loop() {
    if (Serial.available()) {
        int incoming = Serial.read();
        Serial.print("character recieved: ");
        Serial.println(incoming);
    }
}
