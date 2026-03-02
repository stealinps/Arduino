My codes for arduino projects

resistor(r); ground(gnd); red green blue LEDs(RGB); 
power supply(ps); potentiometer(pot); transistor(t);
moisture sensor(ms); motor driver(md);

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

motor driver(L298N)✅
(motors>sides)+(battery+>12v)+(gnd>battery->gnd[microcontroller])+(pin1>en1+pin2>en2+pin3>en3+pin4>en4)


relay ❌

ldr✅ 
[same as resistor]

transistor(npn)✅ 
[(pin/ps>t)+{pin(control)>t(mid)}]>gnd

ir sensor✅
([DAT>pin(input)]+[VCC>5v/3.3V])>gnd

ultrasonic sensor✅
[(5V>VCC)+(pin1>trig)+(pin2>echo)]>gnd

moisture sensor✅ 
([pin ANALOG/DIGITAL>ms(AO/DO)]+5v/ps>vcc)>gnd

lcd✅ 
(VCC>5V)+(gnd>gnd)+(sda>A4)+(scl>A5)

esp32✅
1.install esp32 board package at package manager
2.install esp32 driver
3.use arduino codes

