

//本次拿到的七段顯示器是共陽極,
//顧名思義所有,3或8腳位輸入正極
//其他腳位陽位的正極就一起接上了
//輸出時,其他腳位輸出高電壓對應位置熄燈
//低電位亮燈


const int light[4][7] =
{ {1, 0, 0, 0, 0, 0, 0}, //0
  {1, 1, 1, 0, 1, 1, 0}, //1
  {0, 1, 0, 0, 0, 0, 1},
  {0, 1, 0, 0, 1, 0, 0}

};





void setup() {
  // put your setup code here, to run once:
  /*對應除了3&8外,1~10號腳位*/

  pinMode(7, OUTPUT);//1
  pinMode(8, OUTPUT);//2
  pinMode(9, OUTPUT);//4
  pinMode(10, OUTPUT);//5
  pinMode(11, OUTPUT);//6
  pinMode(12, OUTPUT);//7
  pinMode(13, OUTPUT);//9


}

void loop() {
  // put your main code here, to run repeatedly:

  for (int i = 0; i < 7; i++) {
    digitalWrite(i + 7, light[3][i]);

  }

  delay(1000);
  for (int i = 0; i < 7; i++) {
    digitalWrite(i + 7, light[2][i]);

  }
  delay(1000);
  for (int i = 0; i < 7; i++) {
    digitalWrite(i + 7, light[1][i]);

  }
  delay(1000);
  for (int i = 0; i < 7; i++) {
    digitalWrite(i + 7, light[0][i]);

  }
  delay(1000);


  /*digitalWrite(7,0);
    digitalWrite(8,1);
    digitalWrite(9,LOW);
    digitalWrite(10,LOW);
    digitalWrite(11,LOW);
    digitalWrite(12,LOW);
    digitalWrite(13,LOW);*/


}
