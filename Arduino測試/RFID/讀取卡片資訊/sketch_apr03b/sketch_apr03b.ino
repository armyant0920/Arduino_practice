#include <SPI.h>
#include <MFRC522.h>//
#include <Servo.h>//伺服馬達程式庫

#define RST_PIN A0 //讀卡機重置腳位
#define SS_PIN 10  //晶片選擇腳位
#define SERVO_PIN 2//伺服馬達控制訊號接腳

MFRC522 mfrc(SS_PIN,RST_PIN);//建立MFRC522物件
bool lockSwitch=false;//伺服馬達狀態
Servo servo;

typedef struct data{
    byte uid[4];
    char *name;
  } RFIDTag;

RFIDTag tags[]={
    //白卡
    {{131,219,255,20},"白卡"},
    
    //磁扣
    {{234,195,59,89},"磁扣"}
  
  };

byte totalTags=sizeof(tags)/sizeof(RFIDTag);//取目前存的tags數  

void locker(bool toggle){
  
    if(toggle){
        servo.write(90);
        
      }else{
          servo.write(0);
        
        }
     delay(15);   //等馬達轉到定位                
  }
  

void setup() {
  Serial.begin(9600);
  Serial.print("size of RFIDTag:");
  Serial.println(sizeof(RFIDTag));
  Serial.print("size of tag:");
  Serial.println(sizeof(tags));
  

  
  Serial.println("RFID reader is ready");
  SPI.begin();
  servo.attach(SERVO_PIN);
  mfrc.PCD_Init();//初始化MFRC522 讀卡機模組

}


void loop() {
  if(mfrc.PICC_IsNewCardPresent() && mfrc.PICC_ReadCardSerial())
     {
      byte *id   =mfrc.uid.uidByte;
      byte idSize=mfrc.uid.size;
      bool found=false;//是否找到符合的卡,預設false

      Serial.print("PICC type:");
      //根據卡片的SAK值(mfrc522.uid.sak)判斷卡片類型
      
      MFRC522::PICC_Type piccType=mfrc.PICC_GetType(mfrc.uid.sak);
      Serial.println(mfrc.PICC_GetTypeName(piccType));

      Serial.println("UID Size"+idSize);
      for(byte i=0;i<idSize;i++){//逐一顯示uid碼
        Serial.print("id[");
        Serial.print(i);
        Serial.print("]=");
        Serial.println(id[i]);
          //Serial.println("id["+(char)i+"]="+(char)_id[i]);
               
        }
      for (byte i=0;i<totalTags;i++){
          if(memcmp(tags[i].uid,id,idSize)==0){//比對陣列資料值
              Serial.println(tags[i].name);
              found=true;
              lockSwitch=!lockSwitch;
              locker(lockSwitch);
              break;
            
            }
        
        
        }
        if(!found){
            Serial.println("wrong card");

            if(lockSwitch){
                lockSwitch=false;
                locker(lockSwitch);
              
              }
          
          }
        
             
        mfrc.PICC_HaltA();//卡片進入停止模式
      
    
    }

}
