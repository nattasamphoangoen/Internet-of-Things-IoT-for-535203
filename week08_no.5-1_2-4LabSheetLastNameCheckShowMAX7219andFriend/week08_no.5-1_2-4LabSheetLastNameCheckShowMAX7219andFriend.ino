#include <IFTTTMaker.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <DHTesp.h>
#include "LedControl.h"
char ssid[] = "ssidStudent";
char password[] = "pass==>ssid";
#define KEY "tokenkeyStudent"
#define KEY1 "tokenkeyTeacher"
#define KEY2 "tokenkeyFriend"
#define EVENT_NAME_GOOGLESHEET "EVENTStudenttoSentsheet"
#define EVENT_NAME_LINE "EVENTStudenttoSentLine"
#define EVENT_NAME_Teacher "EVENTTeacher"
#define EVENT_NAME_XXX "EVENTTeacher"
DHTesp dht;
int dht22 = 15;
WiFiClientSecure client;
IFTTTMaker ifttt(KEY, client);
IFTTTMaker ifttt1(KEY1, client);
IFTTTMaker ifttt2(KEY2, client);
LedControl lc = LedControl(22, 4, 23, 1);
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
  if (ifttt1.triggerEvent(EVENT_NAME_Teacher, "B6112455", "Wisanu Masurin",  WiFi.macAddress().c_str())) {
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

  if (ifttt2.triggerEvent(EVENT_NAME_XXX, (String)temp, (String)humi)) {
    Serial.println("Successfully sent to Google sheet xxx");
    delay(2000);
  } else {
    Serial.println("Failed! sent to Google sheet xxx");
    delay(2000);
  }

  if (temp > 28) {
    if (ifttt.triggerEvent(EVENT_NAME_LINE, "The ", "temperature ", "overheat")) {
      Serial.println("Successfully sent to Line");
      delay(2000);
    } else {
      Serial.println("Failed! sent to Line");
      delay(2000);
    }
  } else {
    if (ifttt.triggerEvent(EVENT_NAME_GOOGLESHEET, (String)temp, (String)humi)) {
      Serial.println("Successfully sent to Google sheet");
      delay(2000);
    } else {
      Serial.println("Failed! sent to Google sheet");
      delay(2000);
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
