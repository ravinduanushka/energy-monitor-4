#include <iostream>   
#include <map>        
#include <string>     
#include "EnergyMonitor.h"
#include "Device.h"
using namespace std;

EnergyMonitor::EnergyMonitor() {

}

void EnergyMonitor::addDevice(int id, std::string name, double power, std::string room) {
    devices[id] = Device(id, name, power, room);
}
void EnergyMonitor::toggleDevice(int id) {
    if (devices.find(id) == devices.end()) {
        cout << "Not found" << endl;
        return;
    }

    devices[id].toggle();
    cout << "Toggled device " << id << endl;
}
void EnergyMonitor::showStatus() {

    if (devices.empty()) {
        std::cout << "No devices available!" << std::endl;
        return;
    }

    std::cout << "\n=== Device Status ===" << std::endl;

    for (auto &pair : devices) {
        int id = pair.first;
        Device &d = pair.second;

        std::cout << "ID: " << id << std::endl;
        std::cout << "Name: " << d.getName() << std::endl;
        std::cout << "Power: " << d.getPower() << " W" << std::endl;
        std::cout << "Room: " << d.getRoom() << std::endl;
        std::cout << "Status: " << (d.isOn() ? "ON" : "OFF") << std::endl;
        std::cout << "----------------------" << std::endl;
    }
}