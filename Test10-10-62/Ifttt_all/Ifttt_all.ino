#include <IFTTTMaker.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <DHTesp.h>
#include "LedControl.h"
char ssid[] = "TA_HOME";
char password[] = "TA123456";
#define KEY "hK2P_R3jm24tUl15IkAPUJ7_TobcZeypSpb1t9VNaac"

#define EVENT_NAME_GOOGLESHEET "Esp32Test"
#define EVENT_NAME_mess "Tem"
#define EVENT_NAME_page "Hum"
DHTesp dht;

int dht22 = 23;
WiFiClientSecure client;
IFTTTMaker ifttt(KEY, client);

LedControl lc = LedControl(15, 2, 19, 1);
void setup() {
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
  dht.setup(dht22, DHTesp::DHT11);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);

}
int t, t1, t2, t3, h, h1, h2, h3;
void loop() {
  float temp = dht.getTemperature();
  float humi = dht.getHumidity();
  t = temp * 10;
  t1 = t / 100;
  t2 = t / 10 % 10;
  t3 = t % 10;
  h = humi * 10;
  h1 = h / 100;
  h2 = h / 10 % 10;
  h3 = h % 10;
  Serial.println(temp);

  if (temp > 28) {
    if (ifttt.triggerEvent(EVENT_NAME_mess, "The ", "temperature ", "overheat")) {
      Serial.println("Successfully sent to mess");
    } else {
      Serial.println("Failed! sent to mess");
    }
  } else if (temp < 28) {
    if (ifttt.triggerEvent(EVENT_NAME_page, (String)temp, (String)humi)) {
      Serial.println("Successfully sent to Google page");
    } else {
      Serial.println("Failed! sent to Google page");
    }
  } else {
    if (ifttt.triggerEvent(EVENT_NAME_GOOGLESHEET, (String)temp, (String)humi)) {
      Serial.println("Successfully sent to Google sheet");
    } else {
      Serial.println("Failed! sent to Google sheet");
    }
  }

  lc.setDigit(0, 7, t1, false);
  lc.setDigit(0, 6, t2, true);
  lc.setDigit(0, 5, t3, false);
  lc.setRow(0, 4, B00001101);
  lc.setDigit(0, 3, h1, false);
  lc.setDigit(0, 2, h2, true);
  lc.setDigit(0, 1, h3, false);
  lc.setRow(0, 0, B00010111);
  delay(3000);
}
