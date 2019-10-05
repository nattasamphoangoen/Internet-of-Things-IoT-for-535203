#include <AntoIO.h>
#include "DHTesp.h"
DHTesp dht;
#include "LedControl.h"
const char *ssid = "TA_HOME";
const char *pass = "TA123456";
const char *user = "Newnatta_1";
const char *token = "s1tkp4z9T12Z8873BZt0WXSZ0OdCnRgcz0BnLV17";
const char *thing = "Esp32";
const char *channel_01 = "led01";
const char *channel_02 = "led02";
const char *channel_03 = "Tem";
const char *channel_04 = "Hum";
const char *channel_05 = "sw1";
const char *channel_06 = "sw2";
#define sw_01 21
#define sw_02 22
int sts_sw_01;
int sts_sw_02;
AntoIO anto(user, token, thing);
int LED01 = 4;
int LED02 = 5;
LedControl lc = LedControl(15, 2, 19, 1);
void setup() {
  pinMode(LED01, OUTPUT);
  pinMode(LED02, OUTPUT);
  pinMode(sw_01, INPUT_PULLUP);
  pinMode(sw_02, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.print("\nTrying to connect ");
  Serial.print(ssid);
  Serial.println("...");
  while (!anto.wifi.begin(ssid, pass));
  Serial.println("\nConnected, trying to connect to broker...");
  while (!anto.mqtt.connect(user, token, true));
  Serial.println("\nConnected");
  dht.setup(23, DHTesp::DHT11);
  anto.mqtt.sub(channel_01);
  anto.mqtt.sub(channel_02);
  anto.mqtt.sub(channel_03);
  anto.mqtt.sub(channel_04);
  anto.mqtt.sub(channel_05);
  anto.mqtt.sub(channel_06);
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
}
int counter = 0;
int t, t1, t2, t3, h, h1, h2, h3;
void loop() {
  anto.mqtt.loop();
  if (sts_sw_01 != digitalRead(sw_01)) {
    sts_sw_01 = digitalRead(sw_01);
    anto.mqtt.pub(channel_05, sts_sw_01);
    Serial.print("status sw1="); Serial.println(sts_sw_01);
    delay(100);
  }
  delay(10); //swit2
  if (sts_sw_02 != digitalRead(sw_02)) {
    sts_sw_02 = digitalRead(sw_02);
    anto.mqtt.pub(channel_06, sts_sw_02);
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
  if (topic.indexOf(channel_01) != -1) {
    if (payload.toInt() == 1) {
      digitalWrite(LED01, HIGH);
      Serial.println("HIGH 01");
    } else {
      digitalWrite(LED01, LOW);
      Serial.println("LOW 01");
    }
  } else if (topic.indexOf(channel_02) != -1) {
    if (payload.toInt() == 1) {
      digitalWrite(LED02, HIGH);
      Serial.println("HIGH 02");
    } else {
      digitalWrite(LED02, LOW);
      Serial.println("LOW 02");
    }
  }
}


void publish_Display() {
  float temp = dht.getTemperature();
  float humi = dht.getHumidity();
  anto.mqtt.pub(channel_03, temp);
  anto.mqtt.pub(channel_04, humi);
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
