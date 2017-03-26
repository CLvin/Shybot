//Driving Code

#include <Arduino.h>

left Motor(1, 2);
right Motor(3,4);
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
  //unsubscribe from direction events to stay hidden
  Particle.unsubscribe("direction", chooseDir);
  while (1){
    //wait for info requests
  }
}
void chooseDir(const char *direction, const char *data){
  if (newPhoto == 1){
    direction = data[0]; //first number is direction
    heading = data[1]; //second number is heading
  }
}
