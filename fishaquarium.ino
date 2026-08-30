#include <Servo.h> 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo servoMain;

#define TEMP_PIN A0
#define WL_PIN A1

OneWire oneWire(TEMP_PIN);
DallasTemperature tempSensor(&oneWire);

int repeathour=0;
int repeatmin=1;
int repeatsec=0;

int repeattime=repeatsec+(repeatmin*60)+(repeathour*60*60); //get repeating time in secs

void setup(){
  servoMain.attach(9);
  lcd.begin();
  lcd.backlight();
  lcd.print("Hello Fish!");
  delay(1000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print(" H  M  S   WL T");

  Serial.begin(9600);
  tempSensor.begin();

  servoMain.write(90);
}

unsigned long millisbefore=0;
unsigned long millisafter;

void loop(){
  millisafter=millis();
  if((millisafter-millisbefore)>=1000){
    unsigned long h = millis2hour();
    unsigned long m = millis2min();
    unsigned long s = millis2sec();

    int wl = analogRead(WL_PIN);       

    tempSensor.requestTemperatures();
    float tempC = tempSensor.getTempCByIndex(0);

    Serial.print(h);
    Serial.print(m);
    Serial.print(s);
    Serial.print("WL:");
    Serial.print(wl);
    Serial.print("T:");
    Serial.println(tempC);

    lcd.setCursor(0, 1);
    printPadded2(h);
    lcd.print(" ");
    printPadded2(m);
    lcd.print(" ");
    printPadded2(s);
    lcd.print(" ");
    printPadded4(wl);
    lcd.print(" ");
    lcd.print((int)tempC);

    if(((h*60*60)+(m*60)+s) % repeattime == 0){
      eat();
    }

    millisbefore += 1000;
  }
}

void printPadded2(unsigned long val){
  if(val < 10) lcd.print(" ");
  lcd.print(val);
}

void printPadded4(int val){
  if(val < 1000) lcd.print(" ");
  if(val < 100) lcd.print(" ");
  if(val < 10) lcd.print(" ");
  lcd.print(val);
}

int millis2sec(){
  unsigned long sec=millis()/1000;
  return sec%60;
}
int millis2min(){
  unsigned long min=millis()/(1000UL*60);
  return min%60;
}
int millis2hour(){
  unsigned long hour=millis()/(1000UL*60*60);
  return hour%24;
}

void eat(){
  unsigned long eatbefore=millis();
  while((millis()-eatbefore)<1000){
  servoMain.write(0); //continuous servo
  }
  servoMain.write(90);
}
