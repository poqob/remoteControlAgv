#include "HardwareSerial.h"
#include <stdint.h>
#ifndef MOTOR_HPP
#define MOTOR_HPP

#include <Arduino.h>

class Motor {
private:
  // define pins
  uint8_t _in_3;
  uint8_t _in4;

public:
  Motor(uint8_t in_3, uint8_t in4) {
    // pin setup
    _in_3 = in_3;
    _in4 = in4;
    pinMode(_in_3, OUTPUT);
  }
  Motor() {}



  ~Motor() {}
  void run(uint8_t _power) {
    analogWrite(_in_3, _power);
    }
};

#endif MOTOR_HPP