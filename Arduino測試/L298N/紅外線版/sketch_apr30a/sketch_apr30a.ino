#include <IRremote.h>


const int motorIn1 = 5;
const int motorIn2 = 6;
const int motorIn3 = 9;
const int motorIn4 = 10;
const byte IR_RECEIVE_PIN=11;
char cmd;  // 接收序列埠傳來的指令
int nowSpeed = 0;  // 目前轉速級別, 0級停止, 1級100, 2級150, 3級200, 4級255全速
int nowDirection = 0;  // 目前旋轉方向, 0為forward, 1為backward
char* speedMark[] = {"", "+", "++", "+++", "++++"};
int speedPWM[] = {0, 100, 150, 200, 255};
long input;
int now=0;

void setup() {
  Serial.begin(115200);
  pinMode(motorIn1, OUTPUT);
  pinMode(motorIn2, OUTPUT);
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
               nowSpeed = 4;
               nowDirection = 0;
               
              break;
            case 21://下
              nowSpeed = 4;
              nowDirection = 1;
              break;

            case 68://左
              if (nowSpeed>0) nowSpeed--;            
              break;

           case  67://右
              if (nowSpeed<4) nowSpeed++;
              break;

           case  64://MID
             nowSpeed = 0;

           
              break;

           case 66://*
              break;

           case 74://#
            
              break;
            
           default :
              break;     
              
          }  
          
          changeSpeed();
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
void changeSpeed() {
  showData();
  if (nowDirection==0) {
    // forward
    analogWrite(motorIn1, speedPWM[nowSpeed]);
    analogWrite(motorIn2, 0);
     analogWrite(motorIn3, speedPWM[nowSpeed]);
    analogWrite(motorIn4, 0);
  } else {
    // backward
    analogWrite(motorIn1, 0);
    analogWrite(motorIn2, speedPWM[nowSpeed]);
    analogWrite(motorIn3, 0);
    analogWrite(motorIn4, speedPWM[nowSpeed]);
  }
}
