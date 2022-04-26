#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <string.h>
#include "CRCCar.h"

CRCCar car = CRCCar();

RF24 radio(4, 5); // 4, 5 if ESP32
const byte address[6] = "00001";

void setup() {
  Serial.begin(115200);

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.startListening();

  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  if (radio.available()) {
    char text[32] = {0};
    radio.read(&text, sizeof(text));

    float x = 0.0;
    float y = 0.0;

    char* pch = strtok(text, " ");
    byte i = 0;
    while (pch != NULL) {
      if (i == 0)
        x = atof(pch);
      else
        y = atof(pch);
      pch = strtok(NULL, " ");
    }
    Serial.print(x); Serial.print(" __ "); Serial.println(y);
    car.setVerlocity(x);
    car.setSteering(y);
  }
  car.accelerate();
  delay(20);
}
