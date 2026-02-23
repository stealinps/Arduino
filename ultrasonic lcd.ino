#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int trig = 7;
const int echo=8;


void setup()
{
	pinMode(9,OUTPUT);
	pinMode(10,OUTPUT);
	pinMode(11,OUTPUT);
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
	if(cm<10){
		analogWrite(9,100);
		analogWrite(10,100);
		analogWrite(11,100);
		lcd.setCursor(0, 1); 
		lcd.print("Too close!");
	}
	else{
		analogWrite(9,0);
		analogWrite(10,0);
		analogWrite(11,0);
	}
  delay(500);
	lcd.clear();
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
