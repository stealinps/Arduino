int pin1=9;
int pin2=10;
int pin3=11;
int value1;
int value2;
int value3;
void setup() {
  pinMode(pin1,OUTPUT);
  pinMode(pin2,OUTPUT);
  pinMode(pin3,OUTPUT);
}

void loop() {
  for(value1=0;value1<=255;value1++){
    for(value2=0;value2<=255;value2++){
      for(value3=0;value3<=255;value3++){
        analogWrite(pin1,value1);
        analogWrite(pin2,value2);
        analogWrite(pin3,value3);
      }
    }
  }
}
