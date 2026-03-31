int pin1=9;
int pin2=10;
int pin3=11;
int state=0;
//traffic light system
void setup() {
  pinMode(pin1,OUTPUT);
  pinMode(pin2,OUTPUT);
  pinMode(pin3,OUTPUT);
}

unsigned long lastTime = 0;

void loop() {
  if (millis() - lastTime >= 3000) {
    lastTime = millis();
    switchpin();
  }
}
void switchpin(){
  if(state==0){
    analogWrite(pin1,0);
    analogWrite(pin2,255);
    analogWrite(pin3,0);
    state=1;
  } //merah ke hijau
  else if(state==1){
    analogWrite(pin1,255);
    analogWrite(pin2,0);
    analogWrite(pin3,0);
    state=2;
  } //hijau ke kuning
  else if(state==2){
    analogWrite(pin1,0);
    analogWrite(pin2,0);
    analogWrite(pin3,255);
    state=0;
  } //kuning ke merah
}
