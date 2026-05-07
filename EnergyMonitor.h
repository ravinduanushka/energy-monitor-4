#ifndef ENERGY_MONITOR_H
#define ENERGY_MONITOR_H

#include <map>

#include <vector>
#include <string>
#include "Device.h"
#include "UndoStack.h"
#include "AlertHistory.h"
#include "TreeNode.h"

class EnergyMonitor {
private:
    std::map<int, Device> devices;   // device storage

    AlertHistory alertHistory;
    UndoStack undoStack;
    double powerThreshold = 50;
    double totalConsumption = 0;
    double consumptionThreshold = 500;
    double roomLimit = 100;
    std::vector<double> last7Seconds;
    std::map<std::string, std::vector<std::string>> roomGraph;
     std::map<std::string, double> roomEnergy;
     
    
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
    
    void printAlerts();

    
    void setThreshold(double t);

    void calculateConsumption();
    void setConsumptionThreshold(double t);

    void analyzeRoomUsage();

    
    void updateConsumptionHistory();
    void show7SecondGraph();
    void live7SecondDashboard();
    void connectRooms(std::string r1, std::string r2);
    void updateRoomEnergy();
    void showRoomGraph();
    void findHighUsagePath();
    void dfsPath(std::string room, double currentSum,
             std::map<std::string, bool>& visited,
             std::string path,
             std::string& bestPath,
             double& maxSum);
    


    std::map<int, Device>& getDevices();
    void controlRoom(std::string room, bool state);
    void showRoomControl();
    void checkRoomLimit();
};

#endif
