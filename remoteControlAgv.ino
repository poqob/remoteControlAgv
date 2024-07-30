#include "Arduino.h"
#include "packet.hpp"
#include "motor.hpp"            // data: {"u": "a0", "v": 255}
#include "warning_circuit.hpp"  // data: {"u": "wn", "v": 1}
#include "emergency_stop.hpp"   // data: {"u": "es", "v": 1}

String _input;
Packet packet;
Motor motor0;
Motor motor1;
Motor lineer;
WarningC warning;
EmergencyStop emergencyStop;

void setup() {
  Serial.begin(115200);
  // Define pins and initialize components
  warning = WarningC(10, 1000);
  emergencyStop = EmergencyStop();
  motor0 = Motor(9, 90);
  motor1 = Motor(10, 90);
  lineer= Motor(11,-1);
}

void gateway() {

  if (packet.unit.equals("a1")) {
    motor1.run(packet.value);
  }
else if (packet.unit.equals("a0")) {
  motor0.run(packet.value);
}
else if (packet.unit.equals("es")) {
  if (packet.value == 0) {
    emergencyStop.stop();
  } else if (packet.value == 1) {
    emergencyStop.start();
  }
}
else if (packet.unit.equals("wn")) {
  if (packet.value == 0) {
    warning.stop();
  } else if (packet.value == 1) {
    warning.blink();
  }
}
else if (packet.unit.equals("ln")){
  lineer.run(packet.value);
}
else {
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
