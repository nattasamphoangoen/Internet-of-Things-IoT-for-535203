#define CAYENNE_PRINT Serial 
#include <CayenneMQTTWiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
float Celcius = 0;
float Fahrenheit = 0;
char ssid[] = "ssid";
char wifiPassword[] = "pass";
char username[] = "xxxxxxxxxxxxxxxxxx";
char password[] = "xxxxxxxxxxxxxxxxxx";
char clientID[] = "xxxxxxxxxxxxxxxxxxx";
void setup() {
  Serial.begin(9600);
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
}
void loop() {
  Cayenne.loop();
  sensors.requestTemperatures();
  Celcius = sensors.getTempCByIndex(0);
  Fahrenheit = sensors.toFahrenheit(Celcius);
  Serial.print(" C ");
  Serial.print(Celcius);
  Serial.print(" F ");
  Serial.println(Fahrenheit);
}
CAYENNE_OUT_DEFAULT()
{
  Serial.print("Temperature: ");
  Serial.println(String(Celcius).c_str());
  Cayenne.virtualWrite(0, String(Celcius).c_str());
  Serial.print("Humidity: ");
  Serial.println(String(Fahrenheit).c_str());
  Cayenne.virtualWrite(1, String(Fahrenheit).c_str());
}
CAYENNE_IN_DEFAULT()
{
  CAYENNE_LOG("Channel %u, value %s", request.channel, getValue.asString());
}
