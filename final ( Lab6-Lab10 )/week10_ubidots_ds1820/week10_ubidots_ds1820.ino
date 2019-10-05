#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 4
#include <WiFi.h>
#include <PubSubClient.h>
#define WIFISSID "ssid"
#define PASSWORD "pass"
#define TOKEN "xxxxxxM4sD2FQxy"
#define MQTT_CLIENT_NAME "Username"
#define VARIABLE_LABEL "LabelName"
#define DEVICE_LABEL "DeviceName"
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
char mqttBroker[] = "industrial.api.ubidots.com";
char payload[100];
char topic[150];
char str_tem[6] ;
char str_sensor[10];
WiFiClient ubidots;
PubSubClient client(ubidots);
void setup(void) {
Serial.begin(115200);
WiFi.begin(WIFISSID, PASSWORD);
Serial.println();
Serial.print("Wait for WiFi...");
while (WiFi.status() != WL_CONNECTED) {
Serial.print(".");
delay(500);
}
Serial.println("");
Serial.println("WiFi Connected");
Serial.println("IP address: ");
Serial.println(WiFi.localIP());
client.setServer(mqttBroker, 1883);
// client.setCallback(callback);
Serial.println("ArduinoAll Test Temperature 18B20");
sensors.begin();
}
void reconnect() {
while (!client.connected()) {
Serial.println("Attempting MQTT connection...");
// Attemp to connect
if (client.connect(MQTT_CLIENT_NAME, TOKEN, "")) {
Serial.println("Connected");
} else {
Serial.print("Failed, rc=");
Serial.print(client.state());
Serial.println(" try again in 2 seconds");
delay(2000);
}
}
}
void loop(void) {
sensors.requestTemperatures();
Serial.print(sensors.getTempCByIndex(0));
// str_tem = (char)sensors.getTempCByIndex(0);
Serial.println(" *C");
delay(1000);
if (!client.connected()) {
reconnect();
}
sprintf(topic, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
sprintf(payload, "%s", "");
sprintf(payload, "{\"%s\":", VARIABLE_LABEL);
dtostrf(sensors.getTempCByIndex(0) , 4 , 2, str_tem);
sprintf(payload, "%s {\"value\": %s}}", payload, str_tem);
Serial.println(str_tem);
Serial.println("Publishing data to Ubidots Cloud");
client.publish(topic, payload);
client.loop();
delay(1000);
}
