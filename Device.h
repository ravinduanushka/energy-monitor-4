#ifndef DEVICE_H
#define DEVICE_H

#include <string>

class Device {

private:
    int id;
    std::string name;
    double powerRating;
    std::string room;
    bool status;

public:
    Device();

    Device(int id,
           std::string name,
           double power,
           std::string room);

    void turnOn();
    void turnOff();
    void toggle();

    int getId() const;
    bool isOn() const;
    double getPower() const;

    std::string getName() const;
    std::string getRoom() const;
};

#endif