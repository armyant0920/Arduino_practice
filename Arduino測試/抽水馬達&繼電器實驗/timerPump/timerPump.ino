#include <Wire.h>
#include <ThreeWire.h>
#include <RtcDS1302.h>

#include <string.h>
#include <Timer.h>

#define POWER_PIN 11//沉水馬達控制訊號接腳

#define Grove_Water_Sensor A0 // 

ThreeWire myWire(2, 3, 4); // IO(DATA), SCLK(CLK), CE(RST)
RtcDS1302<ThreeWire> Rtc(myWire);
int state=0;
int current=0;

bool watering=false;

int now=0;
int input;


Timer secondWatch;
Timer waterTimer;


void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(POWER_PIN, OUTPUT);
  pinMode(Grove_Water_Sensor, INPUT); 
  digitalWrite(POWER_PIN,LOW);
  
  
  
  //int waterEvent=waterTimer.oscillate(POWER_PIN,500,HIGH);
  
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
  Rtc.SetDateTime(compiled);//不知為何RTC時間跑到未來時空的話,把他強制設成一樣
  if (now < compiled)
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
  }

  secondWatch.every(1000,showTime);
  waterTimer.every(60000,setCurrentCount);
  setCurrentCount();


}

void loop() {
  
  
  

  
  secondWatch.update();
  waterTimer.update();
  if(Serial.available()){
     input = Serial.readString().toInt();

     Serial.println("input="+String(input));

    
    }
  
  // put your main code here, to run repeatedly:
  //setCurrent();
  //showTime();


  //delay(6000*10);//每分鐘檢查一次
  


}
void showTime(){

   RtcDateTime now = Rtc.GetDateTime();

  printDateTime(now);
  Serial.println();


  /*int value = analogRead(Grove_Water_Sensor);
  Serial.println("value="+String(value));
  if(value>500){
      digitalWrite(POWER_PIN, HIGH);
    
    }else{
       digitalWrite(POWER_PIN, LOW);
      }*/

  //判斷DS1302是否正常，如果不正常，一般是線沒接好，或是電池沒電了
  if (!now.IsValid())
  {
    Serial.println("RTC lost confidence in the DateTime!");
  }

 }





void setCurrentCount(){

   

   Serial.println("執行setCurrent");

    RtcDateTime now = Rtc.GetDateTime();
    Serial.println("now hour="+String(now.Hour()));
     if( now.Hour()<6 ){//dt.Hour()==16 &&
         Serial.println("半夜不執行");
         current=0;
        }else{

            
            
          
           if(current==30){current=0; }
             Serial.println("current="+String(current));
              if(current==0){
                Serial.println("打水~");
                 digitalWrite(POWER_PIN, HIGH); }
                 else{digitalWrite(POWER_PIN, LOW); }
                 current++;

             int value = analogRead(Grove_Water_Sensor);
            Serial.println("value="+String(value));
            if(value>500){
            digitalWrite(POWER_PIN, HIGH);
    
            }      
            
          
          
          }


        
            
 
  

 
  
  }

  #define countof(a) (sizeof(a) / sizeof(a[0]))

void waterTEST(){
  

  Serial.println("執行waterTEST");
   digitalWrite(POWER_PIN, LOW);
  watering=false;
  }




//顯示完整年月日時間的副程式  
void printDateTime(const RtcDateTime& dt)
{
      
      /*if(dt.Minute()%5==0){//每5分鐘
      turn(4);
      
    }*/
    /*if(dt.Second()%10==0 && watering==false){
        watering=true;
        //digitalWrite(POWER_PIN, HIGH); 
        //int waterEvent=waterTimer.pulse(POWER_PIN,1000*9,HIGH);
        //int waterEvent=waterTimer.oscillate(POWER_PIN,500,LOW,4);
        digitalWrite(POWER_PIN, HIGH);
        Serial.println("執行water");
        waterTimer.after(1000*30,waterTEST);
      }*/

    

    /*if(dt.Second()%10==0){
      
      
      
      }*/
  
  
  char datestring[20];

  char minsec_string[5];


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
             dt.Minute(),
             dt.Second() );

  Serial.println(datestring);
    Serial.print(dt.Hour());
      Serial.print(dt.Minute());
  Serial.print(dt.Second());


  Serial.println();

  
   
}
