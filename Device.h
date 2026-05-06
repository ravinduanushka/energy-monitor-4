#pragma once
#include <string>

class Device {
public:
    std::string id;
    std::string name;
    double powerRating; // In watts
    bool status; // true = ON, false = OFF

    Device();
    Device(std::string id, std::string name, double powerRating);

    void turnOn();
    void turnOff();
    double getCurrentUsage() const;
};