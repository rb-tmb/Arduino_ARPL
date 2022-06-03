void setup() {
  pinMode(2,INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  int val = digitalRead(2);
  Serial.print("LED1 Status: ");
  Serial.println(val);
  delay(2000);
}
