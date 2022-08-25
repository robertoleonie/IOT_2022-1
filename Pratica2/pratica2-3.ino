// PRATICA 2-3

const byte led_gpio = D2; // 32 no esp32
const byte foto_gpio = A0; // 25 no esp32

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, ESP32!"); 
  pinMode(led_gpio, OUTPUT);
  pinMode(foto_gpio, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(50); // this speeds up the simulation
  int max_analog = 1023; // 4095 no esp32 
  int foto_resistor = analogRead(foto_gpio);
  // imprime tensao lida
  Serial.println(map(foto_resistor, 0, max_analog, 0, 3300) / 1000.0);
  analogWrite(led_gpio, foto_resistor); 

}
