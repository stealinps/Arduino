int pin1 = 9;
int pin2 = 10;
int pin3 = 11;

int redVal = 0;
int greenVal = 0;
int yelVal = 0;

int i = 0;

void setup() {
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  delay(500);
  for(i=0;i<255;i++){
    redVal++;
    analogWrite(pin1, redVal);
    analogWrite(pin2, greenVal);
    analogWrite(pin3, yelVal);
    delay(20);
  }
  i=0;
}

void loop() {

  if (i < 255) {
    redVal--;
    greenVal++;
    yelVal = 0;
  }
  else if (i < 510) {
    redVal = 0;
    greenVal--;
    yelVal++;
  }
  else if (i < 765) {
    redVal++;
    greenVal = 0;
    yelVal--;
  }
  else {
    i = 0; 
    redVal=255;
    greenVal = 0;
    yelVal=0;
  }

  analogWrite(pin1, redVal);
  analogWrite(pin2, greenVal);
  analogWrite(pin3, yelVal);

  i++;
  delay(20);
}
