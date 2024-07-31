#include <stdint.h>
#ifndef WARNING_HPP
#define WARNING_HPP

#include <Arduino.h>

//
class WarningC {
private:
  // define pins
  uint8_t testpin;
  unsigned long previousMillis;  // zaman kaydını tutacak değişken
  long interval;                 // LED'in yanıp sönme aralığı

public:
  WarningC(uint8_t test_pin, long blink_interval)
    : testpin(test_pin), interval(blink_interval), previousMillis(0) {
    // pin setup
    pinMode(testpin, OUTPUT);
  }

  ~WarningC() {}
  WarningC() {}

  void stop() {
    digitalWrite(testpin, LOW);
  }

  void start() {
    digitalWrite(testpin, HIGH);
  }

  void blink() {
    unsigned long currentMillis = millis();  // şu anki zamanı al

    if (currentMillis - previousMillis >= interval) {
      // zaman aralığı geçtiyse LED durumunu değiştir
      previousMillis = currentMillis;

      // LED'in mevcut durumunu oku ve değiştir
      int state = digitalRead(testpin);
      digitalWrite(testpin, !state);  // LED durumunu tersine çevir
    }
  }
};

#endif  // WARNING_HPP
