#include "Device.h"
using namespace std;

Device::Device() {
    id = 0;
    powerRating = 0;
    status = false;
    room = "";
}

Device::Device(int id, std::string name, double power, std::string room) {
    this->id = id;
    this->name = name;
    this->powerRating = power;
    this->room = room;
    status = false;
}
int Device::getId() const {
    return id;
}

std::string Device::getRoom() const {
    return room;
}

std::string Device::getName() const {
    return name;
}

double Device::getPower() const {
    return powerRating;
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

void Device::toggle() {
    status = !status;
}