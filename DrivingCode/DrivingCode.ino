#define trigPin 13
#define echoPin 12

#include <Motor.h>
//Driving Code

#include <Arduino.h>

Motor right(2, 3);
Motor left(4, 5);
int photoRes = A0; //photoresistor pin
int direc = 0; // NSEW
int heading = 2; //straight ahead
int bit1 = 11; //first bit of info from pi
int bit2 = 12; //second bit of info from pi
int bit3 = 13; //third bit of info from pi


void setup(){
   pinMode(photoRes, INPUT); //attach photoresistor
<<<<<<< HEAD
   pinMode(bit1, INPUT); //attach photoresistor
   pinMode(bit2, INPUT); //attach photoresistor
   pinMode(bit3, INPUT); //attach photoresistor 

=======
   pinMode(trigPin, OUTPUT); //trig, sonic pin
   pinMode(echoPin, INPUT); //echo, sonic pin
   Serial.begin(9600);              //Starting serial communication
>>>>>>> origin/master
   gameInit(); // do initial check of surroundings
}


void loop(){
   
   if (Serial.available() > 0) {
   int incoming = Serial.read();
   Serial.print(“character recieved: “)
   Serial.print(incoming, DEC);
   }
   
   long duration, distance;
   digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
   
  //check photoResistor value to determine if dark place has been reached

   
  int lightLevel = analogRead(photoRes);
  if (lightLevel < 300){
    left.stopMotor();
    right.stopMotor();
    waitTime(); //enter wait stage of game

  }
<<<<<<< HEAD
  else if (range sensor indicates being near a wall slow down){
=======
  if (distance < 10.0){
>>>>>>> origin/master
    int speedL = left.getMotorSpeed();
    int speedR = right.getMotorSpeed();
    left.setMotorSpeed(speedL/2);
    right.setMotorSpeed(speedR/2);
  }
  else { //if none of the other things occur
    chooseDir();
    driveStraight(70);
  }
}

void gameInit(){

  //takePhoto
  delay(100);

  chooseDir();

  right.setMotorSpeed(70); //start moving forwards
  left.setMotorSpeed(70); //start moving forwards
  left.startMotor();
  right.startMotor();

}

void driveStraight(int spd){
  left.setMotorSpeed(spd);
  right.setMotorSpeed(spd);
  left.startMotor();
  right.startMotor();
  delay(100);

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

  }
}
int chooseDir(){

  //determine best heading based on photos
  direc = digitalRead(bit3)*2^2 + digitalRead(bit2)*2 + digitalRead(bit1);
  if (direc == 0){
      turnRight(45);
    }
  else if (direc == 1){
    turnRight(22.5);
  }
  else if (direc == 3){
    turnLeft(22.5);
  }
  else if (direc == 4){
    turnLeft(45);

}
