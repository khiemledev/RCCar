#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
// Setup RF24
RF24 radio(4, 5);
const byte address[6] = "00001";

#define DEVICE_NAME         "RCCar v0.4"
#define SERVICE_UUID        "f645c32d-d949-4241-991e-b422029c4418"
#define CHARACTERISTIC_UUID "dce9aefb-a236-4edb-88e2-a4ecee57b469"


class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string value = pCharacteristic->getValue();

      if (value.length() > 0) {
          char d[50] = {0};
        for (int i = 0; i < value.length(); i++) {
          d[i] = value[i];
        }
        radio.write(&d, sizeof(d));
        Serial.println(d);
      }
    }
};

void setup() {
  Serial.begin(115200);

  // Setup BLE Reading
  BLEDevice::init(DEVICE_NAME);
  BLEServer *pServer = BLEDevice::createServer();

  BLEService *pService = pServer->createService(SERVICE_UUID);

  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pCharacteristic->setCallbacks(new MyCallbacks());

  pCharacteristic->setValue("I'm ESP32 Transmitor");
  pService->start();

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();

  // Setup RF24
  radio.setPALevel(RF24_PA_MAX);
  radio.begin();
  radio.openWritingPipe(address);
  radio.stopListening();

  Serial.println("Setup done! Now you can connect using BLE.");
}

void loop() {
  delay(2000);
}
