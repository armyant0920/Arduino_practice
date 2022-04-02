const int R_pin=9;
const int G_pin=10;
const int B_pin=11;

/*int R_value;
int G_value;
int B_value;*/

int color_now[]={0,0,0};


int turnSpeed=10;//每0.01秒調整一次

int color[]={0,0,0};
//boolean RGB[]={true,true,true};

void setup() {
  Serial.begin(9600);
  Serial.println("setup");
  pinMode(R_pin,OUTPUT);
  pinMode(G_pin,OUTPUT);
  pinMode(B_pin,OUTPUT);
    Serial.println("size1="+String(sizeof(color)/sizeof(color[0])));
   // Serial.println("size2="+String(sizeof(color/sizeof(int))));
   
      Serial.println("setup");
  
}

void resetColor(){
  
  color[0]=random(256);
  color[1]=random(256);
  color[2]=random(256);
  Serial.println("color="+String(color[0])+","+String(color[1])+","+String(color[2]));
  
  }

void loop() {

  if(color[0]==color_now[0] && color[1]==color_now[1] && color[2]==color_now[2] ){
    
    resetColor();
    delay(3000);
    
  }
  
  for(int i=0;i< 3;i++){
        if(color_now[i]!=color[i]){
              if(color_now[i]>color[i]){
                  color_now[i]--;
                
                
                }else{
                    color_now[i]++;
                  
                  
                  }   
                    Serial.println("color:="+String(i)+"="+String(color_now[i]));
          
          
          }   
      
    }
  analogWrite(R_pin,color_now[0]);
  analogWrite(G_pin,color_now[1]);
  analogWrite(B_pin,color_now[2]);
  delay(turnSpeed);
    
 
  
  /*analogWrite(R_pin,128);
  analogWrite(G_pin,128);
  analogWrite(B_pin,0);
  delay(5000);
  analogWrite(R_pin,0);
  analogWrite(G_pin,128);
  analogWrite(B_pin,128);
  delay(5000);
  analogWrite(R_pin,128);
  analogWrite(G_pin,0);
  analogWrite(B_pin,128);
  delay(5000);
    analogWrite(R_pin,255);
  analogWrite(G_pin,255);
  analogWrite(B_pin,255);*/
    //delay(1000);
    

  

   
  // put your main code here, to run repeatedly:

}
