//Driving Code

#include <Arduino.h>

left Motor(2, 3);
right Motor(4,5);
int photoRes = A0; //photoresistor pin
int newPhoto = 1; //1 if want new photo, 0 if not ready for new photo
int direction = 0; // NSEW
int heading = 2; //straight ahead


void setup(){
   pinMode(photoRes, INPUT); //attach photoresistor
   Particle.subscribe("direction", chooseDir); //subscribe to results from camera
   gameInit(); // do initial check of surroundings

}


void loop(){
  //check photoResistor value to determine if dark place has been reached
  Particle.process();
  lightLevel = analogRead(photoRes);
  if (lightLevel < 300){
    left.stopMotor();
    right.stopMotor();
    waitTime(); //enter wait stage of game

  }
  if (range sensor indicates being near a wall slow down){
    int speedL = left.getMotorSpeed();
    int speedR = right.getMotorSpeed();
    left.setMotorSpeed(speedL/2);
    right.setMotorSpeed(speedR/2);
    newPhoto = 1; //allow new photo
  }
  if (right bumper){
    turnLeft(22.5);
    newPhoto = 1; //allow new photo
  }
  if (left bumper){
    turnRight(22.5);
    newPhoto = 1; //allow new photo
  }
  if (both bumpers){
    driveBack();
    newPhoto = 1; //allow new photo
  }
  else { //if none of the other things occur
    driveStraight(70);
  }
}

void gameInit(){
  //facing direction 0
  //takePhoto
  turnLeft(90);
  //facing direction 1
  //takePhoto
  delay(100);
  Particle.process();
  turnLeft(90);
  //facing direction 2
  //takePhoto
  delay(100);
  Particle.process();
  turnLeft(90);
  //facing direction 3
  //takePhoto
  delay(100);
  Particle.process();
  //determine best heading based on photos
  //direction
  if (direction == 0){
    turnLeft(90);
    if (heading == 0){
      turnRight(45);
    }
    else if (heading == 1){
      turnRight(22.5);
    }
    else if (heading == 3){
      turnLeft(22.5);
    }
    else if (heading == 4){
      turnLeft(45);
    }
    Particle.process();
  }
  else if (direction == 1){
    turnLeft(90);
    turnLeft(90);
    if (heading == 0){
      turnRight(45);
    }
    else if (heading == 1){
      turnRight(22.5);
    }
    else if (heading == 3){
      turnLeft(22.5);
    }
    else if (heading == 4){
      turnLeft(45);
    }
    Particle.process();
  }
  else if (direction == 2){
    turnRight(90);
    if (heading == 0){
      turnRight(45);
    }
    else if (heading == 1){
      turnRight(22.5);
    }
    else if (heading == 3){
      turnLeft(22.5);
    }
    else if (heading == 4){
      turnLeft(45);
    }
    Particle.process();
  }
  else{
    if (heading == 0){
      turnRight(45);
    }
    else if (heading == 1){
      turnRight(22.5);
    }
    else if (heading == 3){
      turnLeft(22.5);
    }
    else if (heading == 4){
      turnLeft(45);
    }
    Particle.process();
  }
  right.setMotorSpeed(70); //start moving forwards
  left.setMotorSpeed(70); //start moving forwards
}

void driveStraight(int speed){
  left.setMotorSpeed(speed);
  right.setMotorSpeed(speed);
  Particle.process();
}

void turnLeft(int heading){

}

void turnRight(int heading){

}

void driveBack(){

}

void waitTime(){
  //unsubscribe from direction events to stay hidden
  Particle.unsubscribe("direction", chooseDir);
  while (1){
    //wait for info requests
    Particle.process();
  }
}
void chooseDir(const char *direction, const char *data){
  if (newPhoto == 1){
    direction = data[0]; //first number is direction
    heading = data[1]; //second number is heading
    newPhoto = 0;
  }
  Particle.process();
}
