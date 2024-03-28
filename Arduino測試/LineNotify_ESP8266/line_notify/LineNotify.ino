#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <DFRobot_DHT11.h>
#include <TridentTD_LineNotify.h>
#include <ESP8266WebServer.h>


// 修改成上述寄到登入郵箱的 Token號碼
#define LINE_TOKEN "YMuR8fMGooZWfdHkbhy8XRRR6gSYvb2ABbHsIJ1kUrP"
#define LINE_TOKEN2 "Xn5g6Racqx4heXSWElvUozVuDJ0K28Q5ODOBHiTp5h4"
#define DHT11_PIN 2
DFRobot_DHT11 DHT;

// 設定無線基地台SSID跟密碼,加入多組備用wifi組合,注意只能吃2.4G,若是吃熱點須調整為2.4G
const char* ssidList[]     = {"Galaxy A52s 5G425B","Home-2.4G"};
const char* passwordList[] = {"armyant0920","home3258440"};
const int connectTimes[] ={60,10};//連線時間
const char* lineNotifyHost = "notify-api.line.me";
const char* host = "192.168.54.86";//"sunbird-special-werewolf.ngrok-free.app";
const int https_port = 443;
const int http_port = 80;
int runtimes=0;

unsigned long lastSendTime = 0;

//實驗共用變數
int interval;//執行間隔
enum ServiceType{
  LINENOTIFY,
  MYAPI,
  CUSTOM
};

ESP8266WebServer server(80);

String getMac(){
  return WiFi.macAddress();

}


void setup()
{
  Serial.begin(9600);  // 設定速率 感測器
  String wifi_name="";

  WiFi.mode(WIFI_STA);
  // 連接無線基地台
  while(WiFi.status()!=WL_CONNECTED)
  {//當wifi不是連線狀態
    for(int i=0;i<2;i++)
    {
      wifi_name=String(ssidList[i]);
      Serial.print("\ntrying Working to connect: "+wifi_name+"\n");   
      WiFi.begin(wifi_name, passwordList[i]);   
      int attempt =0;//等待次數
      int connectTime = connectTimes[i];
      while(WiFi.status()!=WL_CONNECTED && attempt< connectTime)
      {
        Serial.print(".");
        attempt++;
        delay(1000);//每秒確認一次
        

      }
      if(WiFi.status()==WL_CONNECTED){
        break;
      }
    }
  }

  // 若連線成功，從 Console顯示 IP

  Serial.println("\nConnected to: "+wifi_name);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("WifiMac:"+getMac());
  server.on("/test1",HTTP_GET,getInfo);
  server.begin();
  Serial.println("server started");
}
void getInfo(){
  String info = getMac();
  server.send(200,"text/plain",info);

}

void echo(){
  String info = getMac();
  Test(info);


}
 
void loop()
{

  unsigned long currentTime=millis();

  
  server.handleClient();

  if(runtimes==0 || currentTime-lastSendTime >= 60*5*1000  ){
    lastSendTime=currentTime;
    DHT.read(DHT11_PIN);
    Serial.print("temp:");
    Serial.print(String(DHT.temperature));
    Serial.print("  humi:");
    Serial.println(String(DHT.humidity));
     LINE.setToken(LINE_TOKEN);

    // 先換行再顯示
    runtimes++;

    //LINE.notify("\n runtime:"+String(runtimes)+"\n temp:" + String(DHT.temperature)+"\n humi:"+String(DHT.humidity));

    String postData="value1="+String(DHT.temperature)+"&value2="+String(DHT.humidity);  

    //測試line
    PostMessage(LINENOTIFY,postData);
    Test(postData);
  }

  // 顯示 Line版本
  //Serial.println(LINE.getVersion());
 
 
  //PostMessage(LINENOTIFY,"just sample data");
  //測試自機API
  //PostMessage("sunbird-special-werewolf.ngrok-free.app",https_port,"myapi/DHT",CUSTOM,postData);
  
  /*    		
  WiFiClientSecure client;
	client.setInsecure();		   
  Serial.println("connect to");
  Serial.println(lineNotifyHost);
  if (!client.connect(lineNotifyHost, https_port)) {
    Serial.println("connection failed");

  }else{
    String postData="value1:"+String(DHT.temperature)+String("&value2:")+String(DHT.humidity);

    // String IFTTT_str = String("POST /myapi/DHT HTTP/1.1\r\n")
    // +String("Content-Type: application/x-www-form-urlencoded\r\n")
    // +String("Host: " + String(host) + "\r\n" + "User-Agent: BuildFailureDetectorESP32\r\n")
    // +String( "Content-Length:" + String(len)+"\r\n" + "Connection: close\r\n\r\n"+postData);    
    String IFTTT_str = 
    "POST /api/notify HTTP/1.1\r\n"
    +String("Host: " + String(lineNotifyHost) + "\r\n") 
    +"Authorization:Bearer " + String(LINE_TOKEN2) + "\r\n" 
    +"Content-Type: application/x-www-form-urlencoded\r\n"
    +String("Connection:close\r\n")
    +"Content-Length:" + String(postData.length())+"\r\n\r\n" 
    +"message=" + postData;
    
    Serial.println("post url:");
    Serial.println(IFTTT_str);
    client.print(IFTTT_str);
    client.stop();
    
    } 
  */
  
 
  // 每30分鐘發送一次
  //delay(60*5*1000);//1800000
}

void PostMessage(ServiceType type,String data){
  switch(type){
    case LINENOTIFY:
      PostMessage(lineNotifyHost,https_port,"",LINENOTIFY,data);
      break;
    case MYAPI:
      break;
    deault:
      Serial.println("invaild type setting");

  }
}

void Test(String postData){
  String test_host="192.168.54.86"; 
  int test_port=80;
  WiFiClient client ;
  String request;
  Serial.println("connect to");
    Serial.println("host:"+String(test_host)+" port:"+test_port);
  if(!client.connect(test_host,test_port)){
    Serial.println("connect fail");

  }else{
    Serial.println("connect success");
    
    request = 
        "POST /"
        +String("myapi/DHT") 
        +" HTTP/1.1\r\n"
        +String("Host: " + String(host) + "\r\n")        
        +"Content-Type: application/x-www-form-urlencoded\r\n"
        
        +"Content-Length:" + String(postData.length())+"\r\n" 
        +String("Connection:close\r\n\r\n")
        +postData;

        Serial.println("Test send data: ");
        Serial.println("DEBUG:request=\n"+request);
          client.print(request);
          //嘗試取得response 
          if(client.connected() && client.available()){
            Serial.println("wait for response..:");
            while(client.available()){
              String line = client.readStringUntil('\r');
              Serial.println(line);         
            } 
            Serial.println("closing connection");
            client.stop();
          }


  }
  


}

//待補method
void PostMessage(String host,int port,String path,ServiceType type, String data){


    if(host.isEmpty()){
          return;
    }

    WiFiClientSecure client;
    client.setInsecure();
    Serial.println("connect to");
    Serial.println("host:"+host+" port:"+port);
    if (!client.connect(host, port)) {
      Serial.println("connection failed");
      return;
    }

    String request;
    switch (type){
       case LINENOTIFY:
        //data = "\""+data + "\"";
        request = 
        "POST /api/notify HTTP/1.1\r\n"
        +String("Host: " + String(lineNotifyHost) + "\r\n") 
        +"Authorization:Bearer " + String(LINE_TOKEN2) + "\r\n" 
        +"Content-Type: application/x-www-form-urlencoded\r\n"
        +String("Connection:close\r\n")
        +"Content-Length:" + String(data.length()+strlen("message="))+"\r\n\r\n" //這邊發現line固定的參數'message='的名稱似乎也會被算進長度,所以長度還要額外+8
        +"message=" +data;      
       break;

       case MYAPI:
         
       break; 

       case CUSTOM:
        
        request = 
        "POST /"
        +String(path) 
        +" HTTP/1.1\r\n"
        +String("Host: " + String(host) + "\r\n")        
        //+"Content-Type: application/x-www-form-urlencoded\r\n"
        +String("Connection:close\r\n")
        +"Content-Length:" + String(data.length())+"\r\n" 
        +data;
       break;

    }
    Serial.println("DEBUG:type="+String(type)+"\n request=\n"+request);
    client.print(request);
    //嘗試取得response 
    if(client.connected() && client.available()){
      Serial.println("wait for response..:");
      while(client.available()){
        String line = client.readStringUntil('\r');
        Serial.println(line);         
      } 
      Serial.println("closing connection");
      client.stop();
    }
    

}

