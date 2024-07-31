#include <stdint.h>
#ifndef MOTOR_HPP
#define MOTOR_HPP

#include <Arduino.h>

class BTS7960 {
private:
  int MOTOR1_PIN1;
  int MOTOR1_PIN2;
  int MOTOR2_PIN1;
  int MOTOR2_PIN2;
  int r_en;
  int l_en;
  int r_en1;
  int l_en1;
  
  int weights[8] = {-20, -10, -5, -1, 1, 5, 10, 20};
  int sensorReading[8] = {0}; 
  float activeSensor = 0; 
  float totalSensor = 0;
  float avgSensor = 0; // Average sensor reading

  float Kp = 3;   // Max deviation = 10 - 0 = 10 ||  255/10 = 25
  float Ki = 0.00015;
  float Kd = 2;

  float error = 0;
  float previousError = 0;
  float totalError = 0;

  float power = 0;

  int PWM_Left;
  int PWM_Right;

  int MAX_SPEED = 100;

  String data;  // Store sensor data string
  bool newPackage = false;  // Flag to check if new package is available                                                                     

public:
  BTS7960(int motor1_pin1, int motor1_pin2, int motor2_pin1, int motor2_pin2,
          int r_en_pin, int l_en_pin, int r_en1_pin, int l_en1_pin)
    : MOTOR1_PIN1(motor1_pin1), MOTOR1_PIN2(motor1_pin2), MOTOR2_PIN1(motor2_pin1),
      MOTOR2_PIN2(motor2_pin2), r_en(r_en_pin), l_en(l_en_pin), r_en1(r_en1_pin), l_en1(l_en1_pin) {
    pinMode(MOTOR1_PIN1, OUTPUT);
    pinMode(MOTOR1_PIN2, OUTPUT);
    pinMode(MOTOR2_PIN1, OUTPUT);
    pinMode(MOTOR2_PIN2, OUTPUT);
    pinMode(r_en, OUTPUT);
    pinMode(l_en, OUTPUT);
    pinMode(r_en1, OUTPUT);
    pinMode(l_en1, OUTPUT);
  }

  void service() {  
    if (newPackage) {
      // Process incoming data
      digitalWrite(r_en, HIGH);
      digitalWrite(l_en, HIGH);
      digitalWrite(r_en1, HIGH);
      digitalWrite(l_en1, HIGH);
      
      PID_program();
      go(PWM_Left, PWM_Right);
      
      Serial.println(data); // DELETE PRINT
      newPackage = !newPackage;
    }
  }

private:
  void PID_program() { 
    readSensor();

    previousError = error; 
    error = avgSensor; 
    totalError += error;

    power = (Kp * error) + (Kd * (error - previousError));
    
    if (power > MAX_SPEED) { 
      power = MAX_SPEED; 
    }
    if (power < -MAX_SPEED) { 
      power = -MAX_SPEED; 
    }

    if (power < 0) { 
      PWM_Right = MAX_SPEED; 
      PWM_Left = MAX_SPEED - abs(int(power));
    } else { 
      PWM_Right = MAX_SPEED - int(power);
      PWM_Left = MAX_SPEED; 
    }
  }

  void go(int speedLeft, int speedRight) {
    if (speedLeft > 0) {
      analogWrite(MOTOR1_PIN1, speedLeft);
      analogWrite(MOTOR1_PIN2, 0);
    } else {
      analogWrite(MOTOR1_PIN1, 0);
      analogWrite(MOTOR1_PIN2, -speedLeft);
    }
    
    if (speedRight > 0) {
      analogWrite(MOTOR2_PIN1, speedRight);
      analogWrite(MOTOR2_PIN2, 0);
    } else {
      analogWrite(MOTOR2_PIN1, 0);
      analogWrite(MOTOR2_PIN2, -speedRight);
    }
  }

  void readSensor() {
    // Convert string data to integer array
    for (int i = 0; i < 8; i++) {
      sensorReading[i] = (data.charAt(i) == '1') ? 1 : 0;
    }

    for (int i = 0; i < 8; i++) {
      if (sensorReading[i] == 1) {
        activeSensor += 1;
      }
      totalSensor += sensorReading[i] * weights[i];
    }  

    avgSensor = (activeSensor > 0) ? (totalSensor / activeSensor) : 0;

    activeSensor = 0; 
    totalSensor = 0;
    for (int i = 0; i < 8; i++) {
      sensorReading[i] = 0;
    }
  }
};

#endif MOTOR_HPP