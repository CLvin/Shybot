#include <Arduino.h>
Motor(2, 3) right;
Motor(4,5) left;

void setup(){


}

void loop(){
  left.setMotorSpeed(50);
  right.setMotorSpeed(50);
  Particle.process();
}
