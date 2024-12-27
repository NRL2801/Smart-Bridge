#include <Servo.h> //Install this library /Users/NRL/Documents/Arduino/smart_bridge2.0/smart_bridge2.0.ino
//27 Sept 2024
Servo tap_servo1;
Servo tap_servo2;

int sensor_pin = 5;   //Connect D5 of Arduino 
int tap_servo1_pin =4;
int tap_servo2_pin =3;  
int val;
int red = 8;
int yellow = 9;
int green = 10;
int red1 = 11;
int yellow1 = 12;
int green1 = 13;
int buz_delay = 500;
int buz_pin = 7;
int buz_freq = 450;
int buz_duration = 300;
bool yellow_flg = false;
bool red_flg = false;
bool trans_flg = false;

void setup(){
  pinMode(sensor_pin,INPUT);
  tap_servo1.attach(tap_servo1_pin);
  tap_servo2.attach(tap_servo2_pin);
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green,  OUTPUT);
  pinMode(red1, OUTPUT);
  pinMode(yellow1, OUTPUT);
  pinMode(green1,  OUTPUT);
}

void loop(){
  val = digitalRead(sensor_pin);

  if (val==0){//sense water
    if (yellow_flg==true){
     
      digitalWrite(yellow,LOW);
      digitalWrite(yellow1,LOW);
      delay(3000);
    }
      else if (yellow_flg==false){
      digitalWrite(green,LOW);
      digitalWrite(yellow,HIGH);
      digitalWrite(green1,LOW);
      digitalWrite(yellow1,HIGH);
      yellow_flg=true;
      delay(2000);
      }
    
    if (red_flg==false){
    digitalWrite(yellow,LOW);
    digitalWrite(red,HIGH);
    digitalWrite(yellow1,LOW);
    digitalWrite(red1,HIGH);
    yellow_flg=true;
    tone(buz_pin, buz_freq, buz_duration);
    delay (buz_delay);
     tap_servo1.write(90); 
    tap_servo2.write(90); 
    red_flg=true;
    delay (2500);
    }
    else if (red_flg==true){
    digitalWrite(red,LOW);
    digitalWrite(green,HIGH);
    digitalWrite(red1,LOW);
    digitalWrite(green1,HIGH);

    tone(buz_pin, buz_freq, buz_duration);
    delay (buz_delay);

    red_flg=true;
    trans_flg=true;


    }
   
  }
  else if (val==1) { // does not sense water
    if (trans_flg==false){
     tap_servo1.write(0); 
     tap_servo2.write(0);  //If you want you can increase & Decrease servo rotation 
    digitalWrite(red,LOW);
    digitalWrite(yellow,LOW);
    digitalWrite(green,HIGH);
    digitalWrite(red1,LOW);
    digitalWrite(yellow1,LOW);
    digitalWrite(green1,HIGH);
    yellow_flg=false;
    red_flg=false;
    delay (1000);
    }
    else if (trans_flg==true){
      digitalWrite(green,LOW);
      digitalWrite(yellow,HIGH);
      digitalWrite(green1,LOW);
      digitalWrite(yellow1,HIGH);
      delay(2000);
      digitalWrite(yellow,LOW);
      digitalWrite(red,HIGH);
      digitalWrite(yellow1,LOW);
      digitalWrite(red1,HIGH);
      delay(1000);
      tap_servo1.write(0); 
      tap_servo2.write(0);  //If you want you can increase & Decrease servo rotation 
      delay (3000);
      red_flg=false;
      yellow_flg=false;
      trans_flg=false;
    }
  }


}
