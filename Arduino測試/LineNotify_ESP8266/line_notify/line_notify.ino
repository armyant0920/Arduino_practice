#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <DFRobot_DHT11.h>
#include <TridentTD_LineNotify.h>


// 修改成上述寄到登入郵箱的 Token號碼
#define LINE_TOKEN "YMuR8fMGooZWfdHkbhy8XRRR6gSYvb2ABbHsIJ1kUrP"
#define DHT11_PIN 2
DFRobot_DHT11 DHT;

// 設定無線基地台SSID跟密碼
//const char* ssid     = "Galaxy A52s 5G425B";
//const char* password = "armyant0920";

const char* ssid     = "Home-2.4G";
const char* password = "home3258440";
const char* host = "maker.ifttt.com";
const int httpPort = 80;

int runtimes=0;

void setup(void)
{
  Serial.begin(9600);  // 設定速率 感測器


  WiFi.mode(WIFI_STA);
  // 連接無線基地台
  WiFi.begin(ssid, password);
  Serial.print("\n\r \n\rWorking to connect");

  // 等待連線，並從 Console顯示 IP
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
 
void loop(void)
{
 
  

  DHT.read(DHT11_PIN);
  Serial.print("temp:");
  Serial.print(String(DHT.temperature));
  Serial.print("  humi:");
  Serial.println(String(DHT.humidity));

  // 顯示 Line版本
  //Serial.println(LINE.getVersion());
 
  LINE.setToken(LINE_TOKEN);

  // 先換行再顯示
  runtimes++;
   
  LINE.notify("\n runtime:"+String(runtimes)+"\n temp:" + String(DHT.temperature)+"\n humi:"+String(DHT.humidity));

  WiFiClient client;
  Serial.println("connect to");
  Serial.println(host);

  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");

  }else{
     String IFTTT_str = "POST /trigger/temperature_received/with/key/c55TxL70wULh1ZvxpQgbcR?value1="+String(DHT.temperature)+"&value2="+String(DHT.humidity)+" HTTP/1.1\r\n"
    + "Host: " + host + "\r\n" + "User-Agent: BuildFailureDetectorESP32\r\n" + "Connection: close\r\n\r\n";    
    Serial.println("post url:");
    Serial.println(IFTTT_str);
    client.print(IFTTT_str);
    client.stop();
    
    }
 
  
 
  // 每30分鐘發送一次
  delay(1800000);
}
