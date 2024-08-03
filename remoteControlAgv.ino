#include "Arduino.h"
#include "packet.hpp"
#include "motor.hpp"            // data: {"u": "a0", "v": 255}
#include "warning_circuit.hpp"  // data: {"u": "wn", "v": 1}
#include "emergency_stop.hpp"   // data: {"u": "es", "v": 1}
#include "motor0.hpp"
#include "lineer0.hpp"
#include "btstest.hpp"
#include "RF.hpp"

Rf rf;
String _input;
Packet packet;
// DistanceService distance;
EmergencyStop emergencyStop;
Lineer lineer;
BtsDriver solteker;
BtsDriver sagteker;

void setup() {
  Serial.begin(250000);  // Serial.begin(115200);
  // Define pins and initialize components
  // distance = DistanceService();// trig echo
  // distance.setup();
  emergencyStop = EmergencyStop();
  lineer = Lineer(7, 6, 32, 33, 31);
  sagteker = BtsDriver(3, 2, 36, 37,127);
  solteker = BtsDriver(4, 5, 40, 41,127);
  rf = Rf(127,75);
}

unsigned long previousMillis = 0;  // Kaydedilen son zamanı saklamak için değişken
const unsigned long interval = 1000;  // Aralık süresi (1 saniye = 1000 milisaniye)

void loop() {
  // Diğer işlemler
  short* results = rf.RFloop(); 
  short SAD = results[0];
  short SOD = results[1];
  short SOA = results[2];
  short SAA = results[3];
  
  // İşlemler
solteker.run(SOD);
  sagteker.run(SAD);
  lineer.run(SOA);

 
}
