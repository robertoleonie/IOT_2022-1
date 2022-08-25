#include <TM1637Display.h>
#include <Servo.h>

TM1637Display display(D6, D5);
Servo servo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  servo.attach(D4);
  display.setBrightness(255);
}

void loop() {
  Serial.print("Lendo o valor da tensao...");
  int tensao = map(analogRead(A0), 0, 1024, 0, 3300);
  Serial.println(tensao);
  int grau = map(tensao, 0, 3300, 0, 90);
  servo.write(grau);
  Serial.print("Graus do giro do servo: ");
  Serial.println(grau);
  showLed(grau, tensao);
  delay(10);
}

void showLed(int grau, int tensao) {
  display.showNumberDec(tensao);
  // delay(2000);
  // display.showNumberDec(grau);
  // delay(2000);
}
