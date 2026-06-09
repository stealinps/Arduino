const int trig=19;
const int echo=18;
const int ldr=35;
void setup() {
  // put your setup code here, to run once:
  pinMode(16,OUTPUT);
  pinMode(17,OUTPUT);
  pinMode(22,OUTPUT);
  pinMode(5,OUTPUT);
  Serial.begin(9600);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(ldr,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  double cm;
  double duration;
  duration = pulseIn(echo, HIGH);
  cm = microsecondsToCentimeters(duration);
  Serial.print(analogRead(ldr));
  Serial.print(" ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  if(analogRead(ldr)<15){
    digitalWrite(5,HIGH);
  }
  else{ 
    digitalWrite(5,LOW);}
  if(cm>10){
  digitalWrite(22,LOW);
  digitalWrite(16,HIGH);
  delay(1000);
  digitalWrite(16,LOW);
  delay(1000);
  digitalWrite(17,HIGH);
  delay(1000);
  digitalWrite(17,LOW);
  delay(1000);
  }
  else digitalWrite(22,HIGH);
}
long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
