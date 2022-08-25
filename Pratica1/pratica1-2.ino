void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Lendo o valor da tensao...");
  delay(200);
  Serial.println(analogRead(A0));
}
