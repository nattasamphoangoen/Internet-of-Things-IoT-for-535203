int i,j;
void setup() {
  Serial.begin(115200);
}

void loop() {
   while(Serial.available()>0){
    int num = Serial.parseInt();
   
      for(i=0;i<num;i++){
        Serial.println();
        for(j=0;j<num;j++){
          if(i==0||i==num-1||j==0||j==num-1||j==i||j==num-1-i){
            Serial.print("X ");
          }
          else{
            Serial.print("  ");
          }
        }
      }
     
   }
}
