int sensorPin = A0;
int buzzerPin = D2;
int sensorValue = 0;
int serialData = 0;

void setup() {
  Serial.begin(115200);
  digitalWrite(buzzerPin, 200*serialData);
}

void loop(){
  // sensorValue = analogRead(sensorPin)*5;
  // sensorValue /= 4;
  delay(5000);
  serialData = Serial.read(DEC);
  analogWriteFreq(200*serialData);
  analogWrite(buzzerPin, 512);
}
