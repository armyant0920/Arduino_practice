/*
  Button

  Turns on and off a light emitting diode(LED) connected to digital pin 13,
  when pressing a pushbutton attached to pin 2.

  The circuit:
  - LED attached from pin 13 to ground through 220 ohm resistor
  - pushbutton attached to pin 2 from +5V
  - 10K resistor attached to pin 2 from ground

  - Note: on most Arduinos there is already an LED on the board
    attached to pin 13.

  created 2005
  by DojoDave <http://www.0j0.org>
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Button
*/

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 7;     // the number of the pushbutton pin
const int ledPin_G =  13;      // the number of the LED pin
const int ledPin_Y =  12;
// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
int current=0;
int times=0;


void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin_G, OUTPUT);
  pinMode(ledPin_Y, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
   Serial.begin(9600);
  Serial.println("start");  
 
}

void loop() {
  // read the state of the pushbutton value:
  current = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:

  if(current!= buttonState){
      delay(50);
      if(current==HIGH){
        
          times+=1;
          Serial.println("on :"+String(times));
                 
        }else{
         Serial.println("off");   
          }
        buttonState=current;
    }
    
  if (current == HIGH) {
      
    // turn LED on:
    digitalWrite(ledPin_G,HIGH );
    digitalWrite(ledPin_Y,LOW );
   
  } else {
    // turn LED off:
    digitalWrite(ledPin_G,LOW);
    digitalWrite(ledPin_Y,HIGH );

    
  }
}
