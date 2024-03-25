
#include <Wire.h>
#include <ThreeWire.h>
#include <RtcDS1302.h>

#include <Servo.h>//伺服馬達程式庫
#include <string.h>



#define SERVO_PIN 8//伺服馬達控制訊號接腳
#define POWER_PIN 9//伺服馬達控制訊號接腳

ThreeWire myWire(2, 3, 4); // IO, SCLK, CE
int current=0;
RtcDS1302<ThreeWire> Rtc(myWire);

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
  pinMode(POWER_PIN,OUTPUT);
  Serial.println("start");
  Serial.print("compiled: ");
  Serial.print(__DATE__);
  Serial.println(__TIME__);
  Rtc.Begin();

  //__DATE__，__TIME__，是程式碼編譯時的日期和時間
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  printDateTime(compiled);
  Serial.println();

  //判斷DS1302是否接好
  if (!Rtc.IsDateTimeValid())
  {
    // Common Causes:
    //    1) first time you ran and the device wasn't running yet
    //    2) the battery on the device is low or even missing

    Serial.println("RTC lost confidence in the DateTime!");
    Rtc.SetDateTime(compiled);
  }

  if (Rtc.GetIsWriteProtected())
  {
    Serial.println("RTC was write protected, enabling writing now");
    Rtc.SetIsWriteProtected(false);
  }

  if (!Rtc.GetIsRunning())
  {
    Serial.println("RTC was not actively running, starting now");
    Rtc.SetIsRunning(true);
  }

  //判斷DS1302上紀綠的時間和編譯時的時間，哪個比較新
  //如果編譯時間比較新，就進行設定，把DS1302上的時間改成新的時間
  //now：DS1302上紀綠的時間，compiled：編譯時的時間
  RtcDateTime now = Rtc.GetDateTime();
  Rtc.SetDateTime(compiled);//不知為何RTC時間跑到未來時空了
  /*if (now < compiled)
  {
    Serial.println("RTC is older than compile time!  (Updating DateTime)");
    //編譯時間比較新，把DS1302上的時間改成編譯的時間
    Rtc.SetDateTime(compiled);
  }
  else if (now > compiled)
  {
    Serial.println("RTC is newer than compile time. (this is expected)");
  }
  else if (now == compiled)
  {
    Serial.println("RTC is the same as compile time! (not expected but all is fine)");
  }*/
                                                                                              
}


void loop() {

  if(Serial.available()){

    
                  input = Serial.readString().toInt();

                  Serial.println("input="+String(input));
                 
                  turn(input);
                   showTime();
                  //digitalWrite(POWER_PIN,HIGH);
                  delay(3000);
                   Serial.println("歸位");
                  //digitalWrite(POWER_PIN,LOW);
                  turn(0);
                  showTime();
                  

              }
  /*else{

     
    
    
    }
  RtcDateTime now = Rtc.GetDateTime();*/

      
              
              

             
   
      
}

void showTime(){

   RtcDateTime now = Rtc.GetDateTime();

  printDateTime(now);
  Serial.println();

  //判斷DS1302是否正常，如果不正常，一般是線沒接好，或是電池沒電了
  if (!now.IsValid())
  {
    Serial.println("RTC lost confidence in the DateTime!");
  }

  }

#define countof(a) (sizeof(a) / sizeof(a[0]))

//顯示完整年月日時間的副程式  
void printDateTime(const RtcDateTime& dt)
{

  
  
  
  char datestring[20];

  char minsec_string[5];

  char sec_string[2];

  snprintf_P(datestring,
             countof(datestring),
             PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
             dt.Month(),
             dt.Day(),
             dt.Year(),
             dt.Hour(),
             dt.Minute(),
             dt.Second() );
             
 snprintf_P(minsec_string,
             countof(minsec_string),
             PSTR("%02u%02u"),
             /*dt.Month(),
             dt.Day(),
             dt.Year(),
             dt.Hour(),*/
             dt.Minute(),
             dt.Second() );

   snprintf_P(sec_string,
             countof(sec_string),
             PSTR("02u"),
            
             dt.Second() );           

  Serial.println(datestring);
  Serial.println(minsec_string);

   Serial.println(sec_string);
   Serial.println(dt.Minute());
    if(dt.Second()>30){
       Serial.println("!!!");
      
      }else{
        Serial.println("DDD!");
        }
   /*char subtext[2];

   strncpy(subtext,&datestring[20],8);
   subtext[2]='\0';
   //memcpy(subtext,datestring[0],20);
   
   
   Serial.println(printf("subtext:%s",subtext));*/
  
   
}
        
        
     
