#include <stdint.h>
#ifndef LINEER_HPP
#define LINEER_HPP

#include <Arduino.h>

class Motor {
private:
  uint8_t _in1;
  uint8_t _in2;

public:
  Motor(uint8_t in1, uint8_t in2) {
    _in1 = in1;
    _in2 = in2;
    pinMode(_in1, OUTPUT);
    pinMode(_in2, OUTPUT);
  }

  ~Motor() {}

  void run(uint8_t direction) {
    if (direction == 0) { // Dur
      digitalWrite(_in1, LOW);
      digitalWrite(_in2, LOW);
    } else if (direction == 1) { // İleri
      digitalWrite(_in1, HIGH);
      digitalWrite(_in2, LOW);
    } else if (direction == 2) { // Geri
      digitalWrite(_in1, LOW);
      digitalWrite(_in2, HIGH);
    }
  }
};

#endif LINEER_HPP