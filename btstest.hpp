#include <stdint.h>
#ifndef BTSTEST_HPP
#define BTSTEST_HPP

#include <Arduino.h>

class Test {
private:
  int MOTOR1_PIN1;
  int MOTOR1_PIN2;
  int r_en;
  int l_en;
public:
  Test() {}
  Test(int MOTOR1_PIN1, int MOTOR1_PIN2, int r_en, int l_en) {
    this->MOTOR1_PIN1 = MOTOR1_PIN1;
    this->MOTOR1_PIN2 = MOTOR1_PIN2;
    this->r_en = r_en;
    this->l_en = l_en;

    pinMode(MOTOR1_PIN1, OUTPUT);
    pinMode(MOTOR1_PIN2, OUTPUT);
    pinMode(r_en, OUTPUT);
    pinMode(l_en, OUTPUT);
  }

  ~Test() {}


  void run(int power) {
    if(power<10)
      return;
    if (power > 0) {
      analogWrite(MOTOR1_PIN1, power);
      analogWrite(MOTOR1_PIN2, 0);
      digitalWrite(r_en, HIGH);
      digitalWrite(l_en, HIGH);
    } else if (power < 0) {
      int inversepower = power * -1;
      analogWrite(MOTOR1_PIN2, inversepower);
      analogWrite(MOTOR1_PIN1, 0);
      digitalWrite(r_en, HIGH);
      digitalWrite(l_en, HIGH);
    } else {
      analogWrite(MOTOR1_PIN1, 0);
      analogWrite(MOTOR1_PIN2, 0);
      
      digitalWrite(r_en, LOW);
      digitalWrite(l_en, LOW);
    }
    
    // Seri monitörde motor gücünü ve MOTOR1_PIN1 PWM değerini yazdır
    Serial.print("Motor Gücü: ");
    Serial.print(power);
    Serial.print(", MOTOR1_PIN1 PWM Değeri: ");
    Serial.print(pulseIn(MOTOR1_PIN1,HIGH));
     Serial.print(", MOTOR1_PIN2 PWM Değeri: ");
    Serial.println(pulseIn(MOTOR1_PIN2,HIGH));
  }
};
#endif BTSTEST_HPP