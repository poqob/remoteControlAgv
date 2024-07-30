#include <stdint.h>
#ifndef LINEER0_HPP
#define LINEER0_HPP

#include <Arduino.h>

class Lineer {
private:
  int IN1;
  int IN2;

public:
  Lineer() {}
  Lineer(int IN1, int IN2) {
    this->IN1 = IN1;
    this->IN2 = IN2;
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
  }

  ~Lineer() {}

  void run(int direction) {
    if (direction == 0) { // Dur
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
    } else if (direction == 1) { // İleri
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
    } else if (direction == 2) { // Geri
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
    }
  }
};

#endif LINEER_HPP