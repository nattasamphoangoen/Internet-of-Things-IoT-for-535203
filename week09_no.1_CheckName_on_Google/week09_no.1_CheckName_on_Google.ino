#include <IFTTTMaker.h>

#include <WiFi.h>
#include <WiFiClientSecure.h>

char ssid[] = "ssiidToUser";
char password[] = "passTossid";
#define KEY "YourKeyToiFTTT"
#define EVENT_NAME "device_on"

WiFiClientSecure client;
IFTTTMaker ifttt(KEY, client);

void setup() {

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

  if (ifttt.triggerEvent(EVENT_NAME, "NameStudent", "studentCode", WiFi.macAddress().c_str())) {
    Serial.println("Successfully sent");
  } else {
    Serial.println("Failed!");
  }

}

void loop() {
}
