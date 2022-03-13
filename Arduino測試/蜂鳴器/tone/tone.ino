#include "pitches.h"
int melody[]={NOTE_C4,NOTE_G4,NOTE_A3,NOTE_G3,NOTE_B3,NOTE_C4};
int song[]={NOTE_G4,NOTE_E4,NOTE_E4,NOTE_F4,NOTE_D4,NOTE_D4,NOTE_C4,NOTE_D4};
int buttonPin=12;
int noteDur[]={4,8,8,4,4,4,4,4};
int noteDur2[]={2,4,4,2,4,4,2,2};

void setup() {

  pinMode(buttonPin,INPUT);
  Serial.begin(9600);
  pinMode(7, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int state=digitalRead(buttonPin);
 

  if(state==1){
      Serial.println(state);
      digitalWrite(7, HIGH); 
      for(int now=0;now<8;now++){
          int dur = 1000/noteDur2[now];
          tone(8,song[now],dur);//8號腳位
          int pause=dur*1.30;
          delay(pause);

          noTone(8);//8號腳位
        
        }
         digitalWrite(7, LOW); 
    
    }

  

}
