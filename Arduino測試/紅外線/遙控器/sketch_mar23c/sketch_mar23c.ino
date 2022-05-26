/*#include <IRremote.h>
int RECV_PIN = 11; //define input pin on Arduino
IRrecv irrecv(RECV_PIN);
decode_results results;

  void setup()
  {
  Serial.begin(9600);
  Serial.println("start");
  irrecv.enableIRIn(); // Start the receiver
  }
  void loop() {
    
  if (irrecv.decode(&results)) {

   Serial.println(results.value, HEX);
   irrecv.resume(); // Receive the next value
    }
  }*/




  //*******************************************************************************
//
//    本程式僅供學習使用，未經作者允許，不得用於其他用途。 版權所有，仿冒必究！
//    1.開發環境：Arduino IDE
//    2.測試使用開發板型號：Arduino UNO R3
//    3.網址：http://store.ruten.com.tw/yuhhann_online
//    4.e-mail：yuhhann.studio@gmail.com、yuhhann.studio@yahoo.com
//    5.FB 粉絲專頁：https://www.facebook.com/yuhhann.studio
//    6.LINE ID：yuhhann.studio
//    7.作者：鈺瀚工作室
//
//    《KEYES》KY-022 紅外線接收模組
//
//*******************************************************************************
/*
#include <IRremote.h>                   // 引用 IRremote 函式庫

const int irReceiverPin = 11;           // 設定紅外線接收器輸出訊號接在 pin11

IRrecv irrecv(irReceiverPin);           // 定義 IRrecv 物件來接收紅外線訊號
decode_results results;                  // 解碼結果將放在 decode_results 結構的 result 變數裏

void setup()
{
  Serial.begin(9600);                     // 開啟 Serial port, 通訊速率為 9600 bps
  irrecv.enableIRIn();                   // 啟動紅外線解碼程序
}

// 顯示紅外線協定種類
void showIRProtocol(decode_results *results) 
{
  Serial.print("Protocol: ");
  
  // 判斷紅外線協定種類
  switch(results->decode_type) {
   case NEC:
     Serial.print("NEC");
     break;
   case SONY:
     Serial.print("SONY");
     break;
   case RC5:
     Serial.print("RC5");
     break;
   case RC6:
     Serial.print("RC6");
     break;
   default:
     Serial.print("Unknown encoding");  
  }  

  // 把紅外線編碼印到 Serial port
  Serial.print(", irCode: ");            
  Serial.print(results->value, HEX);    // 紅外線編碼
  Serial.print(",  bits: ");           
  Serial.println(results->bits);        // 紅外線編碼位元數    
}

void loop() 
{
  if (irrecv.decode(&results)) {         // 解碼成功，收到一組紅外線訊號
    Serial.println(results.value,HEX);
    //showIRProtocol(&results);            // 顯示紅外線協定種類
    irrecv.resume();                     // 繼續收下一組紅外線訊號        
  }
  delay(100);
}*/

/*

#include <IRremote.hpp>


int IR_RECEIVE_PIN = 11; //define input pin on Arduino
void setup()
{
  Serial.begin(115200);
    Serial.println("setup");
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Start the receiver
}

void loop() {
  if (IrReceiver.decode()) {
      Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
      IrReceiver.printIRResultShort(&Serial); // optional use new print version

      IrReceiver.resume(); // Enable receiving of the next value
  }

}
*/



#include <Arduino.h>


#include "pitches.h"
                       
const byte IR_RECEIVE_PIN=11;
//IRrecv irrecv(IR_RECEIVE_PIN); 


long input;
int now=0;
int dur=1000;
      
const int tonePin=8;
           
//IRsend irsend;
//decode_results results;   



int song[]={NOTE_C4,NOTE_D4,NOTE_E4,NOTE_F4,NOTE_G4,NOTE_A4,NOTE_B4,NOTE_C5};
void setup() {
  
                                                                                
  
    Serial.begin(115200);
    Serial.println(F("Enabling IRin"));
   // irrecv.begin(IR_RECEIVE_PIN,ENABLE_LED_FEEDBACK);
   
    IrReceiver.begin(IR_RECEIVE_PIN,ENABLE_LED_FEEDBACK);
    //irsend.begin(3,ENABLE_LED_FEEDBACK);
    Serial.print(F("Ready to receive IR signals at pin "));
    Serial.println(IR_RECEIVE_PIN); 
    delay(1000);
}
void loop() {

         // irsend.sendSony(0xFF38C7, 16); 
         // delay(500);
        //irsend.sendNEC(8,16);
         

        
         
         
        if(IrReceiver.decode()){//irrecv
          input=IrReceiver.decodedIRData.command,HEX;         
          IrReceiver.resume();
        if(input!=0 && input !=NULL && now!=input){
         Serial.println("input="+String(input)+"/"+IrReceiver.decodedIRData.decodedRawData);
          //IrReceiver.printIRResultAsCVariables(&Serial);  // Output address and data as source code variables
           //IrReceiver.compensateAndPrintIRResultAsPronto(&Serial);
           IrReceiver.printIRResultShort(&Serial); // optional use new print version
         now=input;
         noTone(tonePin);//8號腳位  
         switch (input){
          
            case 22:
              tone(tonePin,song[0]);//8號腳位
              break;
            case 25:
              tone(tonePin,song[1]);//8號腳位
              break;
            case 13:
              tone(tonePin,song[2]);//8號腳位
              break;
            case 12:
              tone(tonePin,song[3]);//8號腳位
              break;  
            case 24:
              tone(tonePin,song[4]);//8號腳位
              break;   
            case 94:
              tone(tonePin,song[5]);//8號腳位
              break; 
            case 8:
              tone(tonePin,song[6]);//8號腳位
              break;   
           case 28:
              tone(tonePin,song[7]);//8號腳位
              break;   
           
            
    
                 

      
       
          
             
             
    
                 
             
           default:
              break;     
              

          }    
          delay(500);
             
         // now=(now+1)%7;
         
        // delay(130);

        }             
      }
       
 
}
