/*********
  Complete project details at https://randomnerdtutorials.com  
*********/

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

/*#include <SPI.h>
#define bmp_SCK 14
#define bmp_MISO 12
#define bmp_MOSI 13
#define bmp_CS 15*/

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BMP280 bmp; // I2C
//Adafruit_bmp280 bmp(bmp_CS); // hardware SPI
//Adafruit_bmp280 bmp(bmp_CS, bmp_MOSI, bmp_MISO, bmp_SCK); // software SPI

unsigned long delayTime;

void setup() {
  Serial.begin(115200);
  Serial.println(F("BMP280 test"));

  bool status;

  // default settings
  // (you can also pass in a Wire library object like &Wire2)
  status = bmp.begin(0x76);  
 // if (!status) {
 //   Serial.println("Could not find a valid bmp280 sensor, check wiring!");
 //   while (1);
 // }

  Serial.println("-- Default Test --");
  delayTime = 1000;

  Serial.println();
}

void loop() { 
  printValues();
  delay(delayTime);
}

void printValues() {
  Serial.print("Temperature = ");
  Serial.print(bmp.readTemperature());
  Serial.println(" *C");
  
  // Convert temperature to Fahrenheit
  /*Serial.print("Temperature = ");
  Serial.print(1.8 * bmp.readTemperature() + 32);
  Serial.println(" *F");*/
  
  Serial.print("Pressure = ");
  Serial.print(bmp.readPressure() / 100.0F);
  Serial.println(" hPa");

  Serial.print("Approx. Altitude = ");
  Serial.print(bmp.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");

  /*Serial.print("Humidity = ");
  Serial.print(bmp.readHumidity());
  Serial.println(" %"); */

  Serial.println();
}
