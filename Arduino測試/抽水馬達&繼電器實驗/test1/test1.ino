
int current=0;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  

  digitalWrite(12, HIGH); 

  Serial.println("start");

}

void loop() {
  // put your main code here, to run repeatedly:
  setCurrent();
  delay(3000000);
  

}

void setCurrent(){

  digitalWrite(11, HIGH); 
  delay(600000);
  digitalWrite(11, LOW); 

  /*if(current==30){
    current=0;
    }*/ 
  
  /*Serial.println("current="+String(current));
  if(current==0){

     digitalWrite(11, HIGH); 
    }else{
      digitalWrite(11, LOW); 
      }

   current++;*/
   
  
  
  
  
  }
