#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "DHTesp.h"
char auth[] = "7g05BDyCQD6pVBK-BXVnsRhqUwZuqnlL";

char ssid[] = "ion00";
char pass[] = "ion12345";
DHTesp dht;
BlynkTimer timer;
void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  dht.setup(23, DHTesp::DHT11);
  timer.setInterval(5000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}

void sendSensor()
{
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();
  Serial.println(temperature);
  Serial.println(humidity);
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V0, temperature);
  Blynk.virtualWrite(V1, humidity);
}
