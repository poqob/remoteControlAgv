#include "Arduino.h"
#include "packet.hpp"
#include "motor.hpp"            // data: {"u": "a0", "v": 255}
#include "warning_circuit.hpp"  // data: {"u": "wn", "v": 1}
#include "emergency_stop.hpp"   // data: {"u": "es", "v": 1}
#include "motor0.hpp"  
#include "ln.hpp"
#include "lineer0.hpp"

String _input;
Packet packet;
WarningC warning;
EmergencyStop emergencyStop;
Ln sagteker;
Ln solteker;
Lineer lineer;

void setup() {
  Serial.begin(115200);
  // Define pins and initialize components
  warning = WarningC(10, 1000);
  emergencyStop = EmergencyStop();
  lineer = Lineer(6,7);
  sagteker =Ln(11,2,3);
  solteker =Ln(10,4,5);

}

void gateway() {
  Serial.println(packet.value);
  if (packet.unit.equals("a0")) {
    solteker.run(packet.value);
  }
else if (packet.unit.equals("a1")) {
  sagteker.run(packet.value);
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
    Serial.println(_input);
    packet.fromJson(_input);
  }
  gateway();
}
