#include "Arduino.h"
#include "packet.hpp"
#include "motor.hpp"            // data: {"u": "a0", "v": 255}
#include "warning_circuit.hpp"  // data: {"u": "wn", "v": 1}
#include "emergency_stop.hpp"   // data: {"u": "es", "v": 1}
#include "motor0.hpp"
#include "ln.hpp"
#include "lineer0.hpp"
#include "btstest.hpp"


String _input;
Packet packet;
WarningC warning;
EmergencyStop emergencyStop;
Lineer lineer;
Test solteker;
Test sagteker;

void setup() {
  Serial.begin(115200);
  // Define pins and initialize components
  // warning = WarningC(10, 1000);
  emergencyStop = EmergencyStop();
  lineer = Lineer(4, 5);
  sagteker = Test(2, 3, 36, 37);
  //solteker = Ln(10, 4, 5);
  solteker = Test(4, 5, 40, 41);
}

void gateway() {
  if (packet.unit.equals("a0")) {
    //solteker.run(packet.value);
    solteker.run(packet.value);
  } else if (packet.unit.equals("a1")) {
    sagteker.run(packet.value);
  } else if (packet.unit.equals("es")) {
    if (packet.value == 0) {
      emergencyStop.stop();
    } else if (packet.value == 1) {
      emergencyStop.start();
    }
  } else if (packet.unit.equals("wn")) {
    // if (packet.value == 0) {
    //   warning.stop();
    // } else if (packet.value == 1) {
    //   warning.blink();
    // }
  } else if (packet.unit.equals("ln")) {
    lineer.run(packet.value);
  } else {
    // Handle unknown unit
    //Serial.println("Unknown unit");
  }
}

void loop() {
  if (Serial.available()) {
    _input = Serial.readStringUntil('\n');
    // Serial.println(_input);
    packet.fromJson(_input);
  }
  gateway();
}
