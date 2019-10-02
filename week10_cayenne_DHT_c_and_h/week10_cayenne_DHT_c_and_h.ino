#define CAYENNE_PRINT Serial  
#include <CayenneMQTTWiFi.h>
#include "DHTesp.h"

DHTesp dht;

char ssid[] = "ssis";
char wifiPassword[] = "pass";

char username[] = "xxxxxxx-xxxx-xxxx-xxxxxx";
char password[] = "xxxxxxxxxxxxxxxxxxxxxxxxxx";
char clientID[] = "xxxxxxx-xxxx-xxxx-xxxxxx";

void setup() {
  Serial.begin(9600);
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
  dht.setup(4, DHTesp::DHT22);
}
void loop() {
  Cayenne.loop();
}

CAYENNE_OUT_DEFAULT()
{
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();
  Serial.print(humidity, 1);
  Serial.print("\t\t");
  Serial.print(temperature, 1);
  Serial.println("\t\t");
  Cayenne.virtualWrite(2, String(humidity).c_str());
  Cayenne.virtualWrite(1, String(temperature).c_str());
}
CAYENNE_IN_DEFAULT()
{
  CAYENNE_LOG("Channel %u, value %s", request.channel, getValue.asString());
}
