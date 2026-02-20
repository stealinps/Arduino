int pin1 = 9;
int pin2 = 10;
int pin3 = 11;
const int butpin=2;
int state;
int redVal = 0;
int greenVal = 0;
int yelVal = 0;
unsigned long lastPress = 0;
bool lastState = HIGH;
int i;

void setup() {
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(butpin,INPUT_PULLUP);
  
  for(i = 0; i < 255; i++){
    analogWrite(pin1, redVal);
    redVal++;
    delay(10); 
  }
  i=0;
}
void loop() {
  int phase = i / 255;
  int step = i % 255;
state = digitalRead(butpin);

if (lastState == HIGH && state == LOW) {  
    if (millis() - lastPress > 500) {     
        i = ((i / 255 + 1) % 3) * 255;    
        lastPress = millis();
    }
}

lastState = state;


  if(state==LOW){
    analogWrite(pin1, 0);
    analogWrite(pin2, 0);
    analogWrite(pin3, 0);
    i = (i + 255) % 765;
  }
  else{
    switch (phase) {
    case 0: 
      redVal   = 255 - step;
      greenVal = step;
      yelVal  = 0;
      break;
    case 1: 
      redVal   = 0;
      greenVal = 255 - step;
      yelVal  = step;
      break;
    case 2: 
      redVal   = step;
      greenVal = 0;
      yelVal  = 255 - step;
      break;
  }

  analogWrite(pin1, redVal);
  analogWrite(pin2, greenVal);
  analogWrite(pin3, yelVal);
  i = (i + 1) % 765;
  }

   
  delay(10);
}
