#include <WiFi.h>
#include "ThingSpeak.h"
#include "DHTesp.h"
#include "LedControl.h"
#define dhtPin 23
char ssid[] = "TA_HOME";
char pass[] = "TA123456";
unsigned long myChannelNumber = 879253;
const char* myWriteAPIKey = "LP926859GD7BQNL0";
const char* myReadAPIKey = "709TV3NVBN834FU8";
LedControl lc = LedControl(15, 2, 19, 1);
WiFiClient client;
DHTesp dht;
void setup() {
  Serial.begin(9200);
  dht.setup(dhtPin, DHTesp::DHT11);
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
  ThingSpeak.begin(client);
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
}
int t, t1, t2, t3, h, h1, h2, h3;
void loop() {
  float humi = dht.getHumidity();
  float temp = dht.getTemperature();
  Serial.print("\nTemperature('C)= ");
  Serial.print(temp, 1);
  Serial.print("\tHumidity(%)= ");
  Serial.print(humi, 1);
  Serial.println();
  ThingSpeak.setField(1, temp);
  ThingSpeak.setField(2, humi);
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  for (int i = 'Z'; i >= 'A'; i--) {
    Serial.write(i);
    delay(200);
  }
  t = temp * 10;
  t1 = t / 100;
  t2 = t / 10 % 10;
  t3 = t % 10;
  h = humi * 10;
  h1 = h / 100;
  h2 = h / 10 % 10;
  h3 = h % 10;
  Serial.println(temp);
  lc.setDigit(0, 7, t1, false);
  lc.setDigit(0, 6, t2, true);
  lc.setDigit(0, 5, t3, false);
  lc.setRow(0, 4, B00001101);
  lc.setDigit(0, 3, h1, false);
  lc.setDigit(0, 2, h2, true);
  lc.setDigit(0, 1, h3, false);
  lc.setRow(0, 0, B00010111);
}
