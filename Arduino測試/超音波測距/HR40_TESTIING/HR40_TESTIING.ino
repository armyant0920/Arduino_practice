#include <Ultrasonic.h>

Ultrasonic sonic(12,13);
int distance;
int trigPin = 12;                  //Trig Pin
int echoPin = 13;                  //Echo Pin
long duration, cm, inches;
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);        // 定義輸入及輸出 
  pinMode(echoPin, INPUT);
  

}

void loop() {
  // put your main code here, to run repeatedly:

  distance=sonic.read();//

  Serial.println(String(distance)+"CM");
  

  /*
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);     // 給 Trig 高電位，持續 10微秒
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  pinMode(echoPin, INPUT);             // 讀取 echo 的電位
  duration = pulseIn(echoPin, HIGH);   // 收到高電位時的時間
 
  cm = (duration/2) / 29.1;         // 將時間換算成距離 cm 或 inch  
  inches = (duration/2) / 74; 

  Serial.print("Distance : ");  
  Serial.print(inches);
  Serial.print("in,   ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();*/
  

  delay(500);
  

}
