#include <Servo.h> 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo servoMain;

int repeathour=0;
int repeatmin=1;
int repeatsec=0;

int repeattime=repeatsec+(repeatmin*60)+(repeathour*60*60); //get repeating time in secs

void setup(){
  servoMain.attach(9);
  lcd.begin();
  lcd.backlight();
  lcd.print("Hello Fish!");
  lcd.clear();
  lcd.setCursor(0, 0);
  Serial.begin(9600);
  Serial.print("H");
  Serial.print(" ");
  Serial.print("M");
  Serial.print(" ");
  Serial.println("S");
  lcd.print("H");
  lcd.print(" ");
  lcd.print("M");
  lcd.print(" ");
  lcd.print("S");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("H");
  lcd.print(" ");
  lcd.print("M");
  lcd.print(" ");
  lcd.print("S");
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

    Serial.print(h);
    Serial.print(" ");
    Serial.print(m);
    Serial.print(" ");
    Serial.println(s);

    lcd.setCursor(0, 1); // second row, keeps H M S header on row 0 intact
    printPadded(h);
    lcd.print(" ");
    printPadded(m);
    lcd.print(" ");
    printPadded(s);

    if(((h*60*60)+(m*60)+s) % repeattime == 0){
      eat();
    }

    millisbefore += 1000;
  }
}

// prints a value as 2 characters wide so leftover digits from a
// previous longer value (e.g. "10" -> "9") never get left behind
void printPadded(unsigned long val){
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
