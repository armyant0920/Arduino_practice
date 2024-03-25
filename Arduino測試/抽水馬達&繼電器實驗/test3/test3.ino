#include <Wire.h>
#include <ThreeWire.h>
#include <RtcDS1302.h>
#include <Servo.h>//伺服馬達程式庫
#include <string.h>
#include <Timer.h>

#define SERVO_PIN 8//伺服馬達控制訊號接腳
#define POWER_PIN 11//沉水馬達控制訊號接腳

ThreeWire myWire(2, 3, 4); // IO(DATA), SCLK(CLK), CE(RST)
RtcDS1302<ThreeWire> Rtc(myWire);
int state=0;
int current=0;
bool lockSwitch=false;//伺服馬達狀態
bool watering=false;
Servo servo;
int now=0;
int input;


Timer secondWatch;
Timer servoTimer;
Timer waterTimer;


void turn(int input){
    state=input%5;
    servo.write(state*45); 
    Serial.println("state="+String(state));
    //delay(15);   //等馬達轉到定位                
  }
  
void goback(){
    servo.write(0); 
    Serial.println("Servo reset");
  }

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(POWER_PIN, OUTPUT);
  digitalWrite(POWER_PIN,LOW);
  servo.attach(SERVO_PIN);
  goback();
  
  secondWatch.every(1000,showTime);
  waterTimer.every(60000,setCurrentCount);
  setCurrentCount();
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
  //Rtc.SetDateTime(compiled);//不知為何RTC時間跑到未來時空的話,把他強制設成一樣
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
  


}

void loop() {
  secondWatch.update();
  servoTimer.update();
  waterTimer.update();
  if(Serial.available()){
     input = Serial.readString().toInt();

     Serial.println("input="+String(input));
     feed(input);
     
    
    
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

  //判斷DS1302是否正常，如果不正常，一般是線沒接好，或是電池沒電了
  if (!now.IsValid())
  {
    Serial.println("RTC lost confidence in the DateTime!");
  }

 }





void setCurrentCount(){
   Serial.println("執行setCurrent");
  if(current==30){
    current=0;
    } 
  
  Serial.println("current="+String(current));
  if(current==0){

     digitalWrite(POWER_PIN, HIGH); 
    }else{
      digitalWrite(POWER_PIN, LOW); 
      }

   current++;
  
  }

  #define countof(a) (sizeof(a) / sizeof(a[0]))

void waterTEST(){
  

  Serial.println("執行waterTEST");
   digitalWrite(POWER_PIN, LOW);
  watering=false;
  }

void feed(int i){
     turn(i);
     int afterEvent=servoTimer.after(1000*3,goback);
    
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

      if( dt.Minute()%2==0 and dt.Second()==0 ){//dt.Hour()==16 &&
         Serial.println("執行feed");
        feed(4);
        
         
        
        }

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
  Serial.println(minsec_string);
  Serial.println(dt.Minute());
  Serial.println(dt.Hour());

  
   
}
