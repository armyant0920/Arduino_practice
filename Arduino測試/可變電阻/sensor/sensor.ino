int sensor=A0;
int Read=0;
int light=0;//
int pwm_pin=5;
int out1=7;
int out2=8;
  

void setup() {
  Serial.begin(9600);
   pinMode(pwm_pin,OUTPUT);
   pinMode(out1,OUTPUT);
   pinMode(out2,OUTPUT);
   digitalWrite(out1, LOW); 
   digitalWrite(out2, LOW);
   
}

void loop() {
  Read=analogRead(sensor);
  Serial.println("read="+String(Read));
  
  light=map(Read,0,1023,0,255);//使用map將數字等比例轉換到0~255
  Serial.println("light="+String(light));
  //Serial.println(light);
  if(light==0){
      digitalWrite(out1,HIGH);
      digitalWrite(out2,LOW);
      Serial.println("forward");
    }
   if(light==255){
      digitalWrite(out1,LOW);
      digitalWrite(out2,HIGH);
      Serial.println("backward");
    } 

  analogWrite(pwm_pin,light);//A0號接腳收類比訊號
  delay(50);

}
