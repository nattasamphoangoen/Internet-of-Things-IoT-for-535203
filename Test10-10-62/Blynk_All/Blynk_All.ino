#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "DHTesp.h"
#include "LedControl.h"
char auth[] = "cKhT2tarln1022Vxub2kzoJQRDDMJcVL";
char ssid[] = "TA_HOME";
char pass[] = "TA123456";
DHTesp dht;
BlynkTimer timer;
LedControl lc = LedControl(15, 2, 19, 1);
void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  dht.setup(23, DHTesp::DHT11);
  timer.setInterval(5000L, sendSensor);
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
}

void loop()
{
  Blynk.run();
  timer.run();
}
int t, t1, t2, t3, h, h1, h2, h3;
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
  t = temperature * 10;
  h = humidity * 10;
  t1 = t / 100;
  t2 = t / 10 % 10;
  t3 = t % 10;
  h1 = h / 100;
  h2 = h / 10 % 10;
  h3 = h % 10;
  lc.setDigit(0, 7, t1, false);
  lc.setDigit(0, 6, t2, true);
  lc.setDigit(0, 5, t3, false);
  lc.setChar(0, 4, 'c', false);
  lc.setDigit(0, 3, h1, false);
  lc.setDigit(0, 2, h2, true);
  lc.setDigit(0, 1, h3, false);
  lc.setChar(0, 0, 'h', false);
  Blynk.virtualWrite(V0, temperature);
  Blynk.virtualWrite(V1, humidity);
}
