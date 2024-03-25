#include <IRremote.h>


const int motorIn1 = 5;
const int motorIn2 = 6;
const int motorIn3 = 9;
const int motorIn4 = 10;
const byte IR_RECEIVE_PIN=11;
char cmd;  // 接收序列埠傳來的指令
int nowSpeed = 2;  // 目前轉速級別, 0級停止, 1級100, 2級150, 3級200, 4級255全速
int nowDirection = 0;  // 目前旋轉方向, 0為forward, 1為backward
char* speedMark[] = {"", "+", "++", "+++", "++++"};
int speedPWM[] = {0, 100, 150, 200, 255};
long input;
int now=0;

void setup() {
  Serial.begin(115200);
  pinMode(motorIn1, OUTPUT);
  pinMode(motorIn2, OUTPUT);
   pinMode(motorIn3, OUTPUT);
    pinMode(motorIn4, OUTPUT);
  Serial.println(F("Enabling IRin"));
   // irrecv.begin(IR_RECEIVE_PIN,ENABLE_LED_FEEDBACK);
   IrReceiver.begin(IR_RECEIVE_PIN,ENABLE_LED_FEEDBACK);
    //irsend.begin(3,ENABLE_LED_FEEDBACK);
    Serial.print(F("Ready to receive IR signals at pin "));
    Serial.println(IR_RECEIVE_PIN); 
    delay(1000);
}

void loop() {

  if(IrReceiver.decode()){//irrecv
          input=IrReceiver.decodedIRData.command,HEX;         
          IrReceiver.resume();
        if(input!=0 && input !=NULL){
         Serial.println("input="+String(input)+"/"+IrReceiver.decodedIRData.decodedRawData);
          //IrReceiver.printIRResultAsCVariables(&Serial);  // Output address and data as source code variables
           //IrReceiver.compensateAndPrintIRResultAsPronto(&Serial);
           IrReceiver.printIRResultShort(&Serial); // optional use new print version
         now=input;
     
         switch (input){
          
            case 70://上
               
               nowDirection = 0;
               if(nowSpeed==0){
                nowSpeed++;
                }
               
              break;
            case 21://下
              
              nowDirection = 1;
              if(nowSpeed==0){
                nowSpeed++;
                }
              break;

            case 68://左
              nowDirection = 2;  
              if(nowSpeed==0){
                nowSpeed++;
                }      
              break;

           case  67://右
           nowDirection = 3;  
              if(nowSpeed==0){
                nowSpeed++;
                }     
              
              break;

           case  64://MID
             nowSpeed = 0;

           
              break;

           case 66://*
           if (nowSpeed>0) 
              {nowSpeed--;
              }    
              break;

           case 74://#
           if (nowSpeed<4) 
              {nowSpeed++;
              }
            
              break;
            
           default :
              break;     
              
          }  
          
          moving();
      }
  }
}

// 顯示目前轉向與速度
void showData() {
  if (nowSpeed==0) {
    Serial.println("Stop");
  } else {
    Serial.print(nowDirection==0 ? "Forward ":"Backward ");
    Serial.println(speedMark[nowSpeed]);
  }  
}

// 加減速
void moving() {
  showData();

  switch(nowDirection){
    
    case 0://forward
    analogWrite(motorIn1, speedPWM[nowSpeed]);
    analogWrite(motorIn2, LOW);
    analogWrite(motorIn4, speedPWM[nowSpeed]);
    analogWrite(motorIn3, LOW); 
    break;
    
    case 1://back
    analogWrite(motorIn1, LOW);
    analogWrite(motorIn2, speedPWM[nowSpeed]);
    analogWrite(motorIn4, LOW);
    analogWrite(motorIn3, speedPWM[nowSpeed]);   
    break;
    
    case 2://left
    analogWrite(motorIn1, LOW);
    analogWrite(motorIn2, LOW);
    analogWrite(motorIn4, speedPWM[nowSpeed]);
    analogWrite(motorIn3, LOW);  
    break;
    
    case 3://right
    analogWrite(motorIn1, speedPWM[nowSpeed]);   
    analogWrite(motorIn2, LOW);
    analogWrite(motorIn4, LOW);
    analogWrite(motorIn3, LOW);   
    break;
    
    
    
    }

}
