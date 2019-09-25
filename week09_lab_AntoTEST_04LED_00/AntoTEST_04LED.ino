#include <AntoIO.h>

int D1 = 18;
int D2 = 19;
int D3 = 22;
int D4 = 23;

const char *ssid = "ion00";
const char *pass = "ion12345";
const char *user = "UsertoAnto";
const char *token = "Key";
const char *thing = "UerThing";

const char *Chan1 = "channael";
const char *Chan2 = "channael";
const char *Chan3 = "channael";
const char *Chan4 = "channael";

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

  anto.mqtt.sub(Chan1);
  anto.mqtt.sub(Chan2);
  anto.mqtt.sub(Chan3);
  anto.mqtt.sub(Chan4);
}

void loop() {
  anto.mqtt.loop();
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
