#include <DHT.h> 
#define DHTPIN 2
#define DHTTYPE DHT11
#include <WiFi.h>
#include "ThingSpeak.h"

DHT dht(DHTPIN, DHTTYPE);
WiFiServer server(80);
WiFiClient  client;
const char* ssid = "brisa-2193534";
const char* password =  "2cnjtqgn";
const char * writeAPIKey = "D12FHVE2CL3ODURA";
const char * readAPIKey = "PFAKBKYFLFHBMCK9";
unsigned long channelNumber = 1737635;

void setup() {
  Serial.begin(9200);
  WiFi.begin(ssid, password);
  WiFi.mode(WIFI_MODE_STA);
  ThingSpeak.begin(client);
  Serial.println(WiFi.macAddress());
}

void loop() {
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("Connecting to WiFi ");
    Serial.println(ssid);
  }
  Serial.print("Connected to the WiFi network (");
  Serial.print(WiFi.localIP());
  Serial.println(")");
  //int humidity = dht.readHumidity();
  int humidity = random(100);
  //int temperature = dht.readTemperature();
  int temperature = random(35);
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" *C | ");
  Serial.print("Humidity: "); 
  Serial.println(humidity);
  ThingSpeak.setField(1, temperature);
  ThingSpeak.setField(2, humidity);
  int x = ThingSpeak.writeField(channelNumber, writeAPIKey);
  if(x == 200){
    Serial.println("Channel update successful " + String(x));
  } else {
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  delay(16000);
}
