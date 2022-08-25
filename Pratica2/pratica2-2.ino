// PRATICA 2-2

const byte led_gpio = D2;  // 32 no esp32
const byte botao_gpio = D5; // 25 no esp32
int estado_botao;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, ESP32!"); 
  pinMode(led_gpio, OUTPUT);
  pinMode(botao_gpio, INPUT_PULLUP);
  estado_botao = digitalRead(botao_gpio); 
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(50); // this speeds up the simulation

  /*
  // SUBIDA
  if (digitalRead(botao_gpio) == HIGH)
    digitalWrite(led_gpio, HIGH);
  else
    digitalWrite(led_gpio, LOW);
  
  // DESCIDA
  if (digitalRead(botao_gpio) == LOW)
    digitalWrite(led_gpio, HIGH);
  else
    digitalWrite(led_gpio, LOW);
  */

  // AMBOS
  if (digitalRead(botao_gpio) != estado_botao) {
    digitalWrite(led_gpio, HIGH);
    estado_botao = digitalRead(botao_gpio); // troca os estados
    delay(50);
  }
  else
    digitalWrite(led_gpio, LOW);

}
