#include <iostream>   
#include <map>        
#include <string>     
#include "EnergyMonitor.h"
#include "Device.h"
UndoStack undoStack;
using namespace std;

EnergyMonitor::EnergyMonitor() {

}

void EnergyMonitor::addDevice(int id, std::string name, double power, std::string room) {
    devices[id] = Device(id, name, power, room);
undoStack.push("ADD " + to_string(id));
}
void EnergyMonitor::toggleDevice(int id) {
    if (devices.find(id) == devices.end()) {
        cout << "Not found" << endl;
        return;
    }
    devices[id].toggle();

    undoStack.push("TOGGLE " + to_string(id));    cout << "Toggled device " << id << endl;
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

void EnergyMonitor::undo() {
    if (undoStack.isEmpty()) {
        cout << "Nothing to undo!" << endl;
        return;
    }

    string action = undoStack.pop();

    string type = action.substr(0, action.find(" "));
    int id = stoi(action.substr(action.find(" ") + 1));

    if (type == "TOGGLE") {
        devices[id].toggle(); 
        cout << "Undo toggle for device " << id << endl;
    }

    else if (type == "ADD") {
        devices.erase(id); 
        cout << "Undo add (removed device " << id << ")" << endl;
    }
}