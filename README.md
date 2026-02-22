My codes for arduino projects
resistor(r); ground(gnd); red green blue LEDs(RGB); 
power supply(ps); potentiometer(pot); transistor(t);

LED✅ 
pin/ps>led>r>gnd

fade RGB✅ 
[(pin1>led1>r1)+(pin2>led2>r2)+(pin3>led3>r3)]>gnd

servo✅ 
pin+ps>servo>gnd

buzzer(buz)✅ 
pin/ps>buz>r>gnd

button(btn)✅ 
pin(input_fullup)>btn>gnd

potentiometer✅ 
[(ps>pot)+(analog pin>pot[mid])]>gnd

motor✅ 
([ps>motor>t]+[pin>t(mid)])>gnd

relay

ldr

transistor

ir sensor

ultrasonic sensor

moisture sensor

lcd
esp32

