#ifndef CRCCAR_H // include guard
#define CRCCAR_H

#include <Arduino.h>
#include <analogWrite.h>
#include <math.h>

// Left motor
#define MA1 13
#define MA2 12
// Right motor
#define MB1 14
#define MB2 27

class CRCCar {
  public:
    int baseSpeed;
    float verlocity;
    float steering;

    CRCCar();

    void accelerate();
    void setSteering(float);
    void setVerlocity(float);
};

#endif /* CRCCAR_H */
