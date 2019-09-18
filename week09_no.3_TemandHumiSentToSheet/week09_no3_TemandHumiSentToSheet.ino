#include <IFTTTMaker.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <DHTesp.h>
char ssid[] = "ssidstudent";
char password[] = "passtossid";
#define KEY "YourKeyStudent"
#define EVENT_NAME_GOOGLESHEET "gapA"
#define EVENT_NAME_LINE "BTN2715"

DHTesp dht;
int dht22 = 19;
WiFiClientSecure client;
IFTTTMaker ifttt(KEY, client);

void setup() {

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

}

void loop() {
  float temp = dht.getTemperature();
  float humi = dht.getHumidity();
  Serial.println(temp);

  if (ifttt.triggerEvent(EVENT_NAME_GOOGLESHEET, (String)temp, (String)humi)) {
    Serial.println("Successfully sent to Google sheet");
    delay(2000);
  } else {
    Serial.println("Failed! sent to Google sheet");
  }

  delay(300);
}
