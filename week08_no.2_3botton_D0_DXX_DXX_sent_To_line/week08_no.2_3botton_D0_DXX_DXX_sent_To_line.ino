#include <IFTTTMaker.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <DHTesp.h>

char ssid[] = "ssidToStudent";
char password[] = "passTossid";
#define KEY "YourKeytoIftt"
#define EVENT_NAME1 "even"

DHTesp dht;
int button = 0;
int button1 = 23;
int button2 = 22;
int dht22 = 5;

WiFiClientSecure client;
IFTTTMaker ifttt(KEY, client);

void setup() {
  dht.setup(dht22);
  Serial.begin(115200);
  pinMode(button, INPUT);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);

 
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

}

void loop() {

  float temp = dht.getTemperature();

  float humi = dht.getHumidity();
  int b1 = digitalRead(button);
  int b2 = digitalRead(button1);
  int b3 = digitalRead(button2);
  Serial.print("b1 = ");
  Serial.println(b1);
  Serial.print("b2 = ");
  Serial.println(b2);
  Serial.print("b3 = ");
  Serial.println(b3);

  if ( b1 == 0) {
    ifttt.triggerEvent(EVENT_NAME1, "Panupong", "B6102715");
    Serial.println("Successfully sent to D0");
    while (digitalRead(button) == LOW);
  } else if (b2 == 0) {
    ifttt.triggerEvent(EVENT_NAME1, "715", "???");
    Serial.println("Successfully sent to D23");
    while (digitalRead(button1) == LOW);
  } else if (b3 == 0) {
    ifttt.triggerEvent(EVENT_NAME1, "IGOT", "A");
    Serial.println("Successfully sent to D22");
    while (digitalRead(button2) == LOW);
  }

  delay(300);

}
