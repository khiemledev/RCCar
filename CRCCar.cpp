#include "CRCCar.h"

CRCCar::CRCCar() {
  this->baseSpeed = 100;
  this->steering = 0.0;
  this->verlocity = 0.0;

  // Set output pins
  pinMode(MA1, OUTPUT);
  pinMode(MA2, OUTPUT);
  pinMode(MB1, OUTPUT);
  pinMode(MB2, OUTPUT);
}

void CRCCar::accelerate() {
  int leftSpeed = this->baseSpeed + (255 - this->baseSpeed) * abs(this->verlocity);
  int rightSpeed = this->baseSpeed + (255 - this->baseSpeed) * abs(this->verlocity);

  if (this->steering < 0) {
    leftSpeed -= (255 - this->baseSpeed) * abs(this->steering);
  } else {
    rightSpeed -= (255 - this->baseSpeed) * abs(this->steering);
  }

  if (this->verlocity < 0) {
    // Move forward
    analogWrite(MA1, LOW);
    analogWrite(MA2, leftSpeed);
    analogWrite(MB1, LOW);
    analogWrite(MB2, rightSpeed);
  } else {
    // Move backward
    analogWrite(MA1, leftSpeed);
    analogWrite(MA2, LOW);
    analogWrite(MB1, rightSpeed);
    analogWrite(MB2, LOW);
  }
}

void CRCCar::setSteering(float value) {
  this->steering = min((float) 1.0, max((float) -1.0, value));
}

void CRCCar::setVerlocity(float value) {
  this->verlocity = min((float) 1.0, max((float) -1.0, value));
}
