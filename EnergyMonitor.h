#ifndef ENERGY_MONITOR_H
#define ENERGY_MONITOR_H

#include <map>
#include <queue>
#include <vector>
#include <string>
#include "Device.h"
#include "UndoStack.h"
#include "AlertHistory.h"
#include "TreeNode.h"

class EnergyMonitor {
private:
    std::map<int, Device> devices;   // device storage
    std::queue<int> dataQueue;       // simple queue for now
    AlertHistory alertHistory;
    UndoStack undoStack;
    double powerThreshold = 50;
    double totalConsumption = 0;
    double consumptionThreshold = 100;
    std::vector<double> last7Seconds;

    
public:
    EnergyMonitor();

    // Core features (your menu functions)
    void addDevice(int id, std::string name, double power, std::string room);
    void toggleDevice(int id);    
    void listDevices();
    void showStatus();
    void undo();
   
    void loadFromFile();
    void saveToFile();
    void alertHis();
    void printAlerts();

    void pushReading(int time);
    void processStream();
    void setThreshold(double t);

    void calculateConsumption();
    void setConsumptionThreshold(double t);

    void analyzeRoomUsage();

    
    void updateConsumptionHistory();
    void show7SecondGraph();
    void live7SecondDashboard();

    

    // future features
    std::map<int, Device>& getDevices();
};

#endif
