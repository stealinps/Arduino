#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int trig = 7;
const int echo=8;


void setup()
{
	lcd.begin();
	lcd.backlight();
	lcd.print("Hello, world!");
	Serial.begin(9600);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
}

void loop()
{
	long duration, cm;

  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  cm = microsecondsToCentimeters(duration);
  
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
	lcd.print(cm);
	lcd.print("cm");
	lcd.print(" ");

  delay(1000);
}
long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
} 

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
