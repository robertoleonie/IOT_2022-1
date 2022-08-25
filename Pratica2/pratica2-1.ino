#include <ESP8266WiFi.h>

const char* ssid     = "DCC-LCI";
const char* password = "aluno.dcc!";
const char* previousWifiStatus = "";

void setup() {
  Serial.begin(115200);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
}

void loop() {
  const char* wifiStatus = Wifi.status();

  if (wifiStatus != WL_CONNECTED) {
    if (wifiStatus != previousWifiStatus) {
      Serial.print(wifiStatus);
      previousWifiStatus = wifiStatus;
      wifiStatus = Wifi.status();
    }
    delay(500);
    Serial.print(".");
  } else {
    Serial.println("");
    Serial.println("WiFi connected!");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    delay(30000);
  }
}
