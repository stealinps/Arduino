#include <WiFi.h>

// Update these to match your Phone's Hotspot settings exactly!
const char* ssid = "Stealinp";
const char* password = "12345678";

// Set web server port number to 80
WiFiServer server(80);

String header;
String output26State = "off";
String output27State = "off";

const int output26 = 26;
const int output27 = 27;
const int statepin = 34; //a switch will be used to  determine the state

enum state{
  offline,online
};
state mode;

unsigned long currentTime = millis();
unsigned long previousTime = 0; 
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  delay(1000); 

  pinMode(output26, OUTPUT);
  pinMode(output27, OUTPUT);
  pinMode(statepin,INPUT);
  digitalWrite(output26, LOW);
  digitalWrite(output27, LOW);
  mode=(state)digitalRead(statepin);
  int i;
  for(i=0;i<255;i++){
    digitalWrite(output26,HIGH);
  } //rotate to clear path and indicate initialization for debugging
  for(i=0;i<255;i++){
    digitalWrite(output27,HIGH);
  } //reverse rotation
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
  if(mode==offline){
    Serial.print("Offline Mode\n");
    Serial.print(" ");
    delay(1000);
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
