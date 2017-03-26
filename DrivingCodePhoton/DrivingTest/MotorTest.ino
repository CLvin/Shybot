#include <Arduino.h>
#include <Motor.h>
Motor right(2, 3);
Motor left(4, 5);
int right1 = 1;
int right2 = 2;
int left1 = 3;
int left2 = 4;

void setup(){
  left.setMotorSpeed(100);
  right.setMotorSpeed(100);
  left.startMotor();
  right.startMotor();

}

void loop(){

  Particle.process();
}
