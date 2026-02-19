#include <Servo.h> 
Servo servoMain;
void setup(){
  servoMain.attach(9);
}
void loop(){
  servoMain.write(0);
  delay(500);
  servoMain.write(180);
  delay(500);

}
