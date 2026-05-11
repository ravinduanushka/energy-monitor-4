#include <iostream>   
#include <map>        
#include <string>     
#include "EnergyMonitor.h"
#include "Device.h"
#include <fstream>
#include <sstream>
#include <windows.h>
#include <conio.h>
#include <conio.h>
#include <ctime>
using namespace std;

EnergyMonitor::EnergyMonitor() 
    : alertHistory(5)  // keep last 5 alerts
    {

}

void EnergyMonitor::addDevice(int id, std::string name, double power, std::string room) {
    if (devices.find(id) != devices.end()) {

        cout << "Device ID already exists! Updating instead...\n";

        devices[id] = Device(id, name, power, room);

        return;
    }
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

    // Save reading to history for Merge Sort
    EnergyReading reading = {"TOTAL", (double)time(0), totalConsumption};
    usageHistory.push_back(reading);
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


void EnergyMonitor::live7SecondDashboard() {

    while (true) {

        if (_kbhit()) {
            char key = _getch();

            if (key == 'q' || key == 'Q') {
                cout << "\nExiting dashboard...\n";
                break;
            }
        }

        double total = 0;

        for (auto &pair : devices) {
            Device &d = pair.second;
            if (d.isOn()) total += d.getPower();
        }

        if (last7Seconds.size() == 7)
            last7Seconds.erase(last7Seconds.begin());

        last7Seconds.push_back(total);

        system("cls");

        cout << "=== LIVE DASHBOARD (Press Q to exit) ===\n\n";
        cout << "Total: " << total << " W\n\n";

        for (double v : last7Seconds) {
            cout << v << "W | ";
            for (int i = 0; i < v / 10; i++) cout << "#";
            cout << endl;
        }

        Sleep(1000);
    }
}
void EnergyMonitor::connectRooms(std::string r1, std::string r2) {

    roomGraph[r1].push_back(r2);
    roomGraph[r2].push_back(r1);

    cout << "Connected " << r1 << " <-> " << r2 << endl;
}
void EnergyMonitor::updateRoomEnergy() {

    roomEnergy.clear();

    for (auto &pair : devices) {

        Device &d = pair.second;

        if (d.isOn()) {
            roomEnergy[d.getRoom()] += d.getPower();
        }
    }
}

void EnergyMonitor::showRankedDevices() {
    std::vector<Device> deviceList;
    for (auto const& [id, d] : devices) {
        deviceList.push_back(d);
    }

    bubbleSortDevices(deviceList);

    cout << "\n=== DEVICES RANKED BY POWER (Bubble Sort) ===\n";
    for (const auto& d : deviceList) {
        cout << d.getName() << " : " << d.getPower() << " W [" << d.getRoom() << "]\n";
    }
}

void EnergyMonitor::generateHistoryReport() {
    if (usageHistory.empty()) {
        cout << "No history data available yet!\n";
        return;
    }

    std::vector<EnergyReading> sortedHistory = usageHistory;
    mergeSortReadings(sortedHistory, 0, sortedHistory.size() - 1);

    cout << "\n=== PEAK USAGE REPORT (Merge Sort) ===\n";
    int count = 0;
    for (const auto& r : sortedHistory) {
        cout << "Consumption: " << r.usage << " W\n";
        if (++count >= 10) break; // Top 10
    }
}
void EnergyMonitor::showRoomGraph() {

    cout << "\n=== ROOM CONNECTIVITY ===\n";

    for (auto &pair : roomGraph) {

        cout << pair.first << " → ";

        for (auto &connected : pair.second) {
            cout << connected << " ";
        }

        cout << endl;
    }
}
void EnergyMonitor::dfsPath(std::string room,
                            double currentSum,
                            std::map<std::string, bool>& visited,
                            std::string path,
                            std::string& bestPath,
                            double& maxSum) {

    visited[room] = true;

    currentSum += roomEnergy[room];
    path += room + " ";

    // update best result
    if (currentSum > maxSum) {
        maxSum = currentSum;
        bestPath = path;
    }

    for (std::string neighbor : roomGraph[room]) {

        if (!visited[neighbor]) {
            dfsPath(neighbor, currentSum, visited, path, bestPath, maxSum);
        }
    }

    visited[room] = false; // backtrack
}
void EnergyMonitor::findHighUsagePath() {

    std::string bestPath = "";
    double maxSum = 0;

    std::map<std::string, bool> visited;

    for (auto &pair : roomGraph) {

        std::string startRoom = pair.first;

        dfsPath(startRoom, 0, visited, "", bestPath, maxSum);
    }

    cout << "\n=== HIGH USAGE PATH ===\n";
    cout << "Path: " << bestPath << endl;
    cout << "Total Usage: " << maxSum << " W\n";
}
void EnergyMonitor::controlRoom(std::string room, bool state) {

    for (auto &pair : devices) {

        Device &d = pair.second;

        if (d.getRoom() == room) {

            if (!state && d.isOn()) {
                d.toggle();   // turn OFF
            }

            if (state && !d.isOn()) {
                d.toggle();   // turn ON
            }
        }
    }

    cout << "Room " << room
         << (state ? " turned ON" : " turned OFF")
         << endl;
}
void EnergyMonitor::showRoomControl() {

    std::map<std::string, double> roomUsage;

    for (auto &pair : devices) {

        Device &d = pair.second;

        if (d.isOn()) {
            roomUsage[d.getRoom()] += d.getPower();
        }
    }

    cout << "\n=== ROOM ENERGY USAGE ===\n";

    for (auto &r : roomUsage) {

        cout << r.first << " = " << r.second << " W\n";
    }
}
void EnergyMonitor::checkRoomLimit() {

    map<string, double> roomUsage;

    // Calculate room totals
    for (auto &pair : devices) {

        Device &d = pair.second;

        if (d.isOn()) {
            roomUsage[d.getRoom()] += d.getPower();
        }
    }

    cout << "\n=== ROOM LIMIT CHECK ===\n";

    bool alertFound = false;

    for (auto &room : roomUsage) {

        cout << room.first
             << " : "
             << room.second
             << " W";

        if (room.second > roomLimit) {

            cout << " LIMIT EXCEEDED";

            alertHistory.addAlert(
                "Room limit exceeded: " + room.first
            );

            alertFound = true;
        }

        cout << endl;
    }

    if (!alertFound) {
        cout << "No rooms exceeded limit.\n";
    }

    for (auto &r : roomUsage) {

        if (r.second > roomLimit) {

            cout << " ALERT: " << r.first
                 << " exceeded limit (" << r.second << " W)\n";

            alertHistory.addAlert(
                "Room overload: " + r.first
            );
        }
    }
}