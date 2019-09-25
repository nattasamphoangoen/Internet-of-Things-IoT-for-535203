#include <LedControl.h>
LedControl lc = LedControl(21, 18, 19, 1);
unsigned long delaytime = 250;
#include <WiFi.h>
#include <HTTPClient.h>
const char *ssid = "AAA"; //ชื่อ HP.
const char *pass = "pass";
const char *Anto_URL = "http://api.anto.io/request/";
const char *token = "asasasasasasasaaaaaaaaaaaaaaaaaa";
const char *Data1 = "/gas.91e10.price";
const char *Data2 = "/gas.95e10.price";
const char *Data3 = "/gas.95e20.price";
const char *Data4 = "/gas.hsd.price";
char get_URL1[150];
char get_URL2[150];
char get_URL3[150];
char get_URL4[150];
int pp;
int p1;
int p2;
int p3;
int p4;
void setup()
{
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
  Serial.begin(115200);
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
void loop()
{
  float Price_GAS91E10;
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    strcpy(get_URL1, Anto_URL);
    strcat(get_URL1, token);
    strcat(get_URL1, Data1);
    strcpy(get_URL2, Anto_URL);
    strcat(get_URL2, token);
    strcat(get_URL2, Data2);
    strcpy(get_URL3, Anto_URL);
    strcat(get_URL3, token);
    strcat(get_URL3, Data3);
    strcpy(get_URL4, Anto_URL);
    strcat(get_URL4, token);
    strcat(get_URL4, Data4);
    http.begin(get_URL1);
    int httpCode1 = http.GET();
    if (httpCode1 > 0) {
      String payload1 = http.getString();
      Serial.println(payload1);
      int nLoct1 = payload1.indexOf(',');
      String cString1 = payload1.substring(nLoct1 + 10, nLoct1 + 15);
      Price_GAS91E10 = cString1.toFloat();
      Serial.println(Price_GAS91E10);
      pp = Price_GAS91E10 * 100;
      p1 = pp % 10;
      p2 = (pp % 100 - p1) / 10;
      p3 = (pp % 1000 - p1 - p2) / 100;
      p4 = pp / 1000;
      lc.setDigit(0, 7, 6, false);
      lc.setChar(0, 6, '_', false);
      lc.setDigit(0, 5, 9, false);
      lc.setDigit(0, 4, 1, false);
      lc.setDigit(0, 3, p4, false);
      lc.setDigit(0, 2, p3, false);
      lc.setDigit(0, 1, p2, false);
      lc.setDigit(0, 0, p1, false);
      delay(500);
    }
    http.begin(get_URL2);
    int httpCode2 = http.GET();
    if (httpCode2 > 0) {
      String payload2 = http.getString();
      Serial.println(payload2);
      int nLoct2 = payload2.indexOf(',');
      String cString2 = payload2.substring(nLoct2 + 10, nLoct2 + 15);
      Price_GAS91E10 = cString2.toFloat();
      Serial.println(Price_GAS91E10);
      pp = Price_GAS91E10 * 100;
      p1 = pp % 10;
      p2 = (pp % 100 - p1) / 10;
      p3 = (pp % 1000 - p1 - p2) / 100;
      p4 = pp / 1000;
      lc.setDigit(0, 7, 6, false);
      lc.setChar(0, 6, '_', false);
      lc.setDigit(0, 5, 9, false);
      lc.setDigit(0, 4, 5, false);
      lc.setDigit(0, 3, p4, false);
      lc.setDigit(0, 2, p3, true);
      lc.setDigit(0, 1, p2, false);
      lc.setDigit(0, 0, p1, false);
      delay(500);
    }
    http.begin(get_URL3);
    int httpCode3 = http.GET();
    if (httpCode3 > 0) {
      String payload3 = http.getString();
      Serial.println(payload3);
      int nLoct3 = payload3.indexOf(',');
      String cString3 = payload3.substring(nLoct3 + 10, nLoct3 + 15);
      Price_GAS91E10 = cString3.toFloat();
      Serial.println(Price_GAS91E10);
      pp = Price_GAS91E10 * 100;
      p1 = pp % 10;
      p2 = (pp % 100 - p1) / 10;
      p3 = (pp % 1000 - p1 - p2) / 100;
      p4 = pp / 1000;
      lc.setChar(0, 7, 'E', false);
      lc.setChar(0, 6, '_', false);
      lc.setDigit(0, 5, 2, false);
      lc.setDigit(0, 4, 0, false);
      lc.setDigit(0, 3, p4, false);
      lc.setDigit(0, 2, p3, true);
      lc.setDigit(0, 1, p2, false);
      lc.setDigit(0, 0, p1, false);
      delay(500);
    }
    http.begin(get_URL4);
    int httpCode4 = http.GET();
    if (httpCode4 > 0) {
      String payload4 = http.getString();
      Serial.println(payload4);
      int nLoct4 = payload4.indexOf(',');
      String cString4 = payload4.substring(nLoct4 + 10, nLoct4 + 15);
      Price_GAS91E10 = cString4.toFloat();
      Serial.println(Price_GAS91E10);
      pp = Price_GAS91E10 * 100;
      p1 = pp % 10;
      p2 = (pp % 100 - p1) / 10;
      p3 = (pp % 1000 - p1 - p2) / 100;
      p4 = pp / 1000;
      lc.setDigit(0, 7, 5, false);
      lc.setDigit(0, 6, 0, false);
      lc.setChar(0, 5, 'L', false);
      lc.setChar(0, 4, 'A', false);
      lc.setDigit(0, 3, p4, false);
      lc.setDigit(0, 2, p3, true);
      lc.setDigit(0, 1, p2, false);
      lc.setDigit(0, 0, p1, false);
      delay(500);
    }
    http.end();
  }
}
