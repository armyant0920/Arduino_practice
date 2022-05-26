int sensor=A0;
int Read=0;
int light=0;//
int pwm_pin=5;
  

void setup() {
  Serial.begin(9600);
   pinMode(pwm_pin,OUTPUT);
}

void loop() {
  Read=analogRead(sensor);
  
  light=map(Read,0,1023,0,255);//使用map將數字等比例轉換到0~255
  Serial.println("pwm="+String(light));

  analogWrite(pwm_pin,light);//3號接腳收類比訊號
  delay(10);

}
