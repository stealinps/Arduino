void setup(){
  Serial.begin(9600);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(2,INPUT_PULLUP);
}
int potval=0;
int state;
void loop(){
  state=digitalRead(2);
  Serial.println(state);
  if(state==HIGH){
    potval=analogRead(A0);
  }
  //only change brightness if button not pressed
  analogWrite(9,potval/4);
}
