
#include  <Servo.h>//導入伺服馬達需要
Servo servo;
int angle=0;
int light=0;
int sensor=9;
int LED_Pin=3;

//開關
int before=0;
int current=0;
int buttonState = 0; 
int work=-1;
const int buttonPin = 7;
void setup() {
  Serial.begin(9600);
  pinMode(3,INPUT);
  pinMode(buttonPin,INPUT);//7號腳位接收按鈕變化
 
  servo.attach(sensor);//設定9號腳位為伺服馬達的控制腳位,注意,實際偵測改變的仍是A0腳位,9號腳位只是用於輸出訊號給馬達
  
  
}

void loop() {


  

  current = digitalRead(buttonPin);


    if(current!= buttonState){
      delay(50);
      if(current==HIGH){        
          work*=-1;
          Serial.println("btn down");
          Serial.println("work="+String(work));
     
        }else{
         Serial.println("btn up");   
          }
      
        buttonState=current;
    }
    


   
   //當開關狀態為1時,才開啟可變電阻控制伺服馬達
   if(work==1){
      angle=map(analogRead(A0),0,1023,0,180);
      
      servo.write(angle);
      Serial.println(angle);

    }else{
      
   //當開關狀態為-1時,按鈕隨可變電阻調整亮度
      //使用map將數字等比例轉換到0~255
      light=map(analogRead(A0),0,1023,0,255);//LED部分我們是用3號腳位輸出類比訊號,但值一樣是讀A0腳位的變化
      analogWrite(LED_Pin,light);
      Serial.println("light="+String(light));
      
      
      }
    delay(15);

  }
