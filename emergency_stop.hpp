#ifndef EMERGENCY_STOP_HPP
#define EMERGENCY_STOP_HPP
#include <stdint.h>
#include <Arduino.h>

class EmergencyStop {
  private:
  // define pins


  public:
  EmergencyStop(){
// pin setup
  }
  ~EmergencyStop(){}

  void stop(){
Serial.println("emergency stop");
  }

  void start(){
Serial.println("emergency start");

  }

};

#endif EMERGENCY_STOP_HPP
