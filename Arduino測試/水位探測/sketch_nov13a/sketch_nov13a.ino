#define Grove_Water_Sensor A0 // 


void setup() {
   
   pinMode(Grove_Water_Sensor, INPUT); // The Water Sensor is an Input
   Serial.begin(9600);
   Serial.print("start");
   
}

void loop() {
   //從A0讀取輸入
  int value = analogRead(Grove_Water_Sensor);
  Serial.print(value);    
  Serial.print("   ");      
  if (value > 480) {
    Serial.println("High Level");
  
  }          
  else if ((value > 340) && (value <= 480)) {
    Serial.println("Middle Level");
    
  }
  else if ((value > 100) && (value <=340)){
    Serial.println("Low Level");
   ;
  }     
  else if (value <=100){
    Serial.println("NO Water");
       
  }
  delay(500);
}
