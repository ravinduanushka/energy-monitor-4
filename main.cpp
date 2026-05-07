#include <iostream>
#include <string>
using namespace std;
#include "EnergyMonitor.h"
int main() {
    EnergyMonitor monitor;
    monitor.loadFromFile();  

    monitor.addDevice(1, "Fan", 60, "Room1");
    monitor.addDevice(2, "Light", 20, "Room2");
    
    int choice;
while (true) {
    cout << "=== Energy Monitor ===" << endl;
    cout << "1. Add Device" << endl;
    cout << "2. Toggle Device" << endl;
    cout << "3. List Devices" << endl;
    cout << "4. Undo" << endl;
    cout << "5. Show Alerts" << endl;
    cout << "6. Calculate Consumption" << endl;
    cout << "7. Set Consumption Threshold" << endl;
    cout << "8. Analyze Room Usage" << endl;
    cout << "9. Live 7-Second Dashboard" << endl;
    cout << "10. Control Room (ON/OFF)" << endl;
    cout << "11. Show Room Usage" << endl;
    cout << "12. Check Room Limit" << endl;
    cout << "13. Save And Exit" << endl;



    // cout << "0. Exit" << endl;

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
        else if (choice == 4) {
            monitor.undo();   
        }

        else if (choice == 0) {
            cout << "Exiting...\n";
            break;
        }
        else if (choice == 5) {
            monitor.printAlerts();
        }
        
        else if (choice == 6) {
            monitor.calculateConsumption();
        }
        else if (choice == 7) {
            double threshold;
            cout << "Enter new consumption threshold: ";
            cin >> threshold;
            monitor.setConsumptionThreshold(threshold);
        }
        else if (choice == 8) {
    monitor.analyzeRoomUsage();
       }
        else if (choice == 9) {
            monitor.live7SecondDashboard();
        }   
    
        else if (choice == 10) {
        string room;
        int state;

        cout << "Enter Room Name: ";
        cin >> room;

        cout << "1 = ON, 0 = OFF: ";
        cin >> state;

        monitor.controlRoom(room, state);
    }
        else if (choice == 11) {
            monitor.showRoomControl();
        }
        else if (choice == 12) {
            monitor.checkRoomLimit();
        }
        else if (choice == 13) {
            monitor.saveToFile();
            cout << "Data saved. Exiting...\n";
            break;
        }

        else {
            cout << "Invalid choice!\n";
        }
    }
    return 0;
}
   