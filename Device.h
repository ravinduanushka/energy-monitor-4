#ifndef DEVICE_H
#define DEVICE_H

#include <string>
using namespace std;

class Device {
private:
    int id;
    string name;
    double powerRating;
    double power;
    string room;  
    bool status;

public:
    Device();
    Device(int id, std::string name, double power, std::string room);

    void turnOn();
    void turnOff();
    void toggle();
    
    string getId() const;
    bool isOn() const;
    double getPower() const;

    string getName()const;
    string getRoom() const;  
};

#endif