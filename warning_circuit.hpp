#include <stdint.h>

#ifndef DISTANCE_SERVICE_HPP
#define DISTANCE_SERVICE_HPP
#define TRIGGER_PIN 8
#define ECHO_PIN 9
#include "Arduino.h"

class DistanceService {
private:

  unsigned long previousMillis = 0;
   long interval = 500;



public:
  DistanceService() {}

    void setup() {
    pinMode(TRIGGER_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    digitalWrite(TRIGGER_PIN, LOW);
  }
  ~DistanceService() {}

  void service() {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;

      // Mesafe ölçümünü başlat
      digitalWrite(TRIGGER_PIN, HIGH);
      delayMicroseconds(10);  // Sensörün tetiklenmesi için kısa bir gecikme gereklidir
      digitalWrite(TRIGGER_PIN, LOW);

      // ECHO pininden yanıtı oku
      unsigned long duration = pulseIn(ECHO_PIN, HIGH);

      // Mesafeyi hesapla (ses hızı 34300 cm/s)
      float distance = (duration / 2.0) * 0.0343;  // cm cinsinden mesafe

      if (distance > 0 && distance < 400) {  // Geçerli mesafe aralığı
        Serial.print("Mesafe: ");
        Serial.print(distance);
        Serial.println(" cm");
      } else {
        Serial.println("Mesafe ölçülemiyor.");
      }
    }
  }
};

#endif  // DISTANCE_SERVICE_HPP
