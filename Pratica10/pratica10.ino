#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "DHTesp.h"
#include <Servo.h>

Servo servo;


DHTesp dhtSensor;

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BMP280 bmp; // I2C
//Adafruit_bmp280 bmp(bmp_CS); // hardware SPI
//Adafruit_bmp280 bmp(bmp_CS, bmp_MOSI, bmp_MISO, bmp_SCK); // software SPI

unsigned long delayTime;

// Update these with values suitable for your network.

const char* ssid = "DCC-LCI";
const char* password = "aluno.dcc!";
const char* mqtt_server = "test.mosquitto.org";

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;
int foto_button = 1;

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());
  
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }

  if(topic == "motorIoT2022") {
    int grau = (int) payload;
    servo.write(grau);
  }

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  } else {
    digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.subscribe("motorIoT2022");
    } else {
      Serial.print("failed, rc=");
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

String readTemp() {
  // temperatura em celcius
  TempAndHumidity  data = dhtSensor.getTempAndHumidity();
  return String(data.temperature, 2);
}

String readPreassure() {
  return String(bmp.readPressure() / 100.0F);
}

String readAltitude() {
  return String(bmp.readAltitude(SEALEVELPRESSURE_HPA));
}

String readHumidity() {
  // umidade relativa
  TempAndHumidity  data = dhtSensor.getTempAndHumidity();
  return String(data.humidity, 1);
}

String readFROne() {
  digitalWrite(D5, 0);
  delay(10);
  int pinRead = analogRead(A0);
  return String(pinRead);
}

String readFRTwo() {
  digitalWrite(D5, 1);
  delay(10);
  int pinRead = analogRead(A0);
  return String(pinRead);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(D5, OUTPUT);
  dhtSensor.setup(D6, DHTesp::DHT22);
  servo.attach(D4);

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  bool status;
  // default settings
  // (you can also pass in a Wire library object like &Wire2)
  status = bmp.begin(0x76);  

  Serial.println("-- Default Test --");
  delayTime = 1000;

}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    client.publish("temp", readTemp().c_str());
    client.publish("pres", readPreassure().c_str());
    Serial.println(readHumidity());
    client.publish("hum", readHumidity().c_str());
    client.publish("foto_1", readFROne().c_str());  
    client.publish("foto_2", readFRTwo().c_str());
    client.publish("alt", readAltitude().c_str());
  }
  delay(delayTime);
}
