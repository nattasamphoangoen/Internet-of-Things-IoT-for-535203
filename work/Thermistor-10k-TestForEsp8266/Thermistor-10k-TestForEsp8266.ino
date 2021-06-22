#define RT0 10000  
#define B 3977     
float a = A0;

#define VCC 5  
#define R 10000  

//Variables
float RT, VR, ln, Temp, T0, Read;

void setup() {
  Serial.begin(115200);
  pinMode(A0, INPUT);
  T0 = 25 + 273.15;                
}

void loop() {
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
  delay(1000);

}
