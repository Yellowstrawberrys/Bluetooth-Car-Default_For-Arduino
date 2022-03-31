/*
 Written by Yellowstrawberry Dev.(Eunsoo Jung) | Githubs: https://github.com/Yellowstrawberrys
 Powered by Intl` School of Stuttgart (Sindelfigen Campus) Design Teacher Mr.Godley
 This Code is under The MIT License
 This Code has been written in C++
 This Code has been based on bluetooth moudle HC-05

 Setup-------
 HC-05 rx -> PIN6
 HC-06 tx -> PIN7
*/
#include <SoftwareSerial.h> 

#define rx 6
#define tx 7

SoftwareSerial bluetooth(tx, rx);

char c;
int goBackStack = 0;


//PINS FOR MOTOR
const int A1A = 9;
const int A1B = 10;
const int B1A = 11;
const int B1B = 12;

void setup() {
  //Do not Touch this Part
  Serial.begin(9600);
  bluetooth.begin(9600);
  Init();
}

void Init(){
  //OnStart

  //Init motor output
  pinMode(A1A, OUTPUT);
  pinMode(A1B, OUTPUT);
  pinMode(B1A, OUTPUT);
  pinMode(B1B, OUTPUT);
  
  Serial.println("Ready to Connect Bluetooth | Default password is 0000 or 1234");
}

void loop() {
  //This part this checking client is sending new charater
  if(bluetooth.available() > 0){
    
    //This part is setting variable c to new charater that client sent to arduino
    c = bluetooth.read();

    //This means if c equals charater 'f' then, it will call goFront() method, and it will reset goBackStack
    // *IMPORTANT in almost every language, char means charater and it only allows one letter/charater. a-z, A-Z or number is usefull with Communicating
    if(c == 'f'){
      //Calling goFront() method;
      goFront();
      //Resting goBackStack
      goBackStack = 0;
    }else if(c == 'l'){
      goLeft();
      goBackStack = 0;
    }else if(c == 'r'){
      goRight();
      goBackStack = 0;
    }else if(c == 'b'){
      goBackStack++;
      if(goBackStack == 1)
        Stop();
      else if(goBackStack >= 2){
        //If client sends two back requests, then it calls goBack() method, and rest goBackStack;
        goBack();
        goBackStack = 0;
      }
    }
    //Your Code here
  }

  //DO NOT TOUCH THIS
  //delay(100);
}

void goFront(){
  //on goFront Request
  Serial.println("Front");
  digitalWrite(A1A, HIGH);
  digitalWrite(B1A, HIGH);
  digitalWrite(A1B, LOW);
  digitalWrite(B1B, LOW);
}

void goBack(){
  //on goBack Request
  Serial.println("Back");
  digitalWrite(A1A, LOW);
  digitalWrite(B1A, LOW);
  digitalWrite(A1B, HIGH);
  digitalWrite(B1B, HIGH);
}

void goLeft(){
  //on goLeft Request
  Serial.println("Left");
  digitalWrite(A1A, HIGH);
  digitalWrite(B1A, LOW);
  digitalWrite(A1B, LOW);
  digitalWrite(B1B, HIGH);
}

void goRight(){
  //on goRight Request
  Serial.println("Right");
  digitalWrite(A1A, LOW);
  digitalWrite(B1A, HIGH);
  digitalWrite(A1B, HIGH);
  digitalWrite(B1B, LOW);
}

void Stop(){
  //on Stop Request
  Serial.println("Stop");
  digitalWrite(A1A, LOW);
  digitalWrite(B1A, LOW);
  digitalWrite(A1B, LOW);
  digitalWrite(B1B, LOW);
}
