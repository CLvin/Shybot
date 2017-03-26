#include <Servo.h>

Servo wheels;

void setup() {
  wheels.attach(6);

}

void loop() {
  wheels.write(180);
  delay(700);
  wheels.write(0);
  delay(700);

}
