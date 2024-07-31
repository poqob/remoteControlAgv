#ifndef PACKET_HPP
#define PACKET_HPP

#include <Arduino.h>

class Packet {
public:
    String unit;
    int value;

    Packet() : unit(""), value(0) {}

    Packet(String unit, int value) : unit(unit), value(value) {}

    void fromJson(const String& jsonString) {
        // Basit JSON ayrıştırma
        int unitStart = jsonString.indexOf("\"u\": \"") + 6;
        int unitEnd = jsonString.indexOf("\"", unitStart);
        unit = jsonString.substring(unitStart, unitEnd);

        int valueStart = jsonString.indexOf("\"v\": ", unitEnd) + 4;
        int valueEnd = jsonString.indexOf("}", valueStart);
        value = jsonString.substring(valueStart, valueEnd).toInt();
    }

    String toJson() const {
        // Basit JSON formatı oluşturma
        String jsonString = "{";
        jsonString += "\"u\": \"" + unit + "\", ";
        jsonString += "\"v\": " + String(value);
        jsonString += "}";
        return jsonString;
    }
};

#endif
