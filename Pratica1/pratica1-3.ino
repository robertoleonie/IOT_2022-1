int sensorPin = A0;
int ledPin = D1;
int sensorValue = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  // (INTERNAL);
  digitalWrite(ledPin, LOW);
}

void loop(){
  sensorValue = analogRead(sensorPin)*5;
  //sensorValue /= 4;
  delay(sensorValue);
  digitalWrite(ledPin, 0);
  delay(sensorValue);
  digitalWrite(ledPin, 1);
}
