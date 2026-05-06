#include <iostream>
using namespace std;
#include "EnergyMonitor.h"


int main() {
    EnergyMonitor monitor;
    int choice;

    cout << "=== Energy Monitor ===" << endl;
    cout << "1. Add Device" << endl;
    cout << "2. Toggle Device" << endl;
    cout << "3. List Devices" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
    int id;
    string name;
    double power;
    string room;

    cout << "Enter Device ID: ";
    cin >> id;

    cout << "Enter Device Name: ";
    cin >> name;

    cout << "Enter Power Rating: ";
    cin >> power;

    cout << "Enter Room Name: ";
    cin >> room;

    monitor.addDevice(id, name, power, room);

    cout << "✅ Device Added with Room Successfully!\n";
}
    return 0;
}