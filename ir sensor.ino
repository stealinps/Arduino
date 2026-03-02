void setup() {
  pinMode(35, INPUT);   
  pinMode(2, OUTPUT);    
}

void loop() {
  int irState = digitalRead(35)
  if (irState == LOW) {
    digitalWrite(2, HIGH);  
  } 
else {
    digitalWrite(2, LOW);   
  }
}
