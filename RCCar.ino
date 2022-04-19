#include "BluetoothSerial.h"
#include "CRCCar.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// Global variables
BluetoothSerial SerialBT;
CRCCar car = CRCCar();

void setup() {
  Serial.begin(115200);
  SerialBT.begin("RC Car v0.3");
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  if (SerialBT.available()) {
    int control = SerialBT.read() - '0'; // Cast string to int
    Serial.println(control);
    switch (control) {
      case STOP:
        car.stop();
        break;
      case FORWARD:
        car.forward();
        break;
      case BACKWARD:
        car.backward();
        break;
      case LEFT:
        car.turnLeft();
        break;
      case RIGHT:
        car.turnRight();
        break;
      case STRAIGHT:
        car.goStraight();
        break;
      case ROT_LEFT:
        car.rotateLeft();
        break;
      case ROT_RIGHT:
        car.rotateRight();
        break;
      case 29:
        car.stopRotating();
        break;
      case 30:
        car.stopRotating();
        break;
    }
  }
  car.accelerate();
  delay(20);
}
