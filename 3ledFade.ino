int pin1=9;
int pin2=10;
int pin3=11;
int value;
void setup() {
  pinMode(pin1,OUTPUT);
  pinMode(pin2,OUTPUT);
  pinMode(pin3,OUTPUT);
}

void loop() {
  for(value=0;value<=255;value++){
    analogWrite(pin1,value);
    analogWrite(pin2,value);
    analogWrite(pin3,value);
    delay(10);
  }
  for(value=255;value>=0;value--){
    analogWrite(pin1,value);
    analogWrite(pin2,value);
    analogWrite(pin3,value);
    delay(10);
  }
}
