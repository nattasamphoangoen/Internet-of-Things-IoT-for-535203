#include <WiFi.h>
#include <HTTPClient.h>
#include "LedControl.h"
LedControl lc = LedControl(21, 2, 18, 1);
const char *ssid = "sddddddddd"; //ชื่อ HP.
const char *pass = "pass";
const char *Anto_URL = "https://api.anto.io/request/";
char *get_URL_91e10 = "https://api.anto.io/.../4C8AbxjB2dr0zjusT.../gas.91e10.price";
char *get_URL_95e10 = "https://api.anto.io/.../4C8AbxjB2dr0zjusT.../gas.95e10.price";
char *get_URL_hsd = "https://api.anto.io/.../4C8AbxjB2dr0zjusTQn.../gas.hsd.price";
char *get_URL_95e20 = "https://api.anto.io/.../4C8AbxjB2dr0zjusT.../gas.95e20.price";
void setup() {
  Serial.begin(9600);
  Serial.print("\nTrying to connect ");
  Serial.print(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\nWiFi Connected");
  Serial.print("\nIP address");
  Serial.print("\nWiFi.localIP()");
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
}
void loop() {
  float Price_GAS91e10;
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http1;
    http1.begin(get_URL_91e10);
    int httpCode1 = http1.GET();
    if (httpCode1 > 0) {
      String payload1 = http1.getString();
      Serial.println(payload1);
      int nLoct1 = payload1.indexOf(',');
      String cString1 = payload1.substring(nLoct1 + 10, nLoct1 + 15);
      Serial.println(cString1);
      Price_GAS91e10 = cString1.toFloat();
    }
    int GAS0 = Price_GAS91e10 * 100;
    int GAS1 = GAS0 / 1000;
    int GAS2 = (GAS0 / 100) % 10;
    int GAS3 = (GAS0 / 10) % 10;
    int GAS4 = (GAS0 % 10);
    lc.setDigit(0, 7, 6, false);
    lc.setRow(0, 6, B00001000);
    lc.setDigit(0, 5, 9, false);
    lc.setDigit(0, 4, 1, false);
    lc.setDigit(0, 3, GAS1, false);
    lc.setDigit(0, 2, GAS2, true);
    lc.setDigit(0, 1, GAS3, false);
    lc.setDigit(0, 0, GAS4, false);
    http1.end();
  }
  delay(3000);
  float Price_GAS95e10;
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http2;
    http2.begin(get_URL_95e10);
    int httpCode2 = http2.GET();
    if (httpCode2 > 0) {
      String payload2 = http2.getString();
      Serial.println(payload2);
      int nLoct2 = payload2.indexOf(',');
      String cString2 = payload2.substring(nLoct2 + 10, nLoct2 + 15);
      Serial.println(cString2);
      Price_GAS95e10 = cString2.toFloat();
    }
    int GAS0 = Price_GAS95e10 * 100;
    int GAS1 = GAS0 / 1000;
    int GAS2 = (GAS0 / 100) % 10;
    int GAS3 = (GAS0 / 10) % 10;
    int GAS4 = (GAS0 % 10);
    lc.setDigit(0, 7, 6, false);
    lc.setRow(0, 6, B00001000);
    lc.setDigit(0, 5, 9, false);
    lc.setDigit(0, 4, 5, false);
    lc.setDigit(0, 3, GAS1, false);
    lc.setDigit(0, 2, GAS2, true);
    lc.setDigit(0, 1, GAS3, false);
    lc.setDigit(0, 0, GAS4, false);
    http2.end();
  }
  delay(3000);
  float Price_hsd;
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http3;
    http3.begin(get_URL_hsd);
    int httpCode3 = http3.GET();
    if (httpCode3 > 0) {
      String payload3 = http3.getString();
      Serial.println(payload3);
      int nLoct3 = payload3.indexOf(',');
      String cString3 = payload3.substring(nLoct3 + 10, nLoct3 + 15);
      Serial.println(cString3);
      Price_hsd = cString3.toFloat();
    }
    int GAS0 = Price_hsd * 100;
    int GAS1 = GAS0 / 1000;
    int GAS2 = (GAS0 / 100) % 10;
    int GAS3 = (GAS0 / 10) % 10;
    int GAS4 = (GAS0 % 10);
    lc.setDigit(0, 7, 5, false);
    lc.setDigit(0, 6, 0, false);
    lc.setRow(0, 5, B00001110);
    lc.setRow(0, 4, B01110111);
    lc.setDigit(0, 3, GAS1, false);
    lc.setDigit(0, 2, GAS2, true);
    lc.setDigit(0, 1, GAS3, false);
    lc.setDigit(0, 0, GAS4, false);
    http3.end();
  }
  delay(3000);
  float Price_E20;
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http3;
    http3.begin(get_URL_95e20);
    int httpCode3 = http3.GET();
    if (httpCode3 > 0) {
      String payload3 = http3.getString();
      Serial.println(payload3);
      int nLoct3 = payload3.indexOf(',');
      String cString3 = payload3.substring(nLoct3 + 10, nLoct3 + 15);
      Serial.println(cString3);
      Price_E20 = cString3.toFloat();
    }
    int GAS0 = Price_E20 * 100;
    int GAS1 = GAS0 / 1000;
    int GAS2 = (GAS0 / 100) % 10;
    int GAS3 = (GAS0 / 10) % 10;
    int GAS4 = (GAS0 % 10);
    lc.setRow(0, 7, B01001111);
    lc.setRow(0, 6, B00001000);
    lc.setDigit(0, 5, 2, false);
    lc.setDigit(0, 4, 0, false);
    lc.setDigit(0, 3, GAS1, false);
    lc.setDigit(0, 2, GAS2, true);
    lc.setDigit(0, 1, GAS3, false);
    lc.setDigit(0, 0, GAS4, false);
    http3.end();
  }
  delay(3000);
}
