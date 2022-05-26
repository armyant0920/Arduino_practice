const int motorIn1 = 5;
const int motorIn2 = 6;
char cmd;  // 接收序列埠傳來的指令
int nowSpeed = 0;  // 目前轉速級別, 0級停止, 1級100, 2級150, 3級200, 4級255全速
int nowDirection = 0;  // 目前旋轉方向, 0為forward, 1為backward
char* speedMark[] = {"", "+", "++", "+++", "++++"};
int speedPWM[] = {0, 100, 150, 200, 255};

void setup() {
  Serial.begin(9600); 
  pinMode(motorIn1, OUTPUT);
  pinMode(motorIn2, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    cmd = Serial.read();
    Serial.print("Command:");
    Serial.println(cmd);
    switch (cmd) {
      case '8':    // forward 全速      
        nowSpeed = 4;
        nowDirection = 0;
        changeSpeed();
        break;
      case '2':    // backward 全速
        nowSpeed = 4;
        nowDirection = 1;
        changeSpeed();
        break;
      case '+':    // 加速
        if (nowSpeed<4) nowSpeed++;
        changeSpeed();
        break;
      case '-':    // 減速
        if (nowSpeed>0) nowSpeed--;
        changeSpeed();
        break;
      /*default:    // 停止
        nowSpeed = 0;
        changeSpeed();
        break;*/
    }
  }
}

// 顯示目前轉向與速度
void showData() {
  if (nowSpeed==0) {
    Serial.println("Stop");
  } else {
    Serial.print(nowDirection==0 ? "Forward ":"Backward ");
    Serial.println(speedMark[nowSpeed]);
  }  
}

// 加減速
void changeSpeed() {
  showData();
  if (nowDirection==0) {
    // forward
    analogWrite(motorIn1, speedPWM[nowSpeed]);
    analogWrite(motorIn2, 0);
  } else {
    // backward
    analogWrite(motorIn1, 0);
    analogWrite(motorIn2, speedPWM[nowSpeed]);
  }
}
