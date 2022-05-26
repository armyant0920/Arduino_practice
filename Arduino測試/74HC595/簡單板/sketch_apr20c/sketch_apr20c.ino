byte latchPin = 4;  // Latch pin (STCP腳位)
byte clockPin = 5; // Clock pin (SHCP腳位)
byte dataPin = 2;  // Data pin (DS腳位)

void setup() 
{
  // Set all the pins of 74HC595 as OUTPUT
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  digitalWrite(latchPin, LOW);  // 送資料前要先把 latchPin 設成低電位
  shiftOut(dataPin, clockPin, LSBFIRST,convertToByte("10101010"));
  //shiftOut(dataPin, clockPin, LSBFIRST, 170);  //送出資料，170就是2進位的10101010
  digitalWrite(latchPin, HIGH); // 送完資料後要把 latchPin 設成高電位
  delay(3000);
  digitalWrite(latchPin, LOW);
  //shiftOut(dataPin, clockPin, LSBFIRST, 85);  //85就是2進位的01010101
  shiftOut(dataPin, clockPin, LSBFIRST,convertToByte("11111000"));
  digitalWrite(latchPin, HIGH);
 
 
  delay(3000);


  
}

int convertToByte(String input){
    int factor=2;
    int result=0;
    int cur=0;
    

    for(int i=0;i<input.length();i++){
        String now=String(input.charAt(i));
        Serial.println("now="+now);
        cur=now.toInt();
        Serial.println("cur="+String(cur));
        Serial.println("count="+String(pow(factor,7-i)*cur));
        result+=pow(factor,7-i)*cur;
        Serial.println("result now="+String(result));
        
      
      }
      
      return result;
  
  
  }
