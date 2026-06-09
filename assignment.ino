int enA = 9;
int in1 = 8;
int in2 = 7;
int buzzer=13;
int enB = 3;
int in3 = 5;
int in4 = 4;
int trig=10;
int echo=11;
int led=2;
int ldr=A0;
int ir=A1;

void setup() {
  	Serial.begin(9600);
	
  	pinMode(A0, INPUT);
	pinMode(enA, OUTPUT);
	pinMode(enB, OUTPUT);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);
  	pinMode(trig,OUTPUT);
  	pinMode(echo,INPUT);
	pinMode(buzzer,OUTPUT);
	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
}

void loop() {
  	int ldrval=analogRead(ldr);
  	int irval=analogRead(ir);
  	Serial.print(irval);
  	if(ldrval<10){
   		digitalWrite(led,HIGH);
  	}
  	else{
  		digitalWrite(led,LOW);
  	}
  	
 	if(irval<500){
  		delay(5000);
  	}
  	
  	digitalWrite(trig, LOW);
  	delayMicroseconds(2);
  	digitalWrite(trig, HIGH);
  	delayMicroseconds(10);
  	digitalWrite(trig, LOW);
  	double cm;
  	double duration;
  	duration = pulseIn(echo, HIGH);
  	cm = microsecondsToCentimeters(duration);
  	
  	Serial.print(" ");
  	Serial.print(ldrval);
  	Serial.print(" ");
  	Serial.print(cm);
  	Serial.print("cm");
  	Serial.println();
  	if(cm>20){
      	digitalWrite(buzzer,LOW);
  		digitalWrite(in1,HIGH);
      	digitalWrite(in3,HIGH);
    }
  else {
    	digitalWrite(buzzer,HIGH);
      	digitalWrite(in1,LOW);
      	digitalWrite(in3,LOW);
    }
	
}


long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
