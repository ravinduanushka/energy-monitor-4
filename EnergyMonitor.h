#ifndef ENERGY_MONITOR_H
#define ENERGY_MONITOR_H

#include <map>
#include <queue>
#include <vector>
#include <string>
#include "Device.h"
#include "UndoStack.h"

class EnergyMonitor {
private:
    std::map<int, Device> devices;   // device storage
    std::queue<int> dataQueue;       // simple queue for now
    std::vector<std::string> alerts;
    UndoStack undoStack;

    
public:
    EnergyMonitor();

    // Core features (your menu functions)
    void addDevice(int id, std::string name, double power, std::string room);
    void toggleDevice(int id);    
    void listDevices();
    void showStatus();
    void undo();

    void pushReading(int time);
    void processStream();

    void printAlerts();

    // future features
    std::map<int, Device>& getDevices();
};

#endif
