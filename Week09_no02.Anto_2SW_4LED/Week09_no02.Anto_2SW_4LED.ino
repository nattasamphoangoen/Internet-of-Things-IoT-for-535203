#include <AntoIO.h>
DHTesp dht;
int D1 = 18;
int D2 = 19;
int D3 = 22;
int D4 = 23;
#define sw_01 5
#define sw_02 4
int sts_sw_01;
int sts_sw_02;
const char *ssid = "ssid";
const char *pass = "pass";
const char *user = "aaaaaaaaaaaaaaaa";
const char *token = "ASASASSASSASSSASASASA";
const char *thing = "test4led";
const char *Chan1 = "Led01";
const char *Chan2 = "Led02";
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
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(sw_01, INPUT_PULLUP);
  pinMode(sw_02, INPUT_PULLUP);
  anto.mqtt.sub(Chan1);
  anto.mqtt.sub(Chan2);
  anto.mqtt.sub(Chan3);
  anto.mqtt.sub(Chan4);
  anto.mqtt.sub(Chan5);
  anto.mqtt.sub(Chan6);

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
  
  delay(10);
}
void messageReceived(String topic, String payload, char * bytes, unsigned int length) {
  Serial.print("incoming: ");
  Serial.print(topic);
  Serial.print(" - ");
  Serial.print(payload);
  Serial.println();
  if (topic.indexOf(Chan1) != -1) {
    if (payload.toInt() == 1) {
      digitalWrite(D1, HIGH);
      Serial.println("HIGH");
    } else {
      digitalWrite(D1, LOW);
      Serial.println("LOW");
    }
  } else if (topic.indexOf(Chan2) != -1) {
    if (payload.toInt() == 1) {
      digitalWrite(D2, HIGH);
      Serial.println("HIGH");
    } else {
      digitalWrite(D2, LOW);
      Serial.println("LOW");
    }
  } else if (topic.indexOf(Chan3) != -1) {
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
