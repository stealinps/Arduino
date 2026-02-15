int pin1 = 9;
int pin2 = 10;
int pin3 = 11;

int redVal = 255;
int greenVal = 0;
int blueVal = 0;

int i = 0;

void setup() {
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
}

void loop() {

  if (i < 255) {
    redVal--;
    greenVal++;
    blueVal = 0;
  }
  else if (i < 510) {
    redVal = 0;
    greenVal--;
    blueVal++;
  }
  else if (i < 765) {
    redVal++;
    greenVal = 0;
    blueVal--;
  }
  else {
    i = 0; 
  }

  analogWrite(pin1, redVal);
  analogWrite(pin2, greenVal);
  analogWrite(pin3, blueVal);

  i++;
  delay(10);
}
