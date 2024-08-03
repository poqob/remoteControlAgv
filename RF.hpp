#include "HardwareSerial.h"
#include <stdint.h>
#ifndef RF_HPP
#define RF_HPP


#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

struct Signal {
  byte throttle;
  byte pitch;
  byte roll;
  byte yaw;
  byte aux1;
  byte aux2;
};
class Rf {
private:
    int MAX;
    int MIN;
    int speed;
  void RFsetup() {


    ResetData();
    radio.begin();
    radio.setChannel(100);              // Updated channel
    radio.openReadingPipe(1, address);  // Updated address
    radio.setPALevel(RF24_PA_MAX);      // Updated power level
    radio.startListening();

    for (int i=0; i<10; i++) {
      Serial.print(char(this->address[i]));
    }
  }
public:
  RF24 radio;
  byte address[10]={'e','m','i','r','h','a','n','1','0','0'};
public:

Rf(){}
  Rf(int max_step,int min_step) {
    this->radio = RF24(9, 10);
    this->MAX=max_step;
    this->MIN=min_step;
    this->speed=this->MIN;
    RFsetup();
  }
  ~Rf() {}

  Signal data;

  //50-51

  void ResetData() {
    data.throttle = 127;
    data.roll = 127;
    data.pitch = 127;
    data.yaw = 127;
    data.aux1 = 0;
    data.aux2 = 0;
  }


  unsigned long lastRecvTime = 0;

  void recvData() {
    if (radio.available()) {
      radio.read(&data, sizeof(Signal));
      lastRecvTime = millis();
    }
  }

  int convert(byte _val) {
    int val;
    if (val > 127)
      val = map(_val, 127, speed, 0, speed);
    else
      val = map(_val, 0, 127, -speed, 0);
    if (val < -speed)
      val = -speed;
    else if (val > speed)
      val = speed;
    if (abs(val) < 10)
      val = 0;
    return val;
  }

  void printData() {

    Serial.print("SOD: ");
    Serial.print(convert(data.throttle));  // SOL ANALOG DIKEY EKSEN


    Serial.print(" SAD: ");
    Serial.print(convert(data.pitch));  // SAG ANALOG DIKEY EKSEN

    

    Serial.print(" SOA: ");
    Serial.print(data.aux1);  // SAG ANALOG DIKEY EKSEN

    Serial.print(" SAA: ");
    Serial.println(data.aux2);  // SAG ANALOG DIKEY EKSEN
  }
short SAD, SOD, SOA, SAA;

short* RFloop() {
    static short results[4];  // Static array to hold the results
    recvData();
    unsigned long now = millis();
    if (now - lastRecvTime > 1000) {
        ResetData();
    }
    printData();  // Print received data to Serial Monitor
    SAD = convert(data.pitch);
    SOD = convert(data.throttle);
    SOA = data.aux1;
    SAA = data.aux2;
    if(SAA==0)
      this->speed=this->MIN;
    else
      this->speed = this->MAX;
    // Assign values to the static array
    results[0] = SAD;
    results[1] = SOD;
    results[2] = SOA;
    results[3] = SAA;
    return results;  // Return pointer to the static array
}

};


#endif RF_HPP