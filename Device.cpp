#include "Device.h"

Device::Device() : id(""), name(""), powerRating(0.0), status(false) {}

Device::Device(std::string id, std::string name, double powerRating)
    : id(id), name(name), powerRating(powerRating), status(false) {}

void Device::turnOn() {
    status = true;
}

void Device::turnOff() {
    status = false;
}

double Device::getCurrentUsage() const {
    if (status) {
        return powerRating;
    }
    return 0.0;
}
