/*
    This sketch demonstrates how to set up a simple HTTP-like server.
    The server will set a GPIO pin depending on the request
      http://server_ip/gpio/0 will set the GPIO2 low,
      http://server_ip/gpio/1 will set the GPIO2 high
    server_ip is the IP address of the ESP8266 module, will be
    printed to Serial when the module is connected.
*/

#include <ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "your-ssid"
#define STAPSK  "your-password"
#endif

const int motorIn1 = 5;
const int motorIn2 = 6;
const int motorIn3 = 9;
const int motorIn4 = 10;

const byte IR_RECEIVE_PIN=11;
char cmd;  // 接收序列埠傳來的指令
int nowSpeed = 2;  // 目前轉速級別, 0級停止, 1級100, 2級150, 3級200, 4級255全速
int nowDirection = 0;  // 目前旋轉方向, 0為forward, 1為backward
char* speedMark[] = {"", "+", "++", "+++", "++++"};
int speedPWM[] = {0, 100, 150, 200, 255};
long input;
int now=0;


const char* ssid = "Galaxy A52s 5G425B";//STASSID;
const char* password = "armyant0920";//STAPSK;

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  pinMode(motorIn1, OUTPUT);
  pinMode(motorIn2, OUTPUT);
  pinMode(motorIn3, OUTPUT);
  pinMode(motorIn4, OUTPUT);
  

  // prepare LED
  //pinMode(13, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 0);

  // Connect to WiFi network
  Serial.println();

  Serial.print(F("Connecting to "));
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  Serial.println();
  Serial.println(F("WiFi connected"));

  // Start the server
  server.begin();
  Serial.println(F("Server started"));

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  Serial.println(F("new client"));

  client.setTimeout(5000); // default is 1000

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(F("request: "));
  Serial.println(req);
  client.flush();

  // Match the request
  int val;
  if (req.indexOf(F("/gpio/up")) != -1) {
    val = 0;
    Serial.println("input=0");
  } else if (req.indexOf(F("/gpio/down")) != -1) {
    val = 1;
    Serial.println("input=1");
  }else if (req.indexOf(F("/gpio/left")) != -1){
    val = 2;
    Serial.println("input=1");
    }else if (req.indexOf(F("/gpio/right")) != -1){
    val = 3;
    Serial.println("input=1");
    }else {
    Serial.println(F("invalid request"));
    client.stop();
    return;
    //val = digitalRead(13);
    //Serial.println("input invalid");
    
  }

  switch (val){
          
            case 70://上
               
               nowDirection = 0;
               if(nowSpeed==0){
                nowSpeed++;
                }
               
              break;
            case 21://下
              
              nowDirection = 1;
              if(nowSpeed==0){
                nowSpeed++;
                }
              break;

            case 68://左
              nowDirection = 2;  
              if(nowSpeed==0){
                nowSpeed++;
                }      
              break;

           case  67://右
           nowDirection = 3;  
              if(nowSpeed==0){
                nowSpeed++;
                }     
              
              break;

           case  64://MID
             nowSpeed = 0;

           
              break;

           case 66://*
           if (nowSpeed>0) 
              {nowSpeed--;
              }    
              break;

           case 74://#
           if (nowSpeed<4) 
              {nowSpeed++;
              }
            
              break;
            
           default :
              break;     
              
          }  
          
          moving();


          

  

  

  // Set LED according to the request
  digitalWrite(LED_BUILTIN, val);
  client.flush();

  // read/ignore the rest of the request
  // do not client.flush(): it is for output only, see below
  /*while (client.available()) {
    // byte by byte is not very efficient
    client.read();
  }*/

  // Send the response to the client
  // it is OK for multiple small client.print/write,
  // because nagle algorithm will group them into one single packet
  client.print(F("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html><head><meta charset='UTF-8'></head>\r\nGPIO is now "));
  client.print((val) ? F("high") : F("low"));
  client.print(F("<br><br>Click <a href='http://"));
  client.print(WiFi.localIP());
  client.print(F("/gpio/1'>here</a> to switch LED GPIO on, or <a href='http://"));
  client.print(WiFi.localIP());
  client.print(F("/gpio/0'>here</a> to switch LED GPIO off."));
  client.print(F("<table id='table'><tr><td>X</td><td>U</td><td>X</td></tr><tr><td>L</td><td>S</td><td>R</td></tr><tr><td>X</td><td>D</td><td>X</td></tr></table>"));
  client.print(F("</html>"));

  // The client will actually be *flushed* then disconnected
  // when the function returns and 'client' object is destroyed (out-of-scope)
  // flush = ensure written data are received by the other side
  Serial.println(F("Disconnecting from client"));
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

void moving() 
// 加減速
void moving() {
  showData();

  switch(nowDirection){
    
    case 0://forward
    analogWrite(motorIn1, speedPWM[nowSpeed]);
    analogWrite(motorIn2, LOW);
    analogWrite(motorIn4, speedPWM[nowSpeed]);
    analogWrite(motorIn3, LOW); 
    break;
    
    case 1://back
    analogWrite(motorIn1, LOW);
    analogWrite(motorIn2, speedPWM[nowSpeed]);
    analogWrite(motorIn4, LOW);
    analogWrite(motorIn3, speedPWM[nowSpeed]);   
    break;
    
    case 2://left
    analogWrite(motorIn1, LOW);
    analogWrite(motorIn2, LOW);
    analogWrite(motorIn4, speedPWM[nowSpeed]);
    analogWrite(motorIn3, LOW);  
    break;
    
    case 3://right
    analogWrite(motorIn1, speedPWM[nowSpeed]);   
    analogWrite(motorIn2, LOW);
    analogWrite(motorIn4, LOW);
    analogWrite(motorIn3, LOW);   
    break;
    
    
    
    }

}
