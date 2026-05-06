#include <iostream>
#include <string>
using namespace std;
#include "EnergyMonitor.h"
int main() {
    EnergyMonitor monitor;

    monitor.addDevice(1, "Fan", 60, "Room1");
    monitor.addDevice(2, "Light", 20, "Room2");
    
    int choice;
while (true) {
    cout << "=== Energy Monitor ===" << endl;
    cout << "1. Add Device" << endl;
    cout << "2. Toggle Device" << endl;
    cout << "3. List Devices" << endl;
    cout << "0. Exit" << endl;

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

    cout << "Device Added with Room Successfully!\n";
} 
 else if (choice == 2) {
            int id;
            cout << "Enter Device ID: ";
            cin >> id;

            monitor.toggleDevice(id);
        }

        else if (choice == 3) {
            monitor.showStatus();  
        }

        else if (choice == 0) {
            cout << "Exiting...\n";
            break;
        }

        else {
            cout << "Invalid choice!\n";
        }
    }
    return 0;
}
   