#include "Device.h"

Device::Device() : id(0), name(""), powerRating(0.0), room(""), status(false) {}

Device::Device(int id, std::string name, double powerRating, std::string room)
    : id(id), name(name), powerRating(powerRating), room(room), status(false) {}

void Device::toggle() {
    status = !status;
}

bool Device::isOn() const {
    return status;
}

std::string Device::getName() const {
    return name;
}

double Device::getPower() const {
    return powerRating;
}

std::string Device::getRoom() const {
    return room;
}

int Device::getId() const {
    return id;
}
