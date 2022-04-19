#ifndef CRCCAR_H // include guard
#define CRCCAR_H

#include <Arduino.h>
#include <analogWrite.h>

// Left motor
#define MA1 13
#define MA2 12
// Right motor
#define MB1 14
#define MB2 27

#define STOP 1
#define FORWARD 2
#define BACKWARD 3
#define LEFT 4
#define RIGHT 5
#define STRAIGHT 6
#define ROT_LEFT 7
#define ROT_RIGHT 8

class CRCCar {
  public:
    int speed;
    int baseSpeed;
    int steering;
    int direction;
    int rotating;

    CRCCar();

    void accelerate();

    void resetSpeed();

    void stop();

    void forward();

    void backward();

    void turnLeft();

    void turnRight();

    void rotateLeft();
    
    void rotateRight();

    void stopRotating();

    void goStraight();
};

#endif /* CRCCAR_H */
