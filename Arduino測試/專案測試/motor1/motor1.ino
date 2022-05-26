


#include <Servo.h>//伺服馬達程式庫
#include <string.h>



#define SERVO_PIN 9//伺服馬達控制訊號接腳
const byte IR_RECEIVE_PIN=11;

int state=0;
bool lockSwitch=false;//伺服馬達狀態
Servo servo;
int now=0;
int input;




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

      
    
    
    }*/
    Serial.println("state="+String(state));
    delay(15);   //等馬達轉到定位                
  }
  

void setup() {
  Serial.begin(9600);
  servo.attach(SERVO_PIN);
  Serial.println("start");
                                                                                              
}


void loop() {

      
              if(Serial.available()){
                  input = Serial.readString().toInt();

                  Serial.println("input="+String(input));
                  
                  turn(input);
                  

              }

             
   
      
}
        
        
     
