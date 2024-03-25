
#include <Servo.h>//伺服馬達程式庫
#include <string.h>


#define SERVO_PIN 8//伺服馬達控制訊號接腳

int state=0;
bool lockSwitch=false;//伺服馬達狀態
Servo servo;



void turn(int input){

  state=input%5;
  servo.write(state*45);
  
  

  /*switch(input){
    
    case 1:
    servo.write(0);
    state=1;
    

      break;
    case 2:
    servo.write(45);
    state=2;
      break;
    case 3:
    servo.write(90);
    state=3;
      break;    
      case 4:
    servo.write(90);
    state=3;
      break;  
      case 3:
    servo.write(90);
    state=3;
      break;  
      case 3:
    servo.write(90);
    state=3;
      break;  
      
    
    
    }*/
    Serial.println("state="+String(state));
    

  

     delay(1000);   //等馬達轉到定位                
  }
  

void setup() {
  Serial.begin(9600);
  servo.attach(SERVO_PIN);
  Serial.println("start");
                                                                                              

}


void loop() {

      
              if(Serial.available()){
                int input = Serial.readString().toInt();

                  Serial.println("input="+String(input));
                  
                  turn(input);
                  
                  
                  
                
                }
      
           }
        
        
     
