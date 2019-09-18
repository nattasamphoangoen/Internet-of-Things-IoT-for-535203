#include <IFTTTMaker.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <DHTesp.h>
#include "LedControl.h"
char ssid[] = "ssidstudent";
char password[] = "passtossid";
#define KEY "YourKeyStudent"
#define KEY1 "YourKeyTeacher"
#define EVENT_NAME_GOOGLESHEET "gapA"
#define EVENT_NAME_LINE "BTN2715"
#define EVENT_NAME_Teacher "lastCheck_Sec2"
DHTesp dht;
int button = 23;
int button1 = 22;
int dht22 = 19;
WiFiClientSecure client;
IFTTTMaker ifttt(KEY, client);
IFTTTMaker ifttt1(KEY1, client);
LedControl lc = LedControl(2, 5, 4, 1);
void setup() {
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
  dht.setup(dht22, DHTesp::DHT22);
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
  if (ifttt1.triggerEvent(EVENT_NAME_Teacher, "Panupong K.", "B6102715")) {
    Serial.println("Successfully sent");
  } else
  {
    Serial.println("Failed!");
  }
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

  if (temp > 30) {
    if (ifttt.triggerEvent(EVENT_NAME_LINE, "The ", "temperature ", "overheat")) {
      Serial.println("Successfully sent to Line");
      delay(2000);
    } else {
      Serial.println("Failed! sent to Line");
    }
  } else {
    if (ifttt.triggerEvent(EVENT_NAME_GOOGLESHEET, (String)temp, (String)humi)) {
      Serial.println("Successfully sent to Google sheet");
      delay(2000);
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
  delay(300);
}
