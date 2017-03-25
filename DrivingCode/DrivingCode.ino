//Driving Code

#include <Arduino.h>

left Motor(1, 2);
right Motor(3,4);
int photoRes = A0; //photoresistor pin

void setup(){
   pinMode(photoRes, INPUT);
   gameInit();

}


void loop(){
  //check photoResistor value to determine if dark place has been reached
  lightLevel = analogRead(photoRes);
  if (lightLevel < 300){
    left.stopMotor();
    right.stopMotor();
    waitTime(); //enter wait stage of game
  }
}

void gameInit(){
  //facing direction 0
  //takePhoto
  turnLeft(90);
  //facing direction 1
  //takePhoto
  turnLeft(90);
  //facing direction 2
  //takePhoto
  turnLeft(90);
  //facing direction 3
  //takePhoto
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
  }
}

void driveStraight(int speed){

}

void turnLeft(int heading){

}

void turnRight(int heading){

}

void waitTime(){
  while (1){
    
  }
}
