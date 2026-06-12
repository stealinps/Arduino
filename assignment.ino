#include <WiFi.h>


const char* ssid = "";
const char* password = "";

// Set web server port number to 80
WiFiServer server(80);

String header;
String output26State = "off";
String output27State = "off";

const int output26 = 26;
const int output27 = 27;
const int statepin = 14; //a switch will be used to  determine the state
const int trig     = 19;
const int echo     = 18;
const int ldr      = 35;
const int ir       = 33;
const int led      = 5;
const int buzzer   = 21;



enum state{
  offline,online
};
state mode;

unsigned long currentTime = millis();
unsigned long previousTime = 0; 
const long timeoutTime = 2000;

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

void setup() {
  Serial.begin(115200);
  delay(1000); 
  
  pinMode(output26, OUTPUT);
  pinMode(output27, OUTPUT);
  pinMode(statepin,INPUT);
  pinMode(ldr,INPUT);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(led,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(statepin,INPUT_PULLUP);

  digitalWrite(output26, LOW);
  digitalWrite(output27, LOW);
  mode=(state)digitalRead(statepin);

  int i;
  for(i=0;i<255;i++){
    digitalWrite(output26,HIGH);
    delay(10);
  } //rotate to clear path and indicate initialization for debugging
  for(i=0;i<255;i++){
    digitalWrite(output26,LOW);
    digitalWrite(output27,HIGH);
    delay(10);
  } //reverse rotation
  digitalWrite(output27,LOW);
  // Clear any old network settings and set to client mode
  WiFi.disconnect(true); 
  delay(500);
  WiFi.mode(WIFI_STA);
  delay(500);
  if(mode==online){
    Serial.print("Connecting to Hotspot: ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    
    // Print new Hotspot-assigned IP address!
    Serial.println("");
    Serial.println("WiFi connected successfully!");
    Serial.print("IP address to type into browser: ");
    Serial.println(WiFi.localIP());
    server.begin();
  }
  else{
    Serial.println("Offline Mode ON\n");
    Serial.println("BEGIN AUTONOMOUS FUNCTIONS");

  }
}

void loop(){
  delay(100);
  if(mode==offline){

    int ldrval=analogRead(ldr);
  	if(ldrval<10){digitalWrite(led,HIGH);}
  	else{digitalWrite(led,LOW);}
  	Serial.print(ldrval);
    Serial.print(" ");

    int irval=analogRead(ir);
  	Serial.print(irval);
 	  
  	
  	digitalWrite(trig, LOW);
  	delayMicroseconds(2);
  	digitalWrite(trig, HIGH);
  	delayMicroseconds(10);
  	digitalWrite(trig, LOW);
  	double cm;
  	double duration;
  	duration = pulseIn(echo, HIGH);
  	cm = microsecondsToCentimeters(duration);
  	while(irval<500){
      digitalWrite(trig, LOW);
      delayMicroseconds(2);
      digitalWrite(trig, HIGH);
      delayMicroseconds(10);
      digitalWrite(trig, LOW);
      duration = pulseIn(echo, HIGH);
      cm = microsecondsToCentimeters(duration);
      if(cm<20&&cm>0){
          Serial.print("Object Detected");
          digitalWrite(output26,LOW);
          digitalWrite(output27,LOW);
          delay(100);
          
      }
      if(cm>20){
          Serial.print("Line Not Detected ");
          digitalWrite(output26,HIGH);
          delay(100);
          digitalWrite(output26,LOW);
          digitalWrite(output27,LOW);
          
      }
      irval=analogRead(ir);
      Serial.print(irval);
      Serial.print(" ");
      Serial.print(cm);
      Serial.print("cm");
      Serial.println();
    }
  	
  	Serial.print(" ");
  	Serial.print(cm);
  	Serial.print("cm");
  	Serial.println();
  	if(cm>20){
      	digitalWrite(buzzer,LOW);
  		  digitalWrite(output27,HIGH);
      	digitalWrite(output26,HIGH);
    }
    else {
    	  digitalWrite(buzzer,HIGH);
      	digitalWrite(output27,LOW);
        digitalWrite(output26,LOW);
    }
  }
  else if(mode==online){
  WiFiClient client = server.available();

  if (client) {
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");
    String currentLine = "";
    while (client.connected() && currentTime - previousTime <= timeoutTime) {
      currentTime = millis();
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        header += c;
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            if (header.indexOf("GET /26/on") >= 0) {
              Serial.println("GPIO 26 on");
              output26State = "on";
              digitalWrite(output26, HIGH);
            } else if (header.indexOf("GET /26/off") >= 0) {
              Serial.println("GPIO 26 off"); //motor 1
              output26State = "off";
              digitalWrite(output26, LOW);
            } else if (header.indexOf("GET /27/on") >= 0) {
              Serial.println("GPIO 27 on"); //motor 2
              output27State = "on";
              digitalWrite(output27, HIGH);
            } else if (header.indexOf("GET /27/off") >= 0) {
              Serial.println("GPIO 27 off");
              output27State = "off";
              digitalWrite(output27, LOW);
            }
            
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            client.println("<body><h1>ESP32 Web Server</h1>");
            client.println("<p>GPIO 26 - State " + output26State + "</p>");
            if (output26State=="off") {
              client.println("<p><a href=\"/26/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/26/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            client.println("<p>GPIO 27 - State " + output27State + "</p>");
            if (output27State=="off") {
              client.println("<p><a href=\"/27/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/27/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");
            
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
    }
  }
  else Serial.print("\nMode is weirdly behaving\n");//for debugging
}
