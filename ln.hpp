#include <stdint.h>
#ifndef LN_hpp
#define LN_HPP

#include <Arduino.h>

class Ln {
private:
  int ENA;
  int IN1;
  int IN2;


public:
  Ln(){}
  Ln(int ENA, int IN1, int IN2) {
    this->ENA = ENA;
    this->IN1 = IN1;
    this->IN2 = IN2;

    pinMode(ENA, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);

  }

  ~Ln() {}

  void run(int power) {
    Serial.println(power);
    if(power>0){
      analogWrite(ENA,power);
      digitalWrite(IN1,HIGH);
      digitalWrite(IN2,LOW);
    }
  else if (power < 0) {
    int inversepower = power * -1; 
    analogWrite(ENA, inversepower);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
}

 
  }
};

#endif LN