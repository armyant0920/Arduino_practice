
#include  <Servo.h>//導入伺服馬達需要
Servo servo;
int angle=0;
int light=0;
int sensor=9;
int LED_Pin=3;

//開關
int before=0;
int current=0;



void setup() {
  Serial.begin(9600);

  servo.attach(sensor);//設定9號腳位為伺服馬達的控制腳位,注意,實際偵測改變的仍是A0腳位,9號腳位只是用於輸出訊號給馬達
  
  
}

void loop() {

   
   //當開關狀態為1時,才開啟可變電阻控制伺服馬達
  
      angle=map(analogRead(A0),0,1023,0,180);
      
      servo.write(angle);
      Serial.println(angle);

 
      

    delay(15);

  }
