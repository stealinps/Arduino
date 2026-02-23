#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int trig = 7;
const int echo=8;


void setup()
{
	lcd.begin();
	lcd.backlight();
	lcd.setCursor(0, 0); 
	lcd.print("Distance");
	lcd.setCursor(0, 1);  
	lcd.print("Measurement!");
	delay(1000);
	lcd.clear();
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
  delay(500);
	lcd.clear();
}
long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
} 

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

