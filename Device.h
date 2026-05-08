#pragma once
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
    Device(int id, std::string name, double powerRating, std::string room);

    void toggle();
    bool isOn() const;
    std::string getName() const;
    double getPower() const;
    std::string getRoom() const;
    int getId() const;
};