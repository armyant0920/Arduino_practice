#include <LiquidCrystal_PCF8574.h>
LiquidCrystal_PCF8574 lcd(0x27);  // 設定i2c位址，一般情況就是0x27和0x3F兩種
const int maxLen=16;
const String Moisture="Moisture:";

int num;
void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  pinMode(A0,INPUT);
  
  lcd.begin(16,2);
  lcd.setBacklight(1);
    lcd.clear();
      lcd.setCursor(0, 0);  //設定游標位置 (字,行)
      lcd.print(Moisture);
     lcd.setCursor(0, 1);
    lcd.print("*~ system ready.");
  
     lcd.print(Moisture);
      Serial.print("wait..");
     delay(2000);
     Serial.print("begin");
     
  

}

void loop() {
  // put your main code here, to run repeatedly:
  num=analogRead(A0);
  lcd.clear();
   lcd.setCursor(0, 0);  //設定游標位置 (字,行)
      lcd.print(Moisture);
         lcd.setCursor(0, 1);
         //由於查不到個準則,只好約略將直接置於水中的讀數做參考,
         //其實檢測時,插入土中的深度影響也很大
         //我在完全浸入水中靜置數分鐘後,讀數從1XX會慢慢上升到31X
         //因此蓋抓100%為300
         lcd.print(String(num)+","+String(map(num,300,1023,100,0))+"%");
      
  Serial.println("num="+String(num));
  delay(1000);
  
}
