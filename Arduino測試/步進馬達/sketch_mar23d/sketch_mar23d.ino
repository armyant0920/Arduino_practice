/*
* 步进电机跟随电位器旋转
* (或者其他传感器)使用0 号模拟口输入
* 使用arduino IDE 自带的Stepper.h 库文件
*/
/*#include <Stepper.h>
// 这里设置步进电机旋转一圈是多少步
#define STEPS 100
// attached to 设置步进电机的步数和引脚
Stepper stepper(STEPS, 9, 10, 11, 12);
// 定义变量用来存储历史读数
int previous = 0;
void setup()
{
// 设置电机每分钟的转速为90 步a
stepper.setSpeed(180
);
}
void loop()
{
// 获取传感器读数
int val = analogRead(0);
// 移动步数为当前读数减去历史读数
stepper.step(val - previous);
// 保存历史读数
previous = val;
}*/



#include <Unistep2.h>

Unistep2 stepper(9,10,11,12,4096,1000);
int direction=1;
void setup(){

  Serial.begin(9600);
  Serial.println("setup");
  }
void loop(){
    stepper.run();
    
if(stepper.stepsToGo()==0){
    /*delay(500);
    direction*=-1;*/
    stepper.move(4096*direction);
    
    
  
  }
    
  
  
  }

  
