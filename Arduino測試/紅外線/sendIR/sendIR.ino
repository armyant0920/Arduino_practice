
#include <IRremote.h>

IRsend irsend;




void setup() {
    Serial.begin(115200);
    irsend.begin(true);
}
void loop() {
          //irsend.sendNEC(0xA8, 0x19, 10);
          irsend.sendNEC(0xFB0C, 0x18, 100);
           //Address=0xFB0C Command=0x18 Raw-Data=0xE718FB0C 32 bits LSB first

          
            
          delay(500);
          //irsend.sendSony(0xFF38C7, 16); 

        }             
      
       
 
