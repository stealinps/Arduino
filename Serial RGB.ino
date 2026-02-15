int pin1 = 9;
int pin2 = 10;
int pin3 = 11;

int redVal = 0;
int greenVal = 0;
int yelVal = 0;

int i;

void setup() {
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  Serial.begin(9600);
  analogWrite(pin1,127);
  analogWrite(pin2,127);
  analogWrite(pin3,127);
  Serial.println("Enter color command(r/g/y 0-255 e.g. \"r34\"):");
}
char serInString[10];
char colorCode;
int colorVal;
void loop() {
  readSerialString(serInString);
  colorCode=serInString[0];
  if(colorCode=='r'||colorCode=='g'||colorCode=='y'){
    colorVal=atoi(serInString+1);
    Serial.print("setting color ");
    Serial.print(colorCode);
    Serial.print(" to ");
    Serial.print(colorCode);
    Serial.print(" ");
    serInString[0]=0;
    if(colorCode=='r'){
      analogWrite(pin1,colorVal);
    }
    else if(colorCode=='g'){
      analogWrite(pin2,greenVal);
    }
    else if(colorCode=='y'){
      analogWrite(pin3,yelVal);
    }
  }
  delay(100);
}

void readSerialString(char *strArray){
  int i=0;
  if(!Serial.available()){
    return;
  }
  while(Serial.available()){
    strArray[i]=Serial.read();
    i++;
  }
}
