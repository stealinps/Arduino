int pin1=9;
int pin2=11;
void setup() {
  pinMode(pin1,OUTPUT);
  pinMode(pin2,OUTPUT);
}

void loop() {
  for(int i=0;i<=255;i=i+5){
    analogWrite(pin1,i);
    delay(10);
  }
  for(int i=255;i>=0;i=i-5){
    analogWrite(pin1,i);
    delay(10);
  }
  for(int i=0;i<=255;i=i+5){
    analogWrite(pin2,i);
    delay(10);
  }
  for(int i=255;i>=0;i=i-5){
    analogWrite(pin2,i);
    delay(10);
  }
}
