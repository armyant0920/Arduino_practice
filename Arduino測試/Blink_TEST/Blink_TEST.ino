/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/
int val_comm;
char comm;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  //Serial.setTimeout(100);
  Serial.println("啟動");
  
  
}

// the loop function runs over and over again forever
void loop() {
  
  /*if(Serial.available()>0){//用大於0?
      comm=Serial.read();
      if(comm=="R"){

            digitalWrite(12, HIGH); 
            digitalWrite(13, LOW);
        
        }else if(comm="G"){
            digitalWrite(13, HIGH); 
            digitalWrite(12, LOW);
          }
      Serial.println(comm);
    }*/
    
    digitalWrite(13, HIGH); 
    digitalWrite(12, LOW);
    delay(5000);
    digitalWrite(12, HIGH); 
    digitalWrite(13, LOW);
    delay(5000);
   /*val_comm=Serial.read();
  if(val_comm==1){
    //digitalWrite(11, LOW); 
    digitalWrite(12, LOW); 
    digitalWrite(13, HIGH); 
    
    
    }else if(val_comm==2){
      digitalWrite(12, HIGH); 
      digitalWrite(13, LOW);
      }
   if(val_comm!=""){
      Serial.println("input="+val_comm); 
    }   */
   
  /*digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second*/
}
