int pin1 = 9;
int pin2 = 10;
int pin3 = 11;

char serInString[10];
char colorCode;
int colorVal;

void setup() {
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);

  Serial.begin(9600);

  Serial.println("Enter color command (r/g/y 0-255 e.g. \"r34\"):");
}

void loop() {

  if (readSerialString(serInString)) {

    colorCode = serInString[0];
    colorVal = atoi(serInString + 1);

    if (colorVal < 0) colorVal = 0;
    if (colorVal > 255) colorVal = 255;

    Serial.print("Setting color ");
    Serial.print(colorCode);
    Serial.print(" to ");
    Serial.println(colorVal);

    if (colorCode == 'r') {
      analogWrite(pin1, colorVal);
    }
    else if (colorCode == 'g') {
      analogWrite(pin2, colorVal);
    }
    else if (colorCode == 'y') {
      analogWrite(pin3, colorVal);
    }
  }
}

bool readSerialString(char *strArray) {

  int i = 0;

  if (!Serial.available()) {
    return false;
  }

  delay(5); 

  while (Serial.available() && i < 9) {
    strArray[i] = Serial.read();
    i++;
  }

  strArray[i] = '\0';  

  return true;
}
