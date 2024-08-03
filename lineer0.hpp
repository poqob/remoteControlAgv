#include "HardwareSerial.h"
#include <stdint.h>
#ifndef LINEER0_HPP
#define LINEER0_HPP

#include <Arduino.h>

class Lineer {
private:
  int RPWM;
  int LPWM;
  int r_en;
  int l_en;
  int MZ;
  bool mzListener = false;  // Başlangıçta false
   unsigned long startMillis; // Başlangıç zamanını saklamak için
   unsigned long interval = 2000; // 2 saniye
public:
  Lineer() {}
  Lineer(int IN1, int IN2, int r_en, int l_en, int MZ) {
    this->RPWM = IN1;
    this->LPWM = IN2;
    this->r_en = r_en;
    this->l_en = l_en;
    this->MZ = MZ;
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(r_en, OUTPUT);
    pinMode(l_en, OUTPUT);
    pinMode(MZ, INPUT);
  }

  ~Lineer() {}

  void run(int direction) {
     unsigned long currentMillis = millis(); // Geçerli zamanı al
    if (direction == 1) {  // İleri
     startMillis = currentMillis; // Başlangıç zamanını ayarla
       if (currentMillis - startMillis < interval) {
        analogWrite(RPWM, 255);
        analogWrite(LPWM, 0);
        digitalWrite(r_en, HIGH);
        digitalWrite(l_en, HIGH);
      } 
      mzListener = true;
    } else if (direction == 0) {  // Geri
      analogWrite(RPWM, 0);
      analogWrite(LPWM, 255);
      digitalWrite(r_en, HIGH);
      digitalWrite(l_en, HIGH);

      // Eğer MZ sensöründen gelen değer sıfırsa ve mzListener true ise motorları durdur
      if (digitalRead(this->MZ) == 0 ) {
        analogWrite(RPWM, 0);
        analogWrite(LPWM, 0);
        digitalWrite(r_en, LOW);
        digitalWrite(l_en, LOW);
        
        mzListener = false;  // Sensör değeri sıfır olduğunda dinleyiciyi devre dışı bırak
      }
    } else {
      // Belirtilen yön dışında motorları kapatma kodu
      analogWrite(RPWM, 0);
      analogWrite(LPWM, 0);
      mzListener = false;  // Dinleyiciyi devre dışı bırak
    }

    // Serial.print("lineer_l: ");
    // Serial.print(digitalRead(this->LPWM));

    // Serial.print(" lineer_r: ");
    // Serial.print(digitalRead(this->RPWM));

    // Serial.print(" mz: ");
    // Serial.println(digitalRead(this->MZ));

    // Serial.print("start: ");
    // Serial.print(startMillis);

    // Serial.print("current: ");
    // Serial.println(currentMillis);
  }
};

#endif // LINEER0_HPP
