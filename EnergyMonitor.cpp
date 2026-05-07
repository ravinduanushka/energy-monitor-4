#include <iostream>   
#include <map>        
#include <string>     
#include "EnergyMonitor.h"
#include "Device.h"
#include <fstream>
#include <sstream>
using namespace std;

EnergyMonitor::EnergyMonitor() 
    : alertHistory(5)  // keep last 5 alerts
    {

}

void EnergyMonitor::addDevice(int id, std::string name, double power, std::string room) {
    devices[id] = Device(id, name, power, room);
undoStack.push("ADD " + to_string(id));
    alertHistory.addAlert("Device added: " + to_string(id));
    if (power > powerThreshold) {
        alertHistory.addAlert(" HIGH POWER ALERT: Device " + to_string(id) +
                              " exceeds limit (" + to_string(power) + "W)");
        cout << "ALERT: Power limit exceeded!\n";
}
}

void EnergyMonitor::toggleDevice(int id) {
    if (devices.find(id) == devices.end()) {
        cout << "Not found" << endl;
        return;
    }
    devices[id].toggle();

    undoStack.push("TOGGLE " + to_string(id));    cout << "Toggled device " << id << endl;
        alertHistory.addAlert("Toggled device: " + to_string(id));
        //   cout << "Toggled device " << id << endl;

   double p = devices[id].getPower();

    if (p > powerThreshold && devices[id].isOn()) {
        alertHistory.addAlert("HIGH POWER ALERT: Device " + to_string(id));
        cout << "WARNING: High power device ON!\n";
    }

    calculateConsumption();
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

void EnergyMonitor::loadFromFile() {
    ifstream file("devices.txt");

    if (!file.is_open()) return;

    string line;

    while (getline(file, line)) {
        stringstream ss(line);

        int id;
        string name;
        double power;
        string room;
        int status;

        char comma;

        ss >> id >> comma;
        getline(ss, name, ',');
        ss >> power >> comma;
        getline(ss, room, ',');
        ss >> status;

        devices[id] = Device(id, name, power, room);

        if (status == 1) {
            devices[id].toggle(); // restore ON state
        }
    }

    file.close();
}

void EnergyMonitor::saveToFile() {
    ofstream file("devices.txt");

    for (auto &pair : devices) {
        Device &d = pair.second;

        file << pair.first << ","
             << d.getName() << ","
             << d.getPower() << ","
             << d.getRoom() << ","
             << d.isOn()
             << endl;
    }

    file.close();
}
void EnergyMonitor::printAlerts() {
    alertHistory.displayAlerts();
}
void EnergyMonitor::setThreshold(double t) {
    powerThreshold = t;
}
void EnergyMonitor::calculateConsumption() {

    totalConsumption = 0;

    for (auto &pair : devices) {

        Device &d = pair.second;

        if (d.isOn()) {
            totalConsumption += d.getPower();
        }
    }

    cout << "Total Consumption: "
         << totalConsumption
         << " W" << endl;

    if (totalConsumption > consumptionThreshold) {

        cout << " TOTAL ENERGY LIMIT EXCEEDED!\n";

        alertHistory.addAlert(
            "Total consumption exceeded limit!"
        );
    }
}
void EnergyMonitor::setConsumptionThreshold(double t) {
    consumptionThreshold = t;
}
void EnergyMonitor::analyzeRoomUsage() {

    std::map<std::string, double> roomUsage;

    for (auto &pair : devices) {

        Device &d = pair.second;

        if (d.isOn()) {
            roomUsage[d.getRoom()] += d.getPower();
        }
    }

    std::string highestRoom = "";
    double maxPower = 0;

    for (auto &room : roomUsage) {

        cout << room.first
             << " : "
             << room.second
             << " W" << endl;

        if (room.second > maxPower) {

            maxPower = room.second;
            highestRoom = room.first;
        }
    }

    cout << "\nHighest Consuming Room: "
         << highestRoom
         << " ("
         << maxPower
         << " W)" << endl;
}