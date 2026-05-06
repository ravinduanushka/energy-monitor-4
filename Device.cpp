#include "Device.h"

Device::Device() {
    id = 0;
    power = 0;
    status = false;
    room = "";
}

Device::Device(int id, std::string name, double power, std::string room) {
    this->id = id;
    this->name = name;
    this->powerRating = powerRating;
    this->room = room;
    status = false;
}

std::string Device::getRoom() const {
    return room;
}

std::string Device::getName() const {
    return name;
}

double Device::getPower() const {
    return power;
}

bool Device::isOn() const {
    return status;
}

void Device::turnOn() {
    status = true;
}

void Device::turnOff() {
    status = false;
}