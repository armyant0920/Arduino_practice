int sensor=A0;
  int Read=0;
  int light=0;//
  

void setup() {
  Serial.begin(9600);
   pinMode(3,INPUT);
}

void loop() {
  Read=analogRead(sensor);
  Serial.println(Read);
  light=map(Read,0,1023,0,255);//使用map將數字等比例轉換到0~255

  analogWrite(3,light);//3號接腳收類比訊號
  delay(200);

}
