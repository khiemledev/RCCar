#include "CRCCar.h"

CRCCar::CRCCar() {
  this->speed = 0;
  this->baseSpeed = 150;
  this->steering = STRAIGHT;
  this->direction = FORWARD;
  this->rotating = -1;

  // Set output pins
  pinMode(MA1, OUTPUT);
  pinMode(MA2, OUTPUT);
  pinMode(MB1, OUTPUT);
  pinMode(MB2, OUTPUT);
}

void CRCCar::accelerate() {
  if (this->rotating == ROT_LEFT) {
    analogWrite(MA1, LOW);
    analogWrite(MA2, 150);
  
    analogWrite(MB1, 150);
    analogWrite(MB2, LOW);
    return;
  } else if (this->rotating == ROT_RIGHT) {
    analogWrite(MA1, 150);
    analogWrite(MA2, LOW);
  
    analogWrite(MB1, LOW);
    analogWrite(MB2, 150);
    return;
  }
  
  if (this->speed == 0) {
    analogWrite(MA1, LOW);
    analogWrite(MA2, LOW);
    analogWrite(MB1, LOW);
    analogWrite(MB2, LOW);
    return;
  }
  
  int leftSpeed = this->speed;
  int rightSpeed = this->speed;
  if (this->steering == LEFT) {
    leftSpeed /= 4;
  } else if (this->steering == RIGHT) {
    rightSpeed /= 4;
  }

  if (this->direction == FORWARD) {
    analogWrite(MA1, LOW);
    analogWrite(MA2, leftSpeed);
    analogWrite(MB1, LOW);
    analogWrite(MB2, rightSpeed);
  } else if (this->direction == BACKWARD) {
    analogWrite(MA1, leftSpeed);
    analogWrite(MA2, LOW);
    analogWrite(MB1, rightSpeed);
    analogWrite(MB2, LOW);
  }
}

void CRCCar::resetSpeed() {
  this->speed = this->baseSpeed;
}

void CRCCar::stop() {
  this->speed = 0;
}

void CRCCar::forward() {
  this->direction = FORWARD;
  this->resetSpeed();
}

void CRCCar::backward() {
  this->direction = BACKWARD;
  this->resetSpeed();
}

void CRCCar::turnLeft() {
  this->steering = LEFT;
}

void CRCCar::turnRight() {
  this->steering = RIGHT;
}

void CRCCar::rotateLeft() {
  this->rotating = ROT_LEFT;
}

void CRCCar::rotateRight() {
  this->rotating = ROT_RIGHT;
}

void CRCCar::stopRotating() {
  this->rotating = -1;
}

void CRCCar::goStraight() {
  this->steering = STRAIGHT;
}
