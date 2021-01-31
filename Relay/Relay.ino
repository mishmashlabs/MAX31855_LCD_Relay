int relay1 = 7;

void setup() {
  Serial.begin(9600);
  
  pinMode(relay1, OUTPUT);
  digitalWrite(relay1, HIGH);
}

void loop() {
  digitalWrite(relay1, LOW);
  Serial.println("Relay Pin Low");
  delay(3000);
  digitalWrite(relay1, HIGH);
  Serial.println("Relay Pin High");
  delay(3000);
}
