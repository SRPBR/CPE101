#include <Bounce2.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);; 
Bounce sw1 = Bounce();
Bounce sw2 = Bounce();
Bounce sw3 = Bounce();
Bounce sw4 = Bounce();
#define sw_left 26
#define sw_right 27
#define sw_stop 14
#define sw_limitL 33
#define sw_limitR 25
#define sw_remote 12
#define Ry1 16
#define Ry2 17
int statestop = 1,statelimit = 0,limit = 0,remote = 0;

#define BLYNK_TEMPLATE_ID "TMPL6HsV8oebV"
#define BLYNK_AUTH_TOKEN "2jRlc_dN9BQLRnx4HjFeuND74gc7y4fS"
#define BLYNK_DEVICE_NAME "Blynk"
#define BLYNK_FIRMWARE_VERSION        "0.1.0"
#define BLYNK_PRINT Serial
#define APP_DEBUG
#include "BlynkEdgent.h"
#define sw_left_Blynk V1
#define sw_right_Blynk V3
#define sw_stop_Blynk V2

int i;


BLYNK_WRITE(sw_left_B){i = param.asInt();
    if (i == 1){
      Left();
      
      }
    }
    
BLYNK_WRITE(sw_right_B){i = param.asInt();
    if (i == 1){
      Right();
     
      }
    }

BLYNK_WRITE(sw_stop_B){i = param.asInt();
    if (i == 1){
      Stop();
      
      }
    }
void limitswitch(){
  if(limit == 1){
    if(digitalRead(sw_limitL) == 0){
      statelimit = 1;
      lcd.setCursor(0,1);
      lcd.print("Status Stop    "); 
      digitalWrite(Ry1,LOW);
      digitalWrite(Ry2,LOW);
    }
  }
  if(limit == 2){
    if(digitalRead(sw_limitR) == 0){
      statelimit = 2;
      lcd.setCursor(0,1);
      lcd.print("Status Stop    "); 
      digitalWrite(Ry1,LOW);
      digitalWrite(Ry2,LOW);
    }
  }
}
void Left(){

    lcd.setCursor(0,1);
    lcd.print("Status Left   ");  
    digitalWrite(Ry1,HIGH);
    digitalWrite(Ry2,LOW);
    statestop = 0;
    limit = 1;
    Blynk.virtualWrite (sw_left_Blynk,1);
          Blynk.virtualWrite (sw_stop_Blynk,0);
          Blynk.virtualWrite (sw_right_Blynk,0);
}

void Stop(){
     lcd.setCursor(0,1);
     lcd.print("Status Stop    ");                                   
     digitalWrite(Ry1,LOW);
     digitalWrite(Ry2,LOW);
     statestop = 1;
     statelimit = 0;
     Blynk.virtualWrite (sw_stop_Blynk,1);
          Blynk.virtualWrite (sw_left_Blynk,0);
          Blynk.virtualWrite (sw_right_Blynk,0);
}

void Right(){
     lcd.setCursor(0,1);
     lcd.print("Status Right");
     digitalWrite(Ry1,LOW);
     digitalWrite(Ry2,HIGH);
     statestop = 0;
     limit = 2;
      Blynk.virtualWrite (sw_right_Blynk,1);  
        Blynk.virtualWrite (sw_left_Blynk,0);
        Blynk.virtualWrite (sw_stop_Blynk,0);
}

void select(){
     sw1.update();
     sw2.update();
     sw3.update();
     limitswitch();
     Remote();
     if ((sw1.fell() && statelimit != 1) || (sw4.fell() && remote == 1 && statelimit != 1)){
       if(statestop == 0){
        Stop();
        delay(2000);
       }
       remote = 1;
       Left();
       
     }
     if (sw2.fell() || remote == 2 || remote == 4) {
       if(remote == 4){
        remote = 0;
       }
       if(sw2.fell()){
          if(remote <= 2){
            remote = 2;
          }else{
            remote = 4;
          }
       }
       Stop();
       
     }
     if (sw3.fell() && statelimit != 2 || (sw4.fell() && remote == 3 && statelimit != 2)) {
       if(statestop == 0){
        Stop();
        delay(2000);
       }
       remote = 3;
       Right();  
       
     }
     
}
void Remote(){
  sw4.update();
  if (sw4.fell()) {
    remote = remote + 1;
  }

}
void setup() {
    sw1.attach(sw_left,INPUT_PULLUP);
    sw1.interval(25);
    sw2.attach(sw_right,INPUT_PULLUP);
    sw2.interval(25);
    sw3.attach(sw_stop,INPUT_PULLUP);
    sw3.interval(25);
    sw4.attach(sw_remote,INPUT_PULLUP);
    sw4.interval(25);
    pinMode(Ry1,OUTPUT);
    pinMode(Ry2,OUTPUT);
    pinMode(sw_limitL,INPUT_PULLUP);
    pinMode(sw_limitR,INPUT_PULLUP);
    digitalWrite(Ry1,LOW);
    digitalWrite(Ry2,LOW);
    Serial.begin(9600);
    lcd.begin();
    lcd.backlight();
    delay(2000);
    lcd.setCursor(0,0);
    lcd.print("Motor Controller");
    BlynkEdgent.begin();
    
}

void loop() {
  select();
  BlynkEdgent.run();
}

    
