/*
本程式為LCD 1602的範例

首先要安裝LiquidCrystal_PCF8574的函式庫
接線請參考附圖

LCD 16x2 賣場：
https://www.jmaker.com.tw/products/lcd1602

LCD支架賣場：
https://www.jmaker.com.tw/products/product170

LCD 20x4 賣場：
https://www.jmaker.com.tw/products/lcd20x4



傑森創工賣場：https://www.jmaker.com.tw

傑森創工粉絲團：https://www.facebook.com/jasonshow

 */

#include <LiquidCrystal_PCF8574.h>

LiquidCrystal_PCF8574 lcd(0x27);  // 設定i2c位址，一般情況就是0x27和0x3F兩種

const String text="this is a very very long and boreing string that can not fully shown on LCD";
const int maxLen=16;
int line2_index;

void setup()
{
  lcd.begin(16, 2); // 初始化LCD
  //lcd.begin(20, 4); // 如果是20x4的LCD就是用這行
  
  lcd.setBacklight(255);
  lcd.clear();
  lcd.setCursor(0, 0);  //設定游標位置 (字,行)
  lcd.print("*~ first line.");
  lcd.setCursor(0, 1);
  lcd.print("~* second line.");
  delay(5000);//先停止5秒
} 

void loop()
{
 line2_index=0;
 while(line2_index<text.length()){

    if(line2_index+maxLen>text.length()){
      //如果剩下的文字不足螢幕長度了,固定先把第二行蓋成空白
      for(int i=0;i<maxLen;i++){
        lcd.setCursor(i,1);
        lcd.print(" ");
      }
        //判斷從index開始到哪個位置後沒有文字
        /*int pos=(line2_index+maxLen)-text.length();
        for (int i=pos;i<maxLen;i++){
            lcd.setCursor(maxLen-i,1);
            lcd.print(" "); */        
          }
    lcd.setCursor(0,1);//移動到第二行開頭
    lcd.print(text.substring(line2_index,min(line2_index+maxLen,text.length())));
      
    line2_index++;
    delay(200);
  }
  lcd.setCursor(0, 1);
  lcd.print("~* second line.");
  delay(5000);
  
} 
