My codes for arduino projects

resistor(r); ground(gnd); red green blue LEDs(RGB); 
power supply(ps); potentiometer(pot); transistor(t);
moisture sensor(ms);

Resistor✅ 
pin>+led->r>gnd

LED✅ 
pin/ps>led>r>gnd

fade RGB✅ 
[(pin1>led1>r1)+(pin2>led2>r2)+(pin3>led3>r3)]>gnd

servo✅ 
pin+ps>servo>gnd

buzzer(buz)✅ 
pin/ps>+buz->r>gnd

button(btn)✅ 
pin(input_fullup)>btn>gnd

potentiometer✅ 
[(ps>pot)+(analog pin>pot[mid])]>gnd

motor✅ 
([ps>motor>t]+[pin>t(mid)])>gnd

relay

ldr✅ 
[same as resistor]

transistor(npn)✅ 
[(pin/ps>t)+{pin(control)>t(mid)}]>gnd

ir sensor

ultrasonic sensor✅
[(5V>VCC)+(pin1>trig)+(pin2>echo)]>gnd

moisture sensor✅ 
([pin ANALOG/DIGITAL>ms(AO/DO)]+5v/ps>vcc)>gnd

lcd✅ 
(VCC>5V)+(gnd>gnd)+(sda>A4)+(scl>A5)

esp32

