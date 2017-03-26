#include <Motor.h>

//Driving Code

#include <Arduino.h>

Motor right(2, 3);
Motor left(4, 5);
int photoRes = A0; //photoresistor pin
int newPhoto = 1; //1 if want new photo, 0 if not ready for new photo
int direc = 0; // NSEW
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

  turnLeft(90);
  //facing direction 2
  //takePhoto
  delay(100);

  turnLeft(90);
  //facing direction 3
  //takePhoto
  delay(100);

  //determine best heading based on photos
  //direction
  if (direc == 0){
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

  }
  else if (direc == 1){
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
  else if (direc == 2){
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

void driveStraight(int spd){
  left.setMotorSpeed(spd);
  right.setMotorSpeed(spd);
  left.startMotor();
  right.startMotor();

}

void turnLeft(int deg){
  left.setMotorSpeed(-30);
  right.setMotorSpeed(30);
  left.startMotor();
  right.startMotor();
  if (deg == 22.5){
    delay(50);
  }
  else if (deg == 45){
    delay(100);
  }
  else{
    delay(200);
  }
}

void turnRight(int deg){
  left.setMotorSpeed(30);
  right.setMotorSpeed(-30);
  left.startMotor();
  right.startMotor();
  if (deg == 22.5){
    delay(50);
  }
  else if (deg == 45){
    delay(100);
  }
  else{
    delay(200);
  }
}

void driveBack(){
  left.setMotorSpeed(-75);
  right.setMotorSpeed(-75);
  left.startMotor();
  right.startMotor();
  delay(500);
}

void waitTime(){


  while (1){
    //wait for info requests
    Particle.process();
  }
}
void chooseDir(const char *direc, const char *data){
  if (newPhoto == 1){
    direc = data[0]; //first number is direction
    heading = data[1]; //second number is heading
    newPhoto = 0;
  }

}
