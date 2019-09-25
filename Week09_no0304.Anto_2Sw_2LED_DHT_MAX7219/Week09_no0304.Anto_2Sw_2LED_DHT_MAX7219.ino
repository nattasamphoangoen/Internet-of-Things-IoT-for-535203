#include <AntoIO.h>
#include "LedControl.h"
#include "DHTesp.h"
DHTesp dht;

int D3 = 22;
int D4 = 23;
#define sw_01 5
#define sw_02 4
int sts_sw_01;
int sts_sw_02;
const char *ssid = "ssid";
const char *pass = "pass";
const char *user = "BBBBBBBBBB";
const char *token = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
const char *thing = "test4led";

const char *Chan3 = "Led03";
const char *Chan4 = "Led04";
const char *Chan5 = "sw_01";
const char *Chan6 = "sw_02";
const char *ChanT = "temp1";
const char *ChanH = "hum1";
LedControl lc = LedControl(21, 2, 18, 1);
int counter = 0;
AntoIO anto(user, token, thing);
void setup() {
  Serial.begin(9600);
  Serial.print("\nTrying to connect ");
  Serial.print(ssid);
  Serial.println("...");
  while (!anto.wifi.begin(ssid, pass));
  Serial.println("\nConnected, trying to connect to broker...");
  while (!anto.mqtt.connect(user, token, true));
  Serial.println("\nConnected");
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(sw_01, INPUT_PULLUP);
  pinMode(sw_02, INPUT_PULLUP);

  anto.mqtt.sub(Chan3);
  anto.mqtt.sub(Chan4);
  anto.mqtt.sub(Chan5);
  anto.mqtt.sub(Chan6);
  anto.mqtt.sub(ChanT);
  anto.mqtt.sub(ChanH);
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
  dht.setup(15, DHTesp::DHT22);
}
void loop() {
  anto.mqtt.loop();
  //swit1
  if (sts_sw_01 != digitalRead(sw_01)) {
    sts_sw_01 = digitalRead(sw_01);
    anto.mqtt.pub(Chan5, sts_sw_01);
    Serial.print("status sw1="); Serial.println(sts_sw_01);
    delay(100);
  }
  delay(10); //swit2
  if (sts_sw_02 != digitalRead(sw_02)) {
    sts_sw_02 = digitalRead(sw_02);
    anto.mqtt.pub(Chan6, sts_sw_02);
    Serial.print("status sw2="); Serial.println(sts_sw_02);
    delay(100);
  }
  counter++;
  if (counter % 200 == 0) {
    publish_Display();
  }
  delay(10);
}
void messageReceived(String topic, String payload, char * bytes, unsigned int length) {
  Serial.print("incoming: ");
  Serial.print(topic);
  Serial.print(" - ");
  Serial.print(payload);
  Serial.println();
  if (topic.indexOf(Chan3) != -1) {
    if (payload.toInt() == 1) {
      digitalWrite(D3, HIGH);
      Serial.println("HIGH");
    } else {
      digitalWrite(D3, LOW);
      Serial.println("LOW");
    }
  } else if (topic.indexOf(Chan4) != -1) {
    if (payload.toInt() == 1) {
      digitalWrite(D4, HIGH);
      Serial.println("HIGH");
    } else {
      digitalWrite(D4, LOW);
      Serial.println("LOW");
    }
  }
}
int t, t1, t2, t3, h, h1, h2, h3;
void publish_Display() {
  float temp = dht.getTemperature();
  float humi = dht.getHumidity();
  anto.mqtt.pub(ChanT, temp);
  anto.mqtt.pub(ChanH, humi);
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
