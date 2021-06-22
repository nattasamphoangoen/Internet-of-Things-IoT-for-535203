#include <CayenneMQTTESP8266.h>
#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include "DHTesp.h"
DHTesp dht;

char ssid[] = "Growde179_2.4G";
char password[] = "26049979";
char username[] = "c753c300-ea41-11e9-a38a-d57172a4b4d4";
char mqtt_password[] = "2acffd0bf32ae3ce0340aa228216051a8ff522f3";
char cliend_id[] = "255c2410-d2f8-11eb-b767-3f1a8f1211ba";
#define RT0 10000  
#define B 3977     
float a = A0;
#define VCC 5
#define R 10000

//Variables
float RT, VR, ln, Temp, T0, Read;

void setup() {
  Serial.begin(115200);
  Cayenne.begin(username, mqtt_password, cliend_id, ssid, password);

  pinMode(A0, INPUT);
  T0 = 25 + 273.15;

  pinMode(12, OUTPUT);
  dht.setup(14, DHTesp::DHT11);
  digitalWrite(12, LOW);

}


void loop() {
  
  Cayenne.loop();
  
}

CAYENNE_OUT_DEFAULT()
{
  //thermistor 10k
  Read = analogRead(A0);             
  Read = (5.00 / 1023.00) * Read;     
  VR = VCC - Read;
  RT = Read / (VR / R);              
  ln = log(RT / RT0);
  Temp = (1 / ((ln / B) + (1 / T0))); 
  Temp = Temp - 273.15;                

  Serial.print("Temperature:");
  Serial.print("\t");
  Serial.print(Temp);       
  Serial.print("C\t\t");
  Serial.print(Temp + 273.15);        
  Serial.print("K\t\t");
  Serial.print((Temp * 1.8) + 32);    
  Serial.println("F");
  Cayenne.virtualWrite(3, String(Temp).c_str());

  //DHT11
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();
  Serial.print(humidity, 1);
  Serial.print("\t\t");
  Serial.print(temperature, 1);
  Serial.println("\t\t");
  Cayenne.virtualWrite(2, String(humidity).c_str());
  Cayenne.virtualWrite(1, String(temperature).c_str());
  
  delay(1000);
}

CAYENNE_IN_DEFAULT()
{
  CAYENNE_LOG("Channel %u, value %s", request.channel, getValue.asString());
}

CAYENNE_IN(0)
{
  digitalWrite(12, getValue.asInt());
}
