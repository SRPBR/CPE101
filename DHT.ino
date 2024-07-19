#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);; 
void setup() {
  Serial.begin(9600);
  Serial.println("อุณหภูมิและความชื้น โรงเรือนเพาะเลี้ยงเห็ดนางฟ้า");
  dht.begin();
  
}

void loop() {
  lcd.begin();
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("ผิดพลาด");
    lcd.print("Failse");
    return;}
    Serial.print("อุณหภูมิ: ");
    Serial.print(t);
    Serial.print("°C ");
    Serial.print("ความชื้น: ");
    Serial.print(h);
    Serial.println("%");
    
    lcd.print("Tem: ");
    lcd.print(t);
    lcd.print(" C ");
    lcd.setCursor(0,1);
    lcd.print("Hum: ");
    lcd.print(h);
    lcd.print(" % ");
    lcd.setCursor(0,2);
  }
