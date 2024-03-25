  //col,row
  int arr[2][4]={{8,9,10,11},{4,5,6,7}};

void setup() {
  // 初始化為不亮狀態
  for(int i=4;i<=11;i++){
     pinMode(i,OUTPUT);
  }
  


}


void reset  (){

    //4~7是 Line,初始值接低電
  //8~11是 Column,初始值接高電
    for(int i=4;i<=11;i++){
    
      if(i<=7){
          digitalWrite(i,LOW);
        }else{
          digitalWrite(i,HIGH);
          }
      
    }

}

  
  


void loop() {

  //  row1~4 亮


  for(int i=0;i<4;i++){
         
      for(int j=0;j<4;j++){
          //0為col,1為row
          digitalWrite(arr[1][i],HIGH);
          digitalWrite(arr[0][j],LOW);          
              
        }
        
        delay(2000);
        reset();
       
        
    }
  
 

   for(int i=0;i<4;i++){
         
      for(int j=0;j<4;j++){
          //0為col,1為row
          digitalWrite(arr[1][j],HIGH);
          digitalWrite(arr[0][i],LOW);              
        }
        
        delay(2000);
        reset();
       
        
    }
 
  
  
  /*digitalWrite(arr[1][3],HIGH);
  digitalWrite(arr[0][1],LOW);
  
  delay(5000);
  reset();

  digitalWrite(arr[1][1],HIGH);
  digitalWrite(arr[0][1],LOW);


  delay(5000);*/


  
  

}
