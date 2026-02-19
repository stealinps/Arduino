const int ledpin=9;
const int butpin=2;
int state;
void setup(){
  pinMode(ledpin,OUTPUT);
  pinMode(butpin,INPUT_PULLUP);
}
void loop(){
  state=digitalRead(butpin);
  if(state==HIGH){
    digitalWrite(ledpin,LOW);
  }
  else{
    digitalWrite(ledpin,HIGH);
  }
}
