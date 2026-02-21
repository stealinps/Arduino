void setup(){
  Serial.begin(9600);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
}
int potval;
void loop(){
  potval=analogRead(A0);
  analogWrite(9,potval/4);
}
