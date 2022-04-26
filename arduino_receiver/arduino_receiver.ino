#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <string.h>

RF24 radio(7, 8); // 4, 5 if ESP32
const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.startListening();
  Serial.println("Setup done!");
}

void loop() {
  if (radio.available()) {
    char text[32] = {0};
    radio.read(&text, sizeof(text));

    // Get x, y in text delemiter by a space
    char* pch = strtok(text, " ");
    byte i = 0;
    float x;
    float y;
    while (pch != NULL) {
      if (i == 0) {
        x = atof(pch);
      } else {
        y = atof(pch);
      }
      pch = strtok(NULL, " ");
      i++;
    }
    Serial.print(x); Serial.print(" "); Serial.println(y);
    // Serial.println(text);
    
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
  }
}
