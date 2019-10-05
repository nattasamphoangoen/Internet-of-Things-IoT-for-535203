#include <WiFi.h>
#include "ThingSpeak.h"
WiFiClient client;
#define LED_01 15
#define LED_02 2
#define LED_03 22
#define LED_04 23
char ssid[] = "ssid"; 
char pass[] = "pass"; 
unsigned long myChannelNumber = 00000;
const char* myWriteAPIKey = "xxxxxxxxx";
const char* myReadAPIKey = "yyyyyyyyy";

unsigned long weatherStationChannelNumber = 12397;
void setup() {
  Serial.begin(115200);
  pinMode(LED_01, OUTPUT);
  pinMode(LED_02, OUTPUT);
  pinMode(LED_03, OUTPUT);
  pinMode(LED_04, OUTPUT);
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
}
void loop() {
  int Cmd_LED = ThingSpeak.readFloatField(myChannelNumber, 1, myReadAPIKey);
  Serial.print("Latest Data is: ");
  Serial.println(Cmd_LED);
  if (Cmd_LED == 11)digitalWrite(LED_01, HIGH);
  if (Cmd_LED == 10)digitalWrite(LED_01, LOW);
  if (Cmd_LED == 21)digitalWrite(LED_02, HIGH);
  if (Cmd_LED == 20)digitalWrite(LED_02, LOW);
  if (Cmd_LED == 31)digitalWrite(LED_03, HIGH);
  if (Cmd_LED == 30)digitalWrite(LED_03, LOW);
  if (Cmd_LED == 41)digitalWrite(LED_04, HIGH);
  if (Cmd_LED == 40)digitalWrite(LED_04, LOW);
  if (Cmd_LED == 9) {
    digitalWrite(LED_01, HIGH);
    digitalWrite(LED_02, HIGH);
    digitalWrite(LED_03, HIGH);
    digitalWrite(LED_04, HIGH);
  }
  if (Cmd_LED == 0) {
    digitalWrite(LED_01, LOW);
    digitalWrite(LED_02, LOW);
    digitalWrite(LED_03, LOW);
    digitalWrite(LED_04, LOW);
  }
  delay(3000);
}
